#pragma once

#include "LetterSequence.hpp"
#include "GridElementTraits.hpp"

#include <chobo/memory_view.hpp>

namespace core
{
// a grid element constists of one or more letters plus optional special characters
// letters with no special characters match themeselves
// "-xxx" - must end with "xxx"
// "xxx-" - must begin with "xxx"
class GridElement : public LetterSequence<GridElementTraits::Max_Length>
{
public:
    // checks whether the element matches the pattern
    // we have numPrevMatches as an argument to help check whether this is the beginning of the pattern
    // if it's 0, we assume a beginning
    bool matches(const chobo::const_memory_view<letter>& pattern) const;

    bool frontOnly() const { return back() == '-'; }
    bool backOnly() const { return front() == '-'; }

    // how many letters of the input does this sequence match
    size_t matchLength() const;
};
}