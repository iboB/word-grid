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
babababababababababa
bozb
    )");
    auto l = b.getLanguage();
}
