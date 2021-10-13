// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "../API.h"

#include <string_view>

namespace core
{
class Language;
}

namespace server::util
{

// load language from a directory which contains an index.json file and a dictionary (referenced from the json)
SERVER_API core::Language loadLanguageFromDir(std::string_view dir);

} // namespace server::util
