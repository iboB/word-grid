// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/Dictionary.hpp>
#include <core/DictionarySearch.hpp>
#include <core/Word.hpp>

using namespace core;

TEST_SUITE_BEGIN("Dictionary");

namespace
{
const char d1[] = R"d1c(
horse
a
mule
card
superextralongwordmaaan
something
)d1c";

const uint8_t d2[] = R"d1c(
asd
asdd
asdf
asdz
asddd
)d1c";
}

TEST_CASE("basic")
{
    std::vector<uint8_t> d1buf(d1, d1 + sizeof(d1));
    auto d = Dictionary::fromUtf8Buffer(chobo::make_memory_view(d1buf));
    auto& words = d.words();
    REQUIRE(words.size() == 4);
    CHECK(words[0] == Word::fromAscii("card"));
    CHECK(words[1] == Word::fromAscii("horse"));
    CHECK(words[2] == Word::fromAscii("mule"));
    CHECK(words[3] == Word::fromAscii("something"));

    CHECK(d.hasWord(Word::fromAscii("card")));
    CHECK(d.hasWord(Word::fromAscii("mule")));
    CHECK(d.hasWord(Word::fromAscii("something")));
    CHECK(d.hasWord(Word::fromAscii("horse")));
    CHECK(!d.hasWord(Word::fromAscii("a")));
    CHECK(!d.hasWord(Word::fromAscii("cardd")));
}

TEST_CASE("search")
{
    auto d = Dictionary::fromUtf8Buffer(chobo::make_memory_view(d2, sizeof(d2)));
    DictionarySearch ds;
    auto result = d.search(ds, 'b');
    CHECK(result == Dictionary::SearchResult::None);
    REQUIRE(ds.length() == 1);
    ds.pop();

    result = d.search(ds, 'a');
    CHECK(result == Dictionary::SearchResult::Partial);
    REQUIRE(ds.length() == 1);
    REQUIRE(ds.ranges().size() == 1);
    CHECK(ds.ranges().back().begin == d.words().begin());
    CHECK(ds.ranges().back().end == d.words().end());

    result = d.search(ds, 's');
    CHECK(result == Dictionary::SearchResult::Partial);
    REQUIRE(ds.length() == 2);
    REQUIRE(ds.ranges().size() == 2);
    CHECK(ds.ranges().back().begin == d.words().begin());
    CHECK(ds.ranges().back().end == d.words().end());

    result = d.search(ds, 'd');
    CHECK(result == Dictionary::SearchResult::Exact);
    REQUIRE(ds.length() == 3);
    REQUIRE(ds.ranges().size() == 3);
    CHECK(ds.ranges().back().begin == d.words().begin());
    CHECK(ds.ranges().back().end == d.words().end());

    result = d.search(ds, 'd');
    CHECK(result == Dictionary::SearchResult::Exact);
    REQUIRE(ds.length() == 4);
    REQUIRE(ds.ranges().size() == 4);
    CHECK(ds.ranges().back().end - ds.ranges().back().begin == 2);

    result = d.search(ds, 'd');
    CHECK(result == Dictionary::SearchResult::Exact);
    REQUIRE(ds.length() == 5);
    REQUIRE(ds.ranges().size() == 5);
    CHECK(ds.ranges().back().end - ds.ranges().back().begin == 1);

    result = d.search(ds, 'd');
    CHECK(result == Dictionary::SearchResult::None);
}

TEST_SUITE_END();
