// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"
#include "WordTraits.hpp"

#include <itlib/static_vector.hpp>

namespace core
{
using WordMatchSequence = itlib::static_vector<letter_t, WordTraits::Max_Length>;
}
