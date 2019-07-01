#pragma once

#include "Types.hpp"
#include <chobo/static_vector.hpp>
#include <chobo/memory_view.hpp>

namespace core
{

template <size_t Capacity, typename Child>
class LetterSequence : public chobo::static_vector<letter, Capacity>
{
public:
    LetterSequence() = default;
    ~LetterSequence() = default;

    static Child fromAscii(const char* ascii)
    {
        Child ret;
        while (*ascii && ret.length() < Capacity)
        {
            ret.emplace_back(*ascii++);
        }
        return ret;
    }

    LetterSequence(const LetterSequence&) = default;
    LetterSequence& operator=(const LetterSequence&) = default;
    LetterSequence(LetterSequence&&) noexcept = default;
    LetterSequence& operator=(LetterSequence&&) noexcept = default;

    size_t length() const { return this->size(); }

    chobo::memory_view<letter> view()
    {
        return chobo::make_memory_view(*this);
    }

    chobo::const_memory_view<letter> view() const
    {
        return chobo::make_memory_view(*this);
    }
};

template <size_t Capacity, typename Child>
bool operator<(const LetterSequence<Capacity, Child>& a, const LetterSequence<Capacity, Child>& b) {
    auto ai = a.begin();
    auto aend = a.end();
    auto bi = b.begin();
    auto bend = b.end();
    for (; (ai != aend) && (bi != bend); ++ai, ++bi)
    {
        if (*ai < *bi) return true;
        if (*bi < *ai) return false;
    }
    return (ai == aend) && (bi != bend);
}

}