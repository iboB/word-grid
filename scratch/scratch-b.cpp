#include <iostream>

#include "PlatformUtil.hpp"

#include <core/LanguageBuilder.hpp>
#include <core/LetterSequenceFromUtf8.hpp>
#include <core/PRNG.hpp>
#include <core/Grid.hpp>
#include <core/GridUtils.hpp>
#include <core/ScoredWord.hpp>

#include <set>

using namespace std;

core::GridElement ab(std::string_view str, core::score_t s)
{
    core::GridElement ret;
    core::LetterSequence_FromUtf8(ret, str);
    ret.setScore(s);
    return ret;
}

std::vector<char> readFile(const char* path)
{
    auto f = fopen(path, "rb");

    if (!f) return {};

    int pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    fseek(f, pos, SEEK_SET);

    std::vector<char> r(fileSize);

    fread(r.data(), 1, fileSize, f);

    fclose(f);
    return r;
}

int main()
{
    core::LanguageBuilder lb;
    lb.setDisplayName("foo");
    lb.setAlphabet({
        ab("a", 2), //
        ab("b", 5), //
        ab("c", 3), //
        ab("d", 3), //
        ab("e", 1), //
        ab("f", 5), //
        ab("g", 4), //
        ab("h", 4), //
        ab("i", 2), //
        ab("j", 9), //
        ab("k", 6), //
        ab("l", 3), //
        ab("m", 4), //
        ab("n", 2), //
        ab("o", 2), //
        ab("p", 4), //
        ab("q", 10), //
        ab("r", 2), //
        ab("s", 2), //
        ab("t", 2), //
        ab("u", 4), //
        ab("v", 6), //
        ab("w", 6), //
        ab("x", 9), //
        ab("y", 5), //
        ab("z", 8), //
    });
    lb.setConversionTable({
        {'-', {}},
        {'\'', {}},
        {241, core::LetterSequence_FromUtf8<core::LetterConversionTarget>("n")}
    });
    lb.setMinWordLength(3);

    auto assetPath = core::PlatformUtil::getAssetPath(core::PlatformUtil::getModulePath(), "assets");
    auto dicPath = assetPath + "/dictionaries/sowpods+12d.txt";
    //auto dicPath = assetPath + "/dictionaries/12dicts.txt";
    auto buf = readFile(dicPath.c_str());
    lb.setDictionaryUtf8Buffer(buf);

    {
        auto warnings = lb.getWarnings();
        for (auto& w : warnings) cout << w << '\n';
    }

    auto el = lb.getLanguage();
    if (!el)
    {
        cerr << "couldn't initialize language\n";
        return 1;
    }
    auto& lang = *el;

    core::Grid g({4, 4});

    auto rseed = core::PRNG::randomDevice();
    cout << "Seeding with: " << rseed << '\n';
    core::PRNG rng(rseed);

    auto addWord = [&](std::string_view str) {
        auto p = core::impl::generateRandomEmptyPath(str.length(), g, rng);
        if (p.empty()) return false;
        for (size_t i = 0; i < str.length(); ++i)
        {
            g[p[i]] = lang.alphabet()[str[i] - 'a'];
        }

        return true;
    };

    //std::vector<std::string_view> seedWords = {"ape", "horse", "cow"};
    //for (auto w : seedWords)
    //{
    //    addWord(w);
    //}
    while (true)
    {
       auto& word = rng.randomElement(lang.commonWordsByLength()).get();
       if (addWord(word.displayString)) cout << "added " << word.displayString << '\n';
       else break;
    }

    auto& ft = lang.alphabetFrequencyTable();
    for (auto& e : g.elements())
    {
       if (e.score() == 0) e = rng.randomElement(ft);
    }

    // std::string_view gridData =
    //     // "gore"
    //     // "aapr"
    //     // "chto"
    //     // "osif";
    //     "nori"
    //     "hgut"
    //     "wahp"
    //     "resy";
    //     // "dona"
    //     // "awer"
    //     // "isef"
    //     // "reso";

    // for (uint32_t i = 0; i < 16; ++i)
    // {
    //     g[i].push_back(gridData[i]);
    // }

    for (uint8_t y = 0; y < g.dim().h; ++y)
    {
        for (uint8_t x = 0; x < g.dim().w; ++x)
        {
            cout << char(g[core::GridCoord{x, y}][0]);
        }
        cout << '\n';
    }

    auto words = core::impl::findAllWordsInGridTmp(g, lang.dictionary());

    std::set<std::string_view> common;
    std::set<std::string_view> uncommon;

    for (auto& w : words) {
        if (w.uncommon) uncommon.insert(w.displayString);
        else common.insert(w.displayString);
    }

    cout << "Found " << (common.size() + uncommon.size()) << " words\n";

    cout << "\n\ncommon (" << common.size() << "): ";
    for (auto& w : common) {
        cout << w << ", ";
    }
    cout << "\n\nuncommon (" << uncommon.size() << "): ";
    for (auto& w : uncommon) {
        cout << w << ", ";
    }

    cout << endl;

    return 0;
}
