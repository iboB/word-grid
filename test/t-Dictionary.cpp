#include <doctest/doctest.h>

#include <core/Dictionary.hpp>
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
}

TEST_CASE("basic")
{
    Dictionary d;
    std::vector<uint8_t> d1buf(d1, d1 + sizeof(d1));
    d.loadFromUtf8Buffer(chobo::make_memory_view(d1buf));
    auto& words = d.words();
    REQUIRE(words.size() == 4);
    CHECK(words[0] == Word::fromAscii("card"));
    CHECK(words[1] == Word::fromAscii("horse"));
    CHECK(words[2] == Word::fromAscii("mule"));
    CHECK(words[3] == Word::fromAscii("something"));
}

TEST_SUITE_END();
