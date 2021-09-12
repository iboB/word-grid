// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include <vector>
#include <string_view>

namespace core
{

struct DictionaryWord;

class CORE_API Dictionary
{
    // TODO: add substitution rules
public:
    Dictionary(std::vector<char> utf8Buffer);
    ~Dictionary();

    Dictionary(Dictionary&&) noexcept;
    Dictionary& operator=(Dictionary&&) noexcept;

    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

private:
    void tryAddWord(std::string_view utf8Word);

    std::vector<DictionaryWord> m_words;
    std::vector<char> m_utf8Buffer;
};

}
