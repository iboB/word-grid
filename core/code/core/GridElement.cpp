// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "GridElement.hpp"

#include <algorithm>

namespace core
{

GridElement::OptionIterator GridElement::firstOption() const
{
    return {
        begin(),
        std::find(begin(), end(), Delim_Sign),
        end(),
    };
}

void GridElement::OptionIterator::goToNext()
{
    srcFrom = srcTo + 1; // skip delimeter

    // we currently support up to two options per element
    // that's why we can afford this optimization
    srcTo = srcEnd;
}

LetterSequenceView GridElement::OptionIterator::getMatchSequence() const
{
    auto length = size_t(srcTo - srcFrom);
    if (*srcFrom == Cont_Sign) return {srcFrom + 1, length - 1};
    if (*(srcTo - 1) == Cont_Sign) return {srcFrom, length - 1};
    return LetterSequenceView(srcFrom, length);
}

bool GridElement::matchesWord(LetterSequenceView word) const
{
    if (frontOnly() || backOnly())
    {
        auto ms = firstOption().getMatchSequence();
        if (frontOnly())
        {
            // slice guarantees no errors even if out of bounds
            word = word.slice(0, ms.size());
        }
        else
        {
            word = word.slice(word.size() - ms.size());
        }
        return ms == word;
    }

    for (auto option = firstOption(); !option.isEnd(); option.goToNext())
    {
        auto ms = option.getMatchSequence();
        auto f = std::search(word.begin(), word.end(), ms.begin(), ms.end());
        if (f != word.end()) return true;
    }

    return false;
}

} // namespace core
