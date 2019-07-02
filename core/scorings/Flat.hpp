#pragma once

#include "../Scoring.hpp"

namespace core
{
namespace scorings
{
// give a flat score per word regardless of length or elements
class Flat final : public Scoring
{
public:
    Flat(score_t score = 13);
    virtual score_t calcScore(const Scoring::WordView& view) const override;
private:
    const score_t m_score;
};
}
}