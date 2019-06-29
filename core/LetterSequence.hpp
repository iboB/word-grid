#pragma once

#include "Types.hpp"
#include <chobo/static_vector.hpp>

namespace core
{

template <size_t Capacity>
class LetterSequence : public chobo::static_vector<letter, Capacity>
{
public:
    LetterSequence() = default;
    ~LetterSequence() = default;

    static LetterSequence fromAscii(const char* ascii)
    {
        LetterSequence ret;
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

    size_t length() const { return size(); }
};

template <size_t Capacity>
bool operator<(const LetterSequence<Capacity>& a, const LetterSequence<Capacity>& b) {
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