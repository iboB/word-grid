#pragma once

#include "../Scoring.hpp"

namespace core
{
namespace scorings
{
// give a score per word based on length multiplied by a constant
class Length final : public Scoring
{
public:
    Length(float multiplier = 2.7f);
    virtual score_t calcScore(const Scoring::WordView& view) const override;
private:
    const float m_multiplier;
};
}
}