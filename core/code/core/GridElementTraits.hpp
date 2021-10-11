// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <cstddef>

namespace core
{

struct GridElementTraits
{
    static constexpr size_t Min_Length = 1;
    static constexpr size_t Max_Length = 5;
};

} // namespace core
