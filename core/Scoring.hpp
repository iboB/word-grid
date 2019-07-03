#pragma once

#include "WordElement.hpp"
#include "GridCoord.hpp"

#include <chobo/memory_view.hpp>
#include <chobo/flat_map.hpp>

namespace core
{

class Grid;

class Scoring
{
public:
    Scoring();
    ~Scoring();

    enum class Type {
        Undefined,
        Flat,
        Length,
    };
    Type type() const { return m_type; }

    // both functions assume
    score_t score(const Grid& grid, chobo::const_memory_view<GridCoord> coords) const;
    score_t score(chobo::const_memory_view<WordElement> word) const;

private:
    Type m_type = Type::Undefined;

    // dispatch the score according to the particular request
    template <typename WordView>
    score_t scoreDispatch(const WordView& wv) const;

    // flat scoring
    score_t m_flatScore = 13;

    // length-based scoring
    float m_lengthMultiplier = 2.7f;
    template <typename WordView>
    score_t scoreLength(const WordView& wv) const;
};

}