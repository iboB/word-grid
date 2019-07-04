#pragma once

#include <string>

namespace core
{

namespace PlatformUtil
{
// returns the full path to the current module
std::string getModulePath();

// starts looking from the current directory upwards until it discovers a valid subdirectory described by assetDir
// for example
// getAssetPath("/home/someuser/projects/xxx/build/bin", "assets"); will return /home/someuser/projects/xxx/assets if this directory exists
std::string getAssetPath(std::string baseDir, const std::string& assetDir);
};

}