// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <itlib/memory_view.hpp>
#include <itlib/static_vector.hpp>

namespace core
{

template <size_t L>
using LetterSequence = itlib::static_vector<letter_t, L>;

using LetterSequenceView = itlib::const_memory_view<letter_t>;

} // namespace core
