#pragma once

#include "LetterSequence.hpp"
#include "WordTraits.hpp"

namespace core
{
class Word : public LetterSequence<WordTraits::Max_Length> {};
}