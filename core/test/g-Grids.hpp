// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <core/Grid.hpp>
#include <core/LetterSequenceFromUtf8.hpp>

namespace test
{

// generates an alphabetical grid
// example
// abcd
// efgh
// ijkl
// mnop
inline core::Grid Grid_alphabetical()
{
    core::Grid g({4, 4});
    core::letter_t letter = 'a';
    for (auto& e : g.elements()) e.push_back(letter++);
    return g;
}

// a  b  c    d
// zy b  beg- h
// i  j  a/l  l
// m  n  o    -end
inline core::Grid Grid_fancy()
{
    auto g = Grid_alphabetical();
    auto elems = g.elements();
    core::LetterSequence_FromUtf8(elems[4], "zy");
    core::LetterSequence_FromUtf8(elems[5], "b");
    core::LetterSequence_FromUtf8(elems[6], "beg-");
    core::LetterSequence_FromUtf8(elems[10], "a/l");
    core::LetterSequence_FromUtf8(elems[15], "-end");
    return g;
}
} // namespace test
