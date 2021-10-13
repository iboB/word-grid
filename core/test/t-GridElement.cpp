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
#include <core/WordMatchSequence.hpp>

using namespace core;

TEST_SUITE_BEGIN("GridElement");

WordMatchSequence wms(std::string_view str)
{
    return LetterSequence_FromUtf8<WordMatchSequence>(str);
}


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
    CHECK(e.score == 0);
    CHECK(e.matchesWord(wms("bagavag")));
    CHECK(e.matchesWord(wms("azbzx")));
    CHECK(e.matchesWord(wms("zbza")));
    CHECK(!e.matchesWord(wms("qwerty")));

    auto e2 = e;
    CHECK(e2 == e);
    e2.score = 43;
    CHECK(e2 != e);
    e.score = 43;
    CHECK(e2 == e);

    auto i = e.firstOption();
    CHECK(!i.isEnd());
    auto seq = i.getMatchSequence();
    CHECK(seq.size() == 1);
    CHECK(seq.front() == 'a');
    i.goToNext();
    CHECK(i.isEnd());

    e = ge("x");
    CHECK(e.score == 0);
    CHECK(e.matchesWord(wms("azbzx")));
}

TEST_CASE("Multi")
{
    auto e = ge("xyz");
    CHECK(e.size() == 3);
    CHECK(!e.frontOnly());
    CHECK(!e.backOnly());

    auto i = e.firstOption();
    CHECK(!i.isEnd());
    auto seq = i.getMatchSequence();
    CHECK(seq.size() == 3);
    CHECK(seq.front() == 'x');
    i.goToNext();
    CHECK(i.isEnd());

    CHECK(e.matchesWord(wms("xyz")));
    CHECK(e.matchesWord(wms("axyz")));
    CHECK(e.matchesWord(wms("xyzb")));
    CHECK(e.matchesWord(wms("axyzb")));

    CHECK(!e.matchesWord(wms("yz")));
    CHECK(!e.matchesWord(wms("xy")));
    CHECK(!e.matchesWord(wms("xaybz")));
}

TEST_CASE("Front/Back")
{
    auto e = ge("-ed");
    CHECK(e.size() == 3);
    CHECK(!e.frontOnly());
    CHECK(e.backOnly());
    CHECK(e.score == 0);

    auto i = e.firstOption();
    CHECK(!i.isEnd());
    auto seq = i.getMatchSequence();
    CHECK(seq.size() == 2);
    CHECK(seq.front() == 'e');
    CHECK(seq.back() == 'd');
    i.goToNext();
    CHECK(i.isEnd());

    CHECK(e.matchesWord(wms("ed")));
    CHECK(e.matchesWord(wms("zed")));
    CHECK(!e.matchesWord(wms("e")));
    CHECK(!e.matchesWord(wms("edx")));
    CHECK(!e.matchesWord(wms("zedx")));

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

    CHECK(e.matchesWord(wms("de")));
    CHECK(e.matchesWord(wms("dex")));
    CHECK(!e.matchesWord(wms("d")));
    CHECK(!e.matchesWord(wms("xde")));
    CHECK(!e.matchesWord(wms("zdex")));
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

    CHECK(e.matchesWord(wms("ba")));
    CHECK(e.matchesWord(wms("ab")));
    CHECK(e.matchesWord(wms("qwebrty")));
    CHECK(e.matchesWord(wms("qwearty")));
    CHECK(!e.matchesWord(wms("qwerty")));
}
