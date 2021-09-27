// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/Language.hpp>
#include <core/LanguageBuilder.hpp>

TEST_SUITE_BEGIN("Language");

TEST_CASE("Simple")
{
    core::LanguageBuilder b;
    b.setDisplayName("simple");
    b.setAlphabet({{'a', {1}}, {'b', {5}}, {'o', {3}}});
    b.setDictionaryUtf8Buffer(u8R"(
        abob
        boa
        bbb
        b
        obabo
        boa
        babababababababababa
        bozb
    )");
    auto l = b.getLanguage();

    auto& dic = l.dictionary();
    REQUIRE(dic.size() == 5);

    auto abob = dic.front();
    CHECK(abob.displayString == "abob");
    auto abob2 = l.getWordMatchSequenceFromUtf8("abob");
    REQUIRE(abob2.has_value());
    CHECK(abob.letters == *abob2);

    core::WordMatchSequence fb;
    CHECK(dic[1].displayString == "bbb");
    CHECK(dic[1].letters == l.getWordMatchSequenceFromUtf8("bbb").value_or(fb));
    CHECK(dic[2].displayString == "boa");
    CHECK(dic[3].displayString == "bozb");
    CHECK(dic[4].displayString == "obabo");
}
