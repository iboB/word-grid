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

// this should be moved to either Language or Game as configurable data
struct WordLengthTraits
{
    static constexpr size_t Short_Max = 4;
    static constexpr size_t Medium_Max = 5;
    static constexpr size_t Long_Max = 7;
    static constexpr size_t Longer_Max = 12;
    static constexpr size_t SuperLong_Max = 16; // not actually checked... should be equal to WordTraits::Max_Length
};

} // namespace core
