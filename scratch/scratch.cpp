#include <iostream>
#include <string>
#include <algorithm>

#include <server/Universe.hpp>
#include <server/Game.hpp>

#include <core/Grid.hpp>
#include <core/Word.hpp>
#include <core/Dictionary.hpp>

#include <core/lib/PlatformUtil.hpp>

namespace core
{
template <size_t N, typename Child>
std::ostream& operator<<(std::ostream& out, const LetterSequence<N, Child>& w)
{
    for (auto l : w)
    {
        out.put(l);
    }
    return out;
}
}

std::vector<uint8_t> readFile(const char* path) {
    auto f = fopen(path, "rb");

    if (!f) return {};

    int pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    fseek(f, pos, SEEK_SET);

    std::vector<uint8_t> r(fileSize);

    fread(r.data(), 1, fileSize, f);

    fclose(f);
    return r;
}

using namespace std;
using namespace core;
using namespace server;

int main()
{
    auto mpath = PlatformUtil::getModulePath();
    auto assetPath = PlatformUtil::getAssetPath(std::move(mpath), "assets");
    auto commonDicPath = assetPath + "/dictionaries/common-en.txt";
    auto commonDicData = readFile(commonDicPath.c_str());
    Dictionary dictionary = Dictionary::fromUtf8Buffer(chobo::make_memory_view(commonDicData));

    auto game = std::make_unique<Game>("test", std::move(dictionary));

    Universe universe;
    universe.addGame(std::move(game));

    return 0;
}