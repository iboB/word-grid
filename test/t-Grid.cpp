#include <doctest/doctest.h>

#include <core/Grid.hpp>
#include <core/Word.hpp>

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
    vector<WordElement> elements(16);
    for (unsigned i = 0; i < 16; ++i)
    {
        elements[i].push_back('a' + i);
    }

    Grid grid(4, 4, make_memory_view(elements));

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

    // a  b  c    d
    // zy f  beg- h
    // i  j  k    l
    // m  n  o    -end
    elements[4].swap(WordElement::fromAscii("zy"));
    elements[6].swap(WordElement::fromAscii("beg-"));
    elements[15].swap(WordElement::fromAscii("-end"));

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
}

TEST_SUITE_END();
