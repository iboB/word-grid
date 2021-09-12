// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "UnicodeTolower.hpp"

#include <unordered_map>
#include <limits>

namespace core
{

namespace
{
std::unordered_map<uint16_t, uint16_t> tolowerMap = {
#include "UnicodeTolower.inl"
};
} // namespace

uint32_t UnicodeTolower(uint32_t c)
{
    if (c >= std::numeric_limits<uint16_t>::max()) return c;
    auto f = tolowerMap.find(uint16_t(c));
    if (f == tolowerMap.end()) return c;
    return f->second;
}

}
