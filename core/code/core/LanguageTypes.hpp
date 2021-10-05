// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "GridElement.hpp"

#include <itlib/flat_map.hpp>

namespace core
{

using Alphabet = std::vector<GridElement>;
using Specials = std::vector<GridElement>;

using LetterConversionTarget = LetterSequence<3>;
using LetterConversionTable = itlib::flat_map<letter_t, LetterConversionTarget>;

} // namespace core
