// word-grid
// Copyright (c) 2019 Borislav Stanimirov
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

namespace core
{

Grid::Grid(size_t w, size_t h, itlib::const_memory_view<WordElement> letters)
    : m_width(w)
    , m_height(h)
{
    if (letters.empty())
    {
        m_ownedElements.resize(w * h);
        acquireElementOwnership();
    }
    else
    {
        assert(letters.size() >= w * h);
        m_elements = letters;
    }
}

Grid::~Grid() = default;

Grid::Grid(Grid&&) noexcept = default;
Grid& Grid::operator=(Grid&&) noexcept = default;

void Grid::acquireElementOwnership()
{
    assert(m_ownedElements.empty() || m_elements.data() != m_ownedElements.data());
    m_ownedElements.resize(m_width * m_height);
    m_ownedElements.assign(m_elements.begin(), m_elements.begin() + m_ownedElements.size());
    m_elements.reset(m_ownedElements.data(), m_ownedElements.size());
}

template <typename Visitor>
void Grid::visitAll(Visitor& v, itlib::memory_view<GridCoord> coords) const
{
    GridCoord c;
    for (c.y = 0; c.y < m_height; ++c.y)
    {
        for (c.x = 0; c.x < m_width; ++c.x)
        {
            auto& elem = this->at(c);
            if (!v.push(elem, c)) continue;

            coords.front() = c;

            if (v.done()) return;

            if (this->visitAllR(v, coords, 1))
            {
                return;
            }

            v.pop(elem);
        }
    }
}

template <typename Visitor>
bool Grid::visitAllR(Visitor& v, itlib::memory_view<GridCoord>& coords, size_t length) const
{
    const auto& base = coords[length - 1];

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

            bool alreadyUsed = [&c, &coords, length]()
            {
                for (size_t i = 0; i < length; ++i)
                {
                    if (coords[i] == c) return true;
                }
                return false;
            }();

            if (alreadyUsed) continue;

            auto& elem = this->at(c);
            if (!v.push(elem, c)) continue;

            coords[length] = c;

            if (v.done()) return true;

            if (visitAllR(v, coords, length + 1))
            {
                return true;
            }

            v.pop(elem);
        }
    }

    return false;
}

namespace
{
struct TestPatterVisitor
{
    itlib::static_vector<itlib::const_memory_view<letter>, WordTraits::Max_Length + 1> top;
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
                top.back() = {};
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

size_t Grid::testPattern(itlib::const_memory_view<letter> pattern, itlib::memory_view<GridCoord> coords) const
{
    assert(coords.size() >= pattern.size());
    TestPatterVisitor v = { {pattern} };
    visitAll(v, coords);
    return v.top.size() - 1;
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
    itlib::static_vector<GridCoord, WordTraits::Max_Length> coords;

    bool push(const WordElement& elem, const GridCoord& c)
    {
        if (elem.frontOnly() && !coords.empty())  return false;

        coords.push_back(c);

        auto begin = elem.lbegin();
        auto matchLength = elem.matchLength();
        Dictionary::SearchResult result = Dictionary::SearchResult::None;
        for (size_t i = 0; i < matchLength; ++i)
        {
            result = d.search(ds, *(begin + i));
        }

        if (result == Dictionary::SearchResult::Exact)
        {
            out.addWord(ds.word(), itlib::make_memory_view(coords));
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
        assert(coords.size() != 0);
        coords.pop_back();

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
    itlib::static_vector<GridCoord, WordTraits::Max_Length> coords(WordTraits::Max_Length);
    visitAll(v, itlib::make_memory_view(coords));
}

}