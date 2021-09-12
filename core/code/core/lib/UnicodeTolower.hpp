// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "../API.h"

#include <cstdint>

namespace core
{

// convert unicode character to lower case
// returns the same character if no lower case exists for it
CORE_API uint32_t UnicodeTolower(uint32_t c);

}
