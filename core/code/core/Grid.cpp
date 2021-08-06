// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Grid.hpp"

#include "Word.hpp"
#include "Dictionary.hpp"
#include "DictionarySearch.hpp"
#include "ScoredDictionary.hpp"

#include <array>

namespace core
{

Grid::Grid(size_t w, size_t h, itlib::const_memory_view<WordElement> elements)
    : m_width(w)
    , m_height(h)
{
    if (elements.empty())
    {
        m_elements.resize(w * h);
    }
    else
    {
        assert(elements.size() >= w * h);
        m_elements.assign(elements.begin(), elements.begin() + w*h);
    }
}

Grid::~Grid() = default;

Grid::Grid(Grid&&) noexcept = default;
Grid& Grid::operator=(Grid&&) noexcept = default;

template <typename Visitor>
void Grid::visitAll(Visitor& v, GridPath& path) const
{
    assert(path.empty());
    GridCoord c;
    for (c.y = 0; c.y < m_height; ++c.y)
    {
        for (c.x = 0; c.x < m_width; ++c.x)
        {
            auto& elem = this->at(c);
            if (!v.push(elem, c)) continue;
            path.push_back(c);

            if (v.done()) return;

            if (this->visitAllR(v, path))
            {
                return;
            }

            path.pop_back();
            v.pop(elem);
        }
    }
}

template <typename Visitor>
bool Grid::visitAllR(Visitor& v, GridPath& path) const
{
    const auto& base = path.back();

    for (int y = -1; y <= 1; ++y)
    {
        GridCoord c;
        c.y = base.y + y;
        if (c.y >= m_height) continue;
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = base.x + x;
            if (c.x >= m_width) continue;

            bool alreadyUsed = [&c, &path]()
            {
                for (auto& u : path)
                {
                    if (u == c) return true;
                }
                return false;
            }();

            if (alreadyUsed) continue;

            auto& elem = this->at(c);
            if (!v.push(elem, c)) continue;
            path.push_back(c);

            if (v.done()) return true;

            if (visitAllR(v, path))
            {
                return true;
            }

            path.pop_back();
            v.pop(elem);
        }
    }

    return false;
}

namespace
{
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
}

GridPath Grid::testPattern(itlib::const_memory_view<letter_t> pattern) const
{
    TestPatterVisitor v = { {pattern} };
    GridPath ret;
    visitAll(v, ret);
    return ret;
}

namespace
{
struct FindAllVisitor
{
    FindAllVisitor(const Dictionary& dic, ScoredDictionary& out)
        : d(dic)
        , out(out)
    {}

    const Dictionary& d;
    ScoredDictionary& out;
    DictionarySearch ds;
    GridPath path;

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
            out.addWord(ds.word(), path);
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

void Grid::findAllWords(const Dictionary& d, ScoredDictionary& out) const
{
    out.clear();
    FindAllVisitor v(d, out);
    GridPath path;
    visitAll(v, path);
}

}
