// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "BoardUtils.hpp"

#include "Word.hpp"
#include "Grid.hpp"
#include "WordElement.hpp"
#include "Dictionary.hpp"
#include "DictionarySearch.hpp"
#include "ScoredWord.hpp"

#include <itlib/memory_view.hpp>

#include <cassert>

namespace core::impl
{

namespace
{

template <typename Visitor>
bool visitGridR(const Grid& g, Visitor& v, GridPath& path)
{
    const auto& base = path.back();

    for (int y = -1; y <= 1; ++y)
    {
        GridCoord c;
        c.y = base.y + y;
        if (c.y >= g.h()) continue;
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = base.x + x;
            if (c.x >= g.w()) continue;

            bool alreadyUsed = [&c, &path]()
            {
                for (auto& u : path)
                {
                    if (u == c) return true;
                }
                return false;
            }();

            if (alreadyUsed) continue;

            auto& elem = g.at(c);
            if (!v.push(elem, c)) continue;
            path.push_back(c);

            if (v.done()) return true;

            if (visitGridR(g, v, path))
            {
                return true;
            }

            path.pop_back();
            v.pop(elem);
        }
    }

    return false;
}

template <typename Visitor>
void visitGrid(const Grid& g, Visitor& v, GridPath& path)
{
    assert(path.empty());
    GridCoord c;
    for (c.y = 0; c.y < g.h(); ++c.y)
    {
        for (c.x = 0; c.x < g.w(); ++c.x)
        {
            auto& elem = g.at(c);
            if (!v.push(elem, c)) continue;
            path.push_back(c);

            if (v.done()) return;

            if (visitGridR(g, v, path))
            {
                return;
            }

            path.pop_back();
            v.pop(elem);
        }
    }
}

struct TestPatterVisitor
{
    itlib::static_vector<itlib::const_memory_view<letter_t>, WordTraits::Max_Length + 1> top;
    bool push(const WordElement& elem, const GridCoord&)
    {
        auto& pattern = top.back();

        // skip hyphens
        if (pattern.front() == '-' && top.size() > 1)
        {
            if (pattern.size() == 1) return false; // ends with hyphen?
            pattern = itlib::make_memory_view(pattern.data() + 1, pattern.size() - 1);
        }

        if (!elem.matches(pattern)) return false;
        if (top.size() != 1 && elem.frontOnly()) return false;

        const auto matchLength = elem.matchLength();

        if (top.size() == 1 && elem.backOnly())
        {
            if (pattern.size() == matchLength)
            {
                top.emplace_back();
            }
            else
            {
                return false;
            }
        }
        else
        {
            top.emplace_back(itlib::make_memory_view(pattern.data() + matchLength, pattern.size() - matchLength));
        }

        return true;
    }

    bool done() const
    {
        return top.back().empty();
    }

    void pop(const WordElement&)
    {
        assert(!top.empty());
        top.pop_back();
    }
};

struct FindAllVisitor
{
    FindAllVisitor(const Dictionary& dic, std::vector<ScoredWord>& out)
        : d(dic)
        , out(out)
    {}

    const Dictionary& d;
    std::vector<ScoredWord>& out;
    DictionarySearch ds;
    GridPath path;

    void addWord(const Word& word, const GridPath& path)
    {
        auto& newWord = out.emplace_back();
        newWord.word = word;
        newWord.path = path;
    }


    bool push(const WordElement& elem, const GridCoord& c)
    {
        if (elem.frontOnly() && !path.empty())  return false;

        path.push_back(c);

        auto begin = elem.lbegin();
        auto matchLength = elem.matchLength();
        Dictionary::SearchResult result = Dictionary::SearchResult::None;
        for (size_t i = 0; i < matchLength; ++i)
        {
            result = d.search(ds, *(begin + i));
        }

        if (result == Dictionary::SearchResult::Exact)
        {
            addWord(ds.word(), path);
        }

        if (result == Dictionary::SearchResult::None || elem.backOnly())
        {
            pop(elem);
            return false;
        }

        return true; // partial match
    }

    bool done()
    {
        return false;
    }

    void pop(const WordElement& elem)
    {
        assert(!path.empty());
        path.pop_back();

        auto matchLength = elem.matchLength();
        assert(ds.length() >= matchLength);
        for (size_t i = 0; i < matchLength; ++i) ds.pop();
    }
};

}

GridPath testGridPattern(const Grid& grid, const Word& pattern)
{
    TestPatterVisitor v = { { itlib::make_memory_view(pattern) }  };
    GridPath ret;
    visitGrid(grid, v, ret);
    return ret;
}

std::vector<ScoredWord> findAllWordsInGrid(const Grid& grid, const Dictionary& dictionary)
{
    std::vector<ScoredWord> ret;
    FindAllVisitor v(dictionary, ret);
    GridPath path;
    visitGrid(grid, v, path);
    return ret;
}

}
