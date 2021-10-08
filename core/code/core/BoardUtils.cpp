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

#include "GridVisiting.hpp"

#include <itlib/memory_view.hpp>

#include <cassert>

namespace core::impl
{

namespace
{

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
    FindAllVisitor(const Dictionary& dic, FoundWordCB cb)
        : d(dic)
        , cb(std::move(cb))
        , ds(dic)
    {}

    const Dictionary& d;
    FoundWordCB cb;
    DictionarySearch ds;
    GridPath path;

    bool push(itlib::const_memory_view<letter_t> elem, const GridCoord& c)
    {
        path.push_back(c);

        DictionarySearch::Result result = DictionarySearch::Result::None;
        for (auto l : elem) result = ds.push(l);

        if (result == DictionarySearch::Result::None)
        {
            pop(elem);
            return false;
        }

        if (result == DictionarySearch::Result::Exact)
        {
            cb(*ds.range().begin, path);
            // Don't return. Search deeper for words which also contain this word as it's beginning
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
    return visitGrid(grid, v);
}

void findAllWordsInGrid(const Grid& grid, const Dictionary& dictionary, FoundWordCB cb)
{
    FindAllVisitor v(dictionary, std::move(cb));
    visitGrid(grid, v);
}

std::vector<ScoredWord> findAllWordsInGridTmp(const Grid& grid, const Dictionary& dictionary)
{
    std::vector<ScoredWord> ret;
    findAllWordsInGrid(grid, dictionary, [&ret](const DictionaryWord& word, const GridPath& path) {
        auto& w = ret.emplace_back();
        w.word = word.letters.getView();
        w.displayString = word.displayString;
        w.path = path;
    });
    return ret;
}

namespace
{

using AvailableNeighbors = itlib::static_vector<GridCoord, 8>;

struct Dir
{
    int8_t x;
    int8_t y;
};

// clang-format off
static const Dir int2dir[] = {
    {-1,-1},
    { 0,-1},
    { 1,-1},

    {-1, 0},
    { 1, 0},

    {-1, 1},
    { 0, 1},
    { 1, 1},
};
// clang-format on

bool randomPathR(GridPath& path, uint32_t targetLength, const Grid& grid, PRNG& rng)
{
    if (path.size() == targetLength) return true;

    auto base = path.back();

    auto start = rng.randomInteger(8);
    for (int i = 0; i < 8; ++i)
    {
        auto dir = int2dir[(start + i) % 8];

        GridCoord attempt = base;
        attempt.x += dir.x;
        attempt.y += dir.y;

        // bounds check
        if (attempt.x >= grid.dim().w) continue;
        if (attempt.y >= grid.dim().h) continue;

        // empty check
        if (!grid[attempt].empty()) continue;

        // used check
        if (path.contains(attempt)) continue;

        path.push_back(attempt);
        if (randomPathR(path, targetLength, grid, rng)) return true;
        path.pop_back();
    }

    return false;
}

} // namespace

GridPath generateRandomEmptyPath(size_t slength, const Grid& grid, PRNG& rng)
{
    auto length = uint32_t(slength);
    auto area = grid.dim().area();
    if (length > area || length > WordTraits::Max_Length) return {};
    if (length == 0) return {};

    // check if we even have enough free cells for the path
    auto haveEnough = [&]() {
        uint32_t empty = length;
        for (auto& elem : grid.elements())
        {
            if (!elem.empty()) continue;
            --empty;
            if (empty == 0) return true;
        }
        return false;
    }();
    if (!haveEnough) return {};

    // start search
    GridPath ret;

    auto start = rng.randomInteger(area);
    for (uint32_t i = 0; i < area; ++i)
    {
        auto c = (i + start) % area;
        if (!grid[c].empty()) continue;
        ret.push_back(grid.dim().coordOf(c));
        if (randomPathR(ret, length, grid, rng)) { return ret; }
        ret.pop_back();
    }

    return {};
}

} // namespace core::impl
