// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/DictionarySearch.hpp>
#include <core/LetterSequenceFromUtf8.hpp>

using namespace core;

TEST_SUITE_BEGIN("DictionarySearch");

void add(Dictionary& d, std::string_view str) {
    DictionaryWord w;
    w.displayString = str;
    LetterSequence_FromUtf8(w.letters, str);
    d.insert(std::move(w));
}

TEST_CASE("test")
{
    Dictionary d;
    add(d, "asd");
    add(d, "asdd");
    add(d, "asdf");
    add(d, "asdz");
    add(d, "asddd");

    DictionarySearch ds(d);
    CHECK(ds.range().begin == d.begin());
    CHECK(ds.range().end == d.end());

    auto result = ds.push('b');
    CHECK(result == DictionarySearch::Result::None);
    REQUIRE(ds.size() == 1);
    CHECK(ds.range().begin == ds.range().end);
    ds.pop();

    result = ds.push('a');
    CHECK(result == DictionarySearch::Result::Partial);
    REQUIRE(ds.size() == 1);
    CHECK(ds.range().begin == d.begin());
    CHECK(ds.range().end == d.end());

    result = ds.push('s');
    CHECK(result == DictionarySearch::Result::Partial);
    REQUIRE(ds.size() == 2);
    CHECK(ds.range().begin == d.begin());
    CHECK(ds.range().end == d.end());

    result = ds.push('d');
    CHECK(result == DictionarySearch::Result::Exact);
    REQUIRE(ds.size() == 3);
    CHECK(ds.range().begin == d.begin());
    CHECK(ds.range().end == d.end());

    result = ds.push('d');
    CHECK(result == DictionarySearch::Result::Exact);
    REQUIRE(ds.size() == 4);
    CHECK(ds.range().end - ds.range().begin == 2);

    result = ds.push('d');
    CHECK(result == DictionarySearch::Result::Exact);
    REQUIRE(ds.size() == 5);
    CHECK(ds.range().end - ds.range().begin == 1);

    result = ds.push('d');
    CHECK(result == DictionarySearch::Result::None);
}

TEST_CASE("overflow")
{
    Dictionary d;
    DictionarySearch ds(d);
    for (int i = 0; i < 123; ++i) ds.push(i);

    CHECK(ds.size() == 123);
    CHECK(ds.range().begin == ds.range().end);

    CHECK(ds.push('x') == DictionarySearch::Result::None);
}