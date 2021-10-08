// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/GridElement.hpp>
#include <core/LetterSequenceFromUtf8.hpp>

using namespace core;

TEST_SUITE_BEGIN("GridElement");

GridElement ge(std::string_view str)
{
    return LetterSequence_FromUtf8<GridElement>(str);
}

TEST_CASE("Basic")
{
    auto e = ge("a");
    CHECK(e.size() == 1);
    CHECK(!e.frontOnly());
    CHECK(!e.backOnly());
    CHECK(e.score() == 0);
    e.setScore(7);
    CHECK(e.score() == 7);

    auto e2 = e;
    CHECK(e2 == e);
    e2.setScore(43);
    CHECK(e2 != e);
    e.setScore(43);
    CHECK(e2 == e);

    auto i = e.firstOption();
    CHECK(!i.isEnd());
    auto seq = i.getMatchSequence();
    CHECK(seq.size() == 1);
    CHECK(seq.front() == 'a');
    i.goToNext();
    CHECK(i.isEnd());

    e = ge("x");
    CHECK(e.score() == 0);
}

TEST_CASE("Front/Back")
{
    auto e = ge("-ed");
    CHECK(e.size() == 3);
    CHECK(!e.frontOnly());
    CHECK(e.backOnly());
    CHECK(e.score() == 0);

    auto i = e.firstOption();
    CHECK(!i.isEnd());
    auto seq = i.getMatchSequence();
    CHECK(seq.size() == 2);
    CHECK(seq.front() == 'e');
    CHECK(seq.back() == 'd');
    i.goToNext();
    CHECK(i.isEnd());

    e = ge("de-");
    CHECK(e.size() == 3);
    CHECK(e.frontOnly());
    CHECK(!e.backOnly());

    i = e.firstOption();
    CHECK(!i.isEnd());
    seq = i.getMatchSequence();
    CHECK(seq.size() == 2);
    CHECK(seq.front() == 'd');
    CHECK(seq.back() == 'e');
    i.goToNext();
    CHECK(i.isEnd());
}

TEST_CASE("multi")
{
    auto e = ge("a/b");
    CHECK(e.size() == 3);
    CHECK(!e.frontOnly());
    CHECK(!e.backOnly());

    auto i = e.firstOption();
    CHECK(!i.isEnd());
    auto seq = i.getMatchSequence();
    CHECK(seq.size() == 1);
    CHECK(seq.front() == 'a');
    i.goToNext();
    CHECK(!i.isEnd());
    seq = i.getMatchSequence();
    CHECK(seq.size() == 1);
    CHECK(seq.front() == 'b');
    i.goToNext();
    CHECK(i.isEnd());
}
