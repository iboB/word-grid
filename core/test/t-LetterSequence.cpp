// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/LetterSequenceFromUtf8.hpp>
#include <core/WordMatchSequence.hpp>

using namespace core;

TEST_SUITE_BEGIN("LetterSequence");

WordMatchSequence wms(std::string_view str)
{
    return LetterSequence_FromUtf8<WordMatchSequence>(str);
}

TEST_CASE("construct")
{
    auto w1 = wms("asdf");
    CHECK(w1.size() == 4);
    CHECK(w1[0] == 'a');
    CHECK(w1[1] == 's');
    CHECK(w1[2] == 'd');
    CHECK(w1[3] == 'f');
    auto w2 = wms("asdf");
    CHECK(w1 == w2);

    w1 = wms("superextralongword");
    CHECK(w1.size() == WordTraits::Max_Length);
    w2 = wms("superextralongwo");
    CHECK(w1 == w2);
}

TEST_CASE("cmp")
{
    auto w1 = wms("asdf");
    auto w1a = wms("asdf");
    auto w2 = wms("azdf");
    auto w3 = wms("asdfa");
    auto w4 = wms("asdfz");

    CHECK(w1 == w1);
    CHECK(w1 == w1a);
    CHECK(w1.getView() == w1.getView());
    CHECK(w1.getView() == w1a.getView());

    CHECK(!(w1 < w1a));
    CHECK(!(w1a < w1));
    CHECK(w1 < w2);
    CHECK(w1 < w3);
    CHECK(w3 < w2);
    CHECK(w4 < w2);
    CHECK(w3 < w4);
    CHECK(w1 < w4);
    CHECK(w3.getView() < w4.getView());
    CHECK(w1.getView() < w4.getView());
}
