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
struct WordMatchSequence : public itlib::static_vector<letter_t, WordTraits::Max_Length>
{
    bool operator<(const WordMatchSequence& b) const {
        auto ai = begin();
        auto aend = end();
        auto bi = b.begin();
        auto bend = b.end();
        for (; (ai != aend) && (bi != bend); ++ai, ++bi)
        {
            if (*ai < *bi) return true;
            if (*bi < *ai) return false;
        }
        return (ai == aend) && (bi != bend);
    }
};

}
