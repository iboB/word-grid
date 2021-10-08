// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <core/PRNG.hpp>
#include <iostream>

namespace test
{

core::PRNG makePrng()
{
    auto seed = core::PRNG::randomDevice();
    std::cout << "Creating PRNG with seed: " << seed << '\n';
    return core::PRNG(seed);
}

}
