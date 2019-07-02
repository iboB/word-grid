#include "Length.hpp"

namespace core
{
namespace scorings
{
Length::Length(float multiplier)
    : m_multiplier(multiplier)
{}

score_t Length::calcScore(const Scoring::WordView& view) const
{
    // find actual letter legnth
    size_t length = 0;
    for (size_t i = 0; i < view.size(); ++i)
    {
        length += view.at(i).length();
    }
    return score_t(m_multiplier * length);
}
}
}
