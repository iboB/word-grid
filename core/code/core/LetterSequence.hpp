// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"

#include <itlib/memory_view.hpp>
#include <itlib/static_vector.hpp>

namespace core
{

namespace impl
{
template <typename S>
bool compareLetters(const S& a, const S& b)
{
    auto ai = a.begin();
    auto aend = a.end();
    auto bi = b.begin();
    auto bend = b.end();
    for (; (ai != aend) && (bi != bend); ++ai, ++bi)
    {
        if (*ai < *bi) return true;
        if (*bi < *ai) return false;
    }
    return (ai == aend) && (bi != bend);
}
} // namespace impl

struct LetterSequenceView : public itlib::const_memory_view<letter_t>
{
    using itlib::const_memory_view<letter_t>::const_memory_view;

    bool operator<(const LetterSequenceView& b) const { return impl::compareLetters(*this, b); }
};

template <size_t L>
struct LetterSequence : public itlib::static_vector<letter_t, L>
{
    LetterSequenceView getView() const { return LetterSequenceView(this->data(), this->size()); }

    bool operator<(const LetterSequence& b) const { return impl::compareLetters(*this, b); }
};

} // namespace core
