#include "Flat.hpp"

namespace core
{
namespace scorings
{
Flat::Flat(score_t score)
    : m_score(score)
{}

score_t Flat::calcScore(const Scoring::WordView& view) const
{
    return m_score;
}
}
}
