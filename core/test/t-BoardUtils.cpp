// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/BoardUtils.hpp>
#include <core/Dictionary.hpp>
#include <core/Grid.hpp>
#include <core/ScoredWord.hpp>
#include <core/WordMatchSequence.hpp>

#include "g-Grids.hpp"
#include "tu-GridPath.hpp"

using namespace core;
using namespace core::impl;

TEST_SUITE_BEGIN("BoardUtils");

WordMatchSequence wms(std::string_view str)
{
    return LetterSequence_FromUtf8<WordMatchSequence>(str);
}

TEST_CASE("matching basic")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    auto path = testGridPattern(grid, wms("r"));
    CHECK(path.empty());
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("a"));
    REQUIRE(path.size() == 1);
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("dgjnk"));
    CHECK(path.size() == 5);
    CHECK(path == GridPath{{3, 0}, {2, 1}, {1, 2}, {1, 3}, {2, 2}});

    path = testGridPattern(grid, wms("dgjnka"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("aa"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("zz"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("p"));
    CHECK(path.size() == 1);
    CHECK(path[0] == GridCoord{3, 3});
}

TEST_CASE("matching fancy")
{
    // a  b  c    d
    // zy b  beg- h
    // i  j  a/l  l
    // m  n  o    -end
    auto grid = test::Grid_fancy();

    auto path = testGridPattern(grid, wms("dgjnk"));
    CHECK(path.size() == 0);
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("dbeg"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("beg-d"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("begd"));
    CHECK(path.size() == 2);
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("beg"));
    CHECK(path.size() == 1);
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("be"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("oen"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("begbb"));
    CHECK(path.size() == 3);
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("begend"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("bbcc"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("bbc"));
    CHECK(path.size() == 3);
    CHECK(test::isValidGridPath(path, grid));

    path = testGridPattern(grid, wms("endo"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("oend"));
    CHECK(path.size() == 2);

    path = testGridPattern(grid, wms("o-end"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("end"));
    CHECK(path.size() == 1);

    path = testGridPattern(grid, wms("-end"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("beglend"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, wms("begaend"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, wms("zyjllend"));
    CHECK(path.size() == 5);
    CHECK(test::isValidGridPath(path, grid));
}

DictionaryWord dw(std::string_view str)
{
    DictionaryWord ret;
    LetterSequence_FromUtf8(ret.letters, str);
    ret.displayString = str;
    return ret;
}

TEST_CASE("find all basic")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    Dictionary d = {
        dw("zog"),
        dw("afe"), //
        dw("pokl"), //
        dw("abop"),
        dw("jiebcd"), //
        dw("klij"),
        dw("efkl"), //
        dw("jkkl"),
        dw("iijk"),
    };

    auto found = findAllWordsInGrid(grid, d);
    REQUIRE(found.size() == 4);
    CHECK(found[0].word.displayString == "afe");
    CHECK(found[0].path == GridPath{{0, 0}, {1, 1}, {0, 1}});
    CHECK(found[1].word.displayString == "efkl");
    CHECK(found[1].path == GridPath{{0, 1}, {1, 1}, {2, 2}, {3, 2}});
    CHECK(found[2].word.displayString == "jiebcd");
    CHECK(test::isValidGridPath(found[2].path, grid));
    CHECK(found[3].word.displayString == "pokl");
    CHECK(test::isValidGridPath(found[3].path, grid));
}

TEST_CASE("find all fancy")
{
    // a  b  c    d
    // zy b  beg- h
    // i  j  a/l  l
    // m  n  o    -end
    auto grid = test::Grid_fancy();

    Dictionary d = {
        dw("zog"),
        dw("beg"), //
        dw("begh"), //
        dw("begaend"), //
        dw("beglh"), // x2
        dw("zybbeg"),
        dw("zybblend"), //
        dw("byzb"), dw("yza"),
        dw("abbj"), //
        dw("endo"), dw("dhlm"),
        dw("hlo"), // x2
        dw("cba"), // x3
        dw("begln"), //
        dw("end"), //
    };

    auto found = findAllWordsInGrid(grid, d);
    REQUIRE(found.size() == 14);
    auto f = found.begin();
    CHECK(f->word.displayString == "abbj");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "cba");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "cba");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "cba");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "zybblend");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "beg");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "begh");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "begaend");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "beglh");
    CHECK(f->path == GridPath{{2, 1}, {2, 2}, {3, 1}});
    ++f;
    CHECK(f->word.displayString == "begln");
    CHECK(f->path == GridPath{{2, 1}, {2, 2}, {1, 3}});
    ++f;
    CHECK(f->word.displayString == "beglh");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "hlo");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "hlo");
    CHECK(test::isValidGridPath(f->path, grid));
    ++f;
    CHECK(f->word.displayString == "end");
    CHECK(f->path == GridPath{{3, 3}});

    CHECK(++f == found.end());
}
