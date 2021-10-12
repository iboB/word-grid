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
int compareLetters(const S& a, const S& b)
{
    // could go with std::lexicographical_compare here, but we don't want to drag <algorithm> into this
    auto ai = a.begin();
    auto aend = a.end();
    auto bi = b.begin();
    auto bend = b.end();
    for (; (ai != aend) && (bi != bend); ++ai, ++bi)
    {
        if (*ai < *bi) return -1;
        if (*bi < *ai) return 1;
    }
    if (ai == aend)
    {
        if (bi == bend) return 0;
        return -1;
    }
    return 1;
}
} // namespace impl

using B_LetterSequenceView = itlib::const_memory_view<letter_t>;
struct LetterSequenceView : public B_LetterSequenceView
{
    using B_LetterSequenceView::const_memory_view;
    using B_LetterSequenceView::operator=;

    bool operator==(const LetterSequenceView& b) const { return impl::compareLetters(*this, b) == 0; }
    bool operator<(const LetterSequenceView& b) const { return impl::compareLetters(*this, b) == -1; }
};

template <size_t L>
struct LetterSequence : public itlib::static_vector<letter_t, L>
{
    LetterSequenceView getView() const& { return LetterSequenceView(this->data(), this->size()); }
    LetterSequenceView getView() && = delete;

    bool operator<(const LetterSequence& b) const { return impl::compareLetters(*this, b) == -1; }
};

} // namespace core
