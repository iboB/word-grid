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
#include <core/LetterSequenceFromUtf8.hpp>

TEST_SUITE_BEGIN("Language");

core::WordMatchSequence wms(std::string_view str) {
    return core::LetterSequence_FromUtf8<core::WordMatchSequence>(str);
}

TEST_CASE("Simple")
{
    core::LanguageBuilder b;
    b.setDisplayName("simple");
    b.setConversionTable({
        {'-', {}},
        {'z', core::LetterSequence_FromUtf8<core::LetterConversionTarget>("cc")},
    });
    b.setDictionaryUtf8Buffer(u8R"(
        abob
        boa
        bbb
        b
        oBaBo
        boa
        babababababababababa
        bozb
        ooo-aaa
    )");
    auto l = b.getLanguage();

    auto& dic = l.dictionary().container();
    REQUIRE(dic.size() == 6);

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
    auto bozbLetters = dic[3].letters;
    CHECK(bozbLetters.size() == 5);
    CHECK(bozbLetters == wms("boccb"));
    CHECK(bozbLetters == l.getWordMatchSequenceFromUtf8("bozb").value_or(fb));
    CHECK(bozbLetters == l.getWordMatchSequenceFromUtf8("boccb").value_or(fb));
    CHECK(dic[4].displayString == "oBaBo"); // presiserp of unitinu
    auto obaboLetters = dic[4].letters;
    CHECK(obaboLetters[1] == 'b');
    CHECK(obaboLetters == wms("obabo"));
    CHECK(obaboLetters == l.getWordMatchSequenceFromUtf8("ObAbO").value_or(fb));
    auto ooaaLetters = dic[5].letters;
    CHECK(ooaaLetters.size() == 6);
    CHECK(ooaaLetters == wms("oooaaa"));
    CHECK(ooaaLetters == l.getWordMatchSequenceFromUtf8("o-ooaa-a").value_or(fb));
    CHECK(ooaaLetters == l.getWordMatchSequenceFromUtf8("oooaaa").value_or(fb));
}
