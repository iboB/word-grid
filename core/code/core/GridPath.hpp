// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "WordTraits.hpp"
#include "GridCoord.hpp"

#include <itlib/static_vector.hpp>

namespace core
{
class GridPath : public itlib::static_vector<GridCoord, WordTraits::Max_Length> {};
}
