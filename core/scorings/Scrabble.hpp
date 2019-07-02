#pragma once

#include "../Scoring.hpp"

namespace core
{
namespace scorings
{
// give a score per word based on individual scores per word element
// with different lengths inducing different mulitpliers
class Scrabble final : public Scoring
{
public:
    Scrabble();
    virtual score_t calcScore(const Scoring::WordView& view) const override;
private:
};
}
}