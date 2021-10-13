// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "PlatformUtil.hpp"

#include <sys/stat.h>
#include <sys/types.h>

#if defined(_WIN32)
#    include <Windows.h>
#else
#    include <dlfcn.h>
#    include <unistd.h>
#endif

namespace server
{
namespace PlatformUtil
{

namespace
{
// local function used to identify the current module
void getAddr() {}
} // namespace

std::string getModulePath()
{
    std::string modulePath;
#if defined(_WIN32)
    HMODULE engine;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)getAddr, &engine);

    char path[_MAX_PATH + _MAX_FNAME + 1];
    GetModuleFileNameA(engine, path, _MAX_PATH + _MAX_FNAME);

    // normalize path
    char* p = path;
    while (*p)
    {
        if (*p == '\\') { *p = '/'; }
        ++p;
    }

    modulePath = path;

#else
    void* p = reinterpret_cast<void*>(getAddr);

    Dl_info info;
    dladdr(p, &info);

    if (*info.dli_fname == '/')
    {
        // absolute path!
        // we're fine
        modulePath = info.dli_fname;
    }
    else
    {
        // we got a relative path :(
        // that means that we're on some crazy posix platform which doesn't
        // return proper dli_fname
        // retrieve the executable path and hope for the best
        char buff[2048];
        auto len = readlink("/proc/self/exe", buff, sizeof(buff) - 1);
        if (len > 0)
        {
            buff[len] = 0;
            modulePath = buff;
        }
    }

#endif

    return modulePath;
}

std::string getAssetPath(std::string baseDir, std::string_view assetDir)
{
    while (true)
    {
        auto slash = baseDir.rfind('/');
        if (slash == std::string::npos)
        {
            baseDir = assetDir;
            break;
        }

        baseDir.erase(slash + 1);

        baseDir += assetDir;

        struct stat info;
        if (stat(baseDir.c_str(), &info) == 0 && (info.st_mode & S_IFDIR)) { break; }

        baseDir.erase(slash);
    }

    return baseDir;
}

} // namespace PlatformUtil
} // namespace server
