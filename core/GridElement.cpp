#include "GridElement.hpp"

namespace core
{
bool GridElement::matches(const chobo::const_memory_view<letter>& pattern, size_t numPrevMatches) const
{
    if (empty()) return true; // empty matches everything

    size_t i = 0;
    if (front() == '-') ++i; // skip
    size_t b = size();
    if (back() == '-')
    {
        // there are previous matches, so we're not dealing with the beginnign of a word here
        if (numPrevMatches) return false;
        --b;
    }

    auto len = b - i;
    if (len > pattern.size()) return false;

    auto p = pattern.data();

    for (; i < b; ++i)
    {
        if (at(i) != *p++) return false;
    }

    return true;
}
}