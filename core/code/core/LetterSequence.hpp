// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"
#include <itlib/static_vector.hpp>
#include <itlib/memory_view.hpp>

namespace core
{

template <size_t Capacity, typename Child>
class LetterSequence : public itlib::static_vector<letter, Capacity>
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

    itlib::memory_view<letter> view()
    {
        return itlib::make_memory_view(*this);
    }

    itlib::const_memory_view<letter> view() const
    {
        return itlib::make_memory_view(*this);
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