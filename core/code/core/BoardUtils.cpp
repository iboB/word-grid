// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "BoardUtils.hpp"

#include "Dictionary.hpp"
#include "DictionarySearch.hpp"
#include "Grid.hpp"
#include "GridElement.hpp"
#include "PRNG.hpp"
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
    auto& gridElem = g[c];

    if (gridElem.frontOnly() && !path.empty()) return false;

    for (auto option = gridElem.firstOption(); !option.isEnd(); option.goToNext())
    {
        auto seq = option.getMatchSequence();

        if (!v.push(seq, c)) continue;
        path.push_back(c);
        if (v.done()) return true;

        if (!gridElem.backOnly())
        {
            // only recurse if this is not a back-only grid elem
            if (visitGridR(g, v, path)) return true;
        }

        v.pop(seq);
        path.pop_back();
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

            bool alreadyUsed = [&c, &path]() {
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
    itlib::static_vector<LetterSequenceView, WordTraits::Max_Length + 1> top;

    bool push(LetterSequenceView elem, const GridCoord&)
    {
        auto& pattern = top.back();

        auto pp = pattern.begin();
        auto ep = elem.begin();

        while (ep != elem.end())
        {
            if (pp == pattern.end()) return false; // end of pattern before end of element
            if (*ep != *pp) return false; // no match

            ++ep;
            ++pp;
        }

        top.emplace_back(LetterSequenceView(pp, pattern.end() - pp));

        return true;
    }

    bool done() const { return top.back().empty(); }

    void pop(itlib::const_memory_view<letter_t>)
    {
        assert(!top.empty());
        top.pop_back();
    }
};

struct FindAllVisitor
{
    FindAllVisitor(const Dictionary& dic, std::vector<FindAllWord>& out)
        : d(dic)
        , out(out)
        , ds(dic)
    {}

    const Dictionary& d;
    std::vector<FindAllWord>& out;
    DictionarySearch ds;
    GridPath path;

    bool push(itlib::const_memory_view<letter_t> elem, const GridCoord& c)
    {
        path.push_back(c);

        DictionarySearch::Result result = DictionarySearch::Result::None;
        for (auto l : elem) { result = ds.push(l); }

        if (result == DictionarySearch::Result::Exact)
        {
            out.push_back({*ds.range().begin, path});
            // Don't return. Search deeper for words which also contain this word as it's beginning
        }

        if (result == DictionarySearch::Result::None)
        {
            pop(elem);
            return false;
        }

        return true; // partial match
    }

    bool done() { return false; }

    void pop(itlib::const_memory_view<letter_t> elem)
    {
        assert(!path.empty());
        path.pop_back();

        assert(ds.curMatch().size() >= elem.size());
        for (size_t i = 0; i < elem.size(); ++i) ds.pop();
    }
};

} // namespace

GridPath testGridPattern(const Grid& grid, const WordMatchSequence& pattern)
{
    TestPatternVisitor v = {{pattern.getView()}};
    GridPath ret;
    visitGrid(grid, v, ret);
    return ret;
}

std::vector<FindAllWord> findAllWordsInGrid(const Grid& grid, const Dictionary& dictionary)
{
    std::vector<FindAllWord> ret;
    FindAllVisitor v(dictionary, ret);
    GridPath path;
    visitGrid(grid, v, path);
    return ret;
}

namespace
{

using AvailableNeighbors = itlib::static_vector<GridCoord, 8>;

AvailableNeighbors generateAvailableNeighbors(const GridCoord& coord, uint32_t w, uint32_t h, const GridPath& path)
{
    AvailableNeighbors ret;

    for (int y = -1; y <= 1; ++y)
    {
        GridCoord c;
        c.y = coord.y + y;
        if (c.y >= h) continue;
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = coord.x + x;
            if (c.x >= w) continue;

            bool alreadyUsed = [&c, &path]() {
                for (auto& u : path)
                {
                    if (u == c) return true;
                }
                return false;
            }();

            if (alreadyUsed) continue;

            ret.push_back(c);
        }
    }

    return ret;
}

bool randomPathR(GridPath& path, uint32_t targetLength, uint32_t w, uint32_t h, PRNG& rng)
{
    if (path.size() == targetLength) return true;

    auto neighbors = generateAvailableNeighbors(path.back(), w, h, path);

    while (!neighbors.empty())
    {
        auto i = rng.randomInteger(neighbors.size());
        path.push_back(neighbors[i]);
        neighbors.erase(neighbors.begin() + i);
        if (randomPathR(path, targetLength, w, h, rng)) return true;
        path.pop_back();
    }

    return false;
}

} // namespace

GridPath generateRandomPath(uint32_t length, uint32_t w, uint32_t h, PRNG& rng)
{
    if (length > w * h || length > WordTraits::Max_Length) return {};
    if (length == 0) return {};

    GridPath ret;
    // choose starting element
    ret.push_back({rng.randomInteger(uint8_t(w)), rng.randomInteger(uint8_t(h))});

    randomPathR(ret, length, w, h, rng);

    return ret;
}

} // namespace core::impl
