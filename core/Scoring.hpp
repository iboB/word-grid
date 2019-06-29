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
    score_t score(Grid& grid, chobo::const_memory_view<GridCoord> coords) const;
    score_t score(chobo::const_memory_view<WordElement> word) const;

private:
    chobo::flat_map<WordElement, score_t> m_scores;
};

}