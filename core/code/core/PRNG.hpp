// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

namespace core
{

// pseudo-random number generator
// wraps std::minstd_rand in a pimpl object so we don't need to expose the entirety of <random> when including this
class CORE_API PRNG
{
public:
    // negative seed seeds with std::random_device
    PRNG(int seed = -1);
    ~PRNG();

    PRNG(const PRNG&) = delete;
    PRNG& operator=(const PRNG&) = delete;

    // random number from 0 to INT_MAX
    int get();

    // return a random number from 0 to t (t must be <= INT_MAX)
    template <typename T>
    T randomInteger(T t)
    {
        return T(get() % t);
    }

    // get a random element from a std::vector-like container
    template <typename T>
    auto randomElement(const T& t) -> typename T::const_reference
    {
        return t[randomInteger(t.size())];
    }

private:
    static inline constexpr long IMPL_SIZE = 8;

    char m_implBuf[IMPL_SIZE];

    struct Impl;
    Impl& m_impl;

    // function which has access to our private parts and can make the static assertion as early as possible
    static void makeStaticAssert();
};

} // namespace core
