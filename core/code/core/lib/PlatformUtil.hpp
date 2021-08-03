// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <string>
#include <string_view>

namespace core
{

namespace PlatformUtil
{
// returns the full path to the current module
std::string getModulePath();

// starts looking from the provided directory upwards until it discovers a valid subdirectory described by assetDir
// for example
// getAssetPath("/home/someuser/projects/xxx/build/bin", "assets"); will return /home/someuser/projects/xxx/assets if this directory exists
std::string getAssetPath(std::string baseDir, std::string_view assetDir);
};

}
