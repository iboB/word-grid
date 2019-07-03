#include <doctest/doctest.h>

#include <core/Grid.hpp>
#include <core/Word.hpp>

#include "g-Grids.hpp"

using namespace core;
using namespace std;
using namespace chobo;

TEST_SUITE_BEGIN("Grid");

TEST_CASE("matching")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    vector<GridCoord> coordsData(50);
    auto coords = make_memory_view(coordsData);
    auto wordData = Word::fromAscii("dgjnk");
    auto word = make_memory_view(wordData);

    auto len = grid.testPattern(word, coords);
    CHECK(len == 5);
    CHECK(coords[0] == GridCoord{ 3, 0 });
    CHECK(coords[1] == GridCoord{ 2, 1 });
    CHECK(coords[2] == GridCoord{ 1, 2 });
    CHECK(coords[3] == GridCoord{ 1, 3 });
    CHECK(coords[4] == GridCoord{ 2, 2 });

    wordData = Word::fromAscii("dgjnka");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("zz");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("p");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 1);
    CHECK(coords[0] == GridCoord{ 3, 3 });

    grid = test::Grid_fancy();

    wordData = Word::fromAscii("dgjnk");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("dbeg-");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("dbeg");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("begd");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 2);

    wordData = Word::fromAscii("beg");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 1);

    wordData = Word::fromAscii("begfzy");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 3);

    wordData = Word::fromAscii("endo");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("oend");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 2);

    wordData = Word::fromAscii("o-end");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 2);

    wordData = Word::fromAscii("end");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 1);

    wordData = Word::fromAscii("-end");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 0);

    wordData = Word::fromAscii("begbzyjkend");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 6);

    wordData = Word::fromAscii("begbzy-jkend");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    CHECK(len == 6);
}

TEST_SUITE_END();
