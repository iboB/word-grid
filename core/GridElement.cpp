#include "GridElement.hpp"

namespace core
{
bool GridElement::matches(const chobo::const_memory_view<letter>& pattern) const
{
    if (empty()) return true; // empty matches everything

    size_t i = 0;
    if (front() == '-') ++i; // skip
    size_t b = size();
    if (back() == '-') --b;

    auto len = b - i;
    if (len > pattern.size()) return false;

    auto p = pattern.data();

    for (; i < b; ++i)
    {
        if (at(i) != *p++) return false;
    }

    return true;
}

size_t GridElement::matchLength() const
{
    if (length() <= 1) return length();
    if (front() == '-' || back() == '-') return length() - 1;
    return length();
}
}