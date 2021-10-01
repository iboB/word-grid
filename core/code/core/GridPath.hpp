// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "GridCoord.hpp"
#include "WordTraits.hpp"

#include <itlib/static_vector.hpp>

namespace core
{
using GridPath = itlib::static_vector<GridCoord, WordTraits::Max_Length>;
} // namespace core
