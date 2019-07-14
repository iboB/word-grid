#pragma once

#include "Types.hpp"
#include "Word.hpp"
#include "GridCoord.hpp"

namespace core
{
struct ScoredWord
{
    Word word;
    chobo::static_vector<GridCoord, WordTraits::Max_Length> coords;
    score_t score;
};
}