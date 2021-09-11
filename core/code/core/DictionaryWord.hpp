// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "WordMatchSequence.hpp"

#include <string_view>

namespace core
{

class DictionaryWord
{
public:

private:
    WordMatchSequence m_letters;
    std::string_view m_displayString;
}

}
