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

core::WordMatchSequence wms(std::string_view str)
{
    return core::LetterSequence_FromUtf8<core::WordMatchSequence>(str);
}

core::GridElement ab(std::string_view str, core::score_t s)
{
    core::GridElement ret;
    core::LetterSequence_FromUtf8(ret, str);
    ret.setScore(s);
    return ret;
}

TEST_CASE("Simple")
{
    core::LanguageBuilder b;
    CHECK(b.missingRequiredFields().all());
    b.setDisplayName("simple")
        .setMinWordLength(3)
        .setConversionTable({
            {'-', {}},
            {'z', core::LetterSequence_FromUtf8<core::LetterConversionTarget>("cc")},
        })
        .setDictionaryUtf8Buffer(
            u8R"(
            abob
            boa
            bbb
            b
            oBaBo
            boa
            babababababababababa
            bozb
            ooo-aaa
        )")
        .setMinScore(213)
        .setMaxScore(3050)
        .setAlphabet({
            ab("a", 1),
            ab("b", 3),
            ab("c", 2),
            ab(" ", 0),
            ab("e", -1),
            ab("d", 4),
            ab("z", 5),
        })
        .setSpecials({});

    CHECK(b.missingRequiredFields().none());
    auto el = b.getLanguage();
    REQUIRE(el.has_value());

    auto& l = *el;
    CHECK(l.displayName() == "simple");
    CHECK(l.minScore() == 213);
    CHECK(l.maxScore() == 3050);

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

    auto& abc = l.alphabet();
    REQUIRE(abc.size() == 7);
    CHECK(abc[0].size() == 1);
    CHECK(abc[0][0] == 'a');
    CHECK(abc[0].score() == 1);
    CHECK(abc[3].letterSequence() == wms(" "));
    CHECK(abc[3].score() == 0);

    auto& fq = l.alphabetFrequencyTable();

    // reuse GridElement to but add expected counts in score
    core::Alphabet counts = {
        ab("a", 60),
        ab("b", 20),
        ab("c", 30),
        ab(" ", 12),
        ab("e", 10),
        ab("d", 15),
        ab("z", 12),
    };
    auto sum = 0;
    for (auto& c : counts) sum += c.score();
    REQUIRE(fq.size() == sum);
    auto fi = fq.begin();
    auto hits = 0;
    for (auto& c : counts)
    {
        for (int i = 0; i < c.score(); ++i)
        {
            hits += c.letterSequence() == fi->get().letterSequence();
            ++fi;
        }
    }
    CHECK(hits == sum);
}
