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

itlib::const_memory_view<letter_t> GridElement::OptionIterator::getMatchSequence() const
{
    auto length = size_t(srcTo - srcFrom);
    if (*srcFrom == Cont_Sign) return {srcFrom + 1, length - 1};
    if (*(srcTo - 1) == Cont_Sign) return {srcFrom, length - 1};
    return {srcFrom, length};
}

} // namespace core
