// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Scoring.hpp"
#include "Grid.hpp"

namespace core
{

Scoring::Scoring() = default;
Scoring::~Scoring() = default;

Scoring::Scoring(const Scoring&) = default;
Scoring& Scoring::operator=(const Scoring&) = default;

Scoring::Scoring(Scoring&&) noexcept = default;
Scoring& Scoring::operator=(Scoring&&) noexcept = default;

Scoring Scoring::flat(score_t flatScore)
{
    Scoring ret;
    ret.m_type = Type::Flat;
    ret.m_flatScore = flatScore;
    return ret;
}

Scoring Scoring::length(float lengthMultiplier)
{
    Scoring ret;
    ret.m_type = Type::Length;
    ret.m_lengthMultiplier = lengthMultiplier;
    return ret;
}

namespace
{
struct GridCoordView
{
    GridCoordView(const Grid& g, const GridPath& c)
        : grid(g), coords(c)
    {}

    size_t size() const
    {
        return coords.size();
    }

    const WordElement& at(size_t i) const
    {
        return grid.at(coords[i]);
    }

    const Grid& grid;
    const GridPath& coords;
};

struct WordElementView
{
    WordElementView(const itlib::const_memory_view<WordElement>& w)
        : word(w)
    {}

    size_t size() const
    {
        return word.size();
    }

    const WordElement& at(size_t i) const
    {
        return word.at(i);
    }

    itlib::const_memory_view<WordElement> word;
};
}

score_t Scoring::score(const Grid& grid, const GridPath& coords) const
{
    return scoreDispatch(GridCoordView(grid, coords));
}

score_t Scoring::score(itlib::const_memory_view<WordElement> word) const
{
    return scoreDispatch(WordElementView(word));
}

template <typename WordView>
score_t Scoring::scoreDispatch(const WordView& wv) const
{
    switch (m_type)
    {
        case Type::Flat: return m_flatScore;
        case Type::Length: return scoreLength(wv);
        default:
            assert(false);
            return 0;
    }
}

template <typename WordView>
score_t Scoring::scoreLength(const WordView& view) const
{
    // find actual letter legnth
    size_t length = 0;
    for (size_t i=0; i<view.size(); ++i)
    {
        length += view.at(i).matchLength();
    }
    return score_t(m_lengthMultiplier * length);
}

}
