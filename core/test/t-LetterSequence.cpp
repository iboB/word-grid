// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/Word.hpp>
#include <core/WordElement.hpp>

using namespace core;

TEST_SUITE_BEGIN("LetterSequence");

TEST_CASE("construct")
{
    auto w1 = Word::fromAscii("asdf");
    CHECK(w1.length() == 4);
    auto w2 = Word::fromAscii("asdf");
    CHECK(w1 == w2);

    w1 = Word::fromAscii("superextralongword");
    CHECK(w1.length() == WordTraits::Max_Length);
    w2 = Word::fromAscii("superextralongwo");
    CHECK(w1 == w2);
}

TEST_CASE("cmp")
{
    auto w1 = Word::fromAscii("asdf");
    auto w1a = Word::fromAscii("asdf");
    auto w2 = Word::fromAscii("azdf");
    auto w3 = Word::fromAscii("asdfa");
    auto w4 = Word::fromAscii("asdfz");

    CHECK(!(w1 < w1a));
    CHECK(!(w1a < w1));
    CHECK(w1 < w2);
    CHECK(w1 < w3);
    CHECK(w3 < w2);
    CHECK(w4 < w2);
    CHECK(w3 < w4);
    CHECK(w1 < w4);
}

TEST_CASE("elems basic")
{
    Word w = Word::fromAscii("absolutely");

    auto e = WordElement::fromAscii("a");
    CHECK(e.length() == 1);
    CHECK(!e.frontOnly());
    CHECK(!e.backOnly());
    CHECK(e.matchLength() == 1);
    CHECK(e.matches(w.view()));
}

TEST_SUITE_END();
