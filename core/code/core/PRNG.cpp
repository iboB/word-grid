// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "PRNG.hpp"

#include <new>
#include <random>

namespace core
{

struct PRNG::Impl
{
    Impl(unsigned seed)
        : rng(seed)
    {}
    std::minstd_rand rng;
};

void PRNG::makeStaticAssert()
{
    static_assert(sizeof(Impl) <= IMPL_SIZE);
}

namespace
{
unsigned fixupSeed(int seed)
{
    if (seed < 0) return std::random_device()();
    return unsigned(seed);
}
} // namespace

PRNG::PRNG(int seed)
    : m_impl(*new (m_implBuf) Impl(fixupSeed(seed)))
{}

PRNG::~PRNG()
{
    m_impl.~Impl();
}

// returns a random number from 0 to INT_MAX
int PRNG::operator()()
{
    return m_impl.rng();
}

} // namespace core