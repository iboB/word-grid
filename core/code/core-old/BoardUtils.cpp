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
bool visitGridR(const Grid& g, Visitor& v, GridPath& path);

template <typename Visitor>
bool visitItem(const Grid& g, const GridCoord& c, Visitor& v, GridPath& path)
{
    auto& gridElem = g.at(c);

    if (gridElem.frontOnly() && !path.empty()) return false;

    for (auto option = gridElem.firstOption(); !option.isEnd(); option.goToNext())
    {
        auto seq = option.getMatchSequence();

        if (!v.push(seq, c)) continue;
        if (v.done()) return true;

        if (!gridElem.backOnly())
        {
            path.push_back(c);
            if (visitGridR(g, v, path)) return true;
            path.pop_back();
        }

        v.pop(seq);
    }

    return false;
}

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

            if (visitItem(g, c, v, path)) return true;
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
            if (visitItem(g, c, v, path)) return;
        }
    }
}

struct TestPatternVisitor
{
    itlib::static_vector<itlib::const_memory_view<letter_t>, WordTraits::Max_Length + 1> top;
    bool push(itlib::const_memory_view<letter_t> elem, const GridCoord&)
    {
        auto& pattern = top.back();

        auto pp = pattern.begin();
        auto ep = elem.begin();

        while (ep != elem.end())
        {
            if (pp == pattern.end())
            {
                return false;
            }
            else if (*pp == '-')
            {
                // skip hyphens
                ++pp;
                continue;
            }
            else if (*ep != *pp)
            {
                // no match
                return false;
            }

            ++ep;
            ++pp;
        }

        top.emplace_back(itlib::const_memory_view(pp, pattern.end() - pp));

        return true;
    }

    bool done() const
    {
        return top.back().empty();
    }

    void pop(itlib::const_memory_view<letter_t>)
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


    bool push(itlib::const_memory_view<letter_t> elem, const GridCoord& c)
    {
        path.push_back(c);

        Dictionary::SearchResult result = Dictionary::SearchResult::None;
        for (auto l : elem)
        {
            result = d.search(ds, l);
        }

        if (result == Dictionary::SearchResult::Exact)
        {
            addWord(ds.word(), path);
        }

        if (result == Dictionary::SearchResult::None)
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

    void pop(itlib::const_memory_view<letter_t> elem)
    {
        assert(!path.empty());
        path.pop_back();

        assert(ds.length() >= elem.size());
        for (size_t i = 0; i < elem.size(); ++i) ds.pop();
    }
};

}

GridPath testGridPattern(const Grid& grid, const Word& pattern)
{
    TestPatternVisitor v = { { itlib::make_memory_view(pattern) }  };
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
