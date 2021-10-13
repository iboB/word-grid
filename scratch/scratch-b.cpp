#include <iostream>

#include <core/BasicBoard.hpp>
#include <core/BoardUtils.hpp>
#include <core/Grid.hpp>
#include <core/GridUtils.hpp>
#include <core/LanguageBuilder.hpp>
#include <core/LetterSequenceFromUtf8.hpp>
#include <core/PRNG.hpp>
#include <core/ScoreUtils.hpp>
#include <core/ScoredWord.hpp>

#include <server/PlatformUtil.hpp>

#include <set>

using namespace std;

core::GridElement ab(std::string_view str, core::score_t s)
{
    core::GridElement ret;
    core::LetterSequence_FromUtf8(ret, str);
    ret.score = s;
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
    lb.setConversionTable({{'-', {}}, {'\'', {}}, {241, core::LetterSequence_FromUtf8<core::LetterConversionTarget>("n")}});
    lb.setMinWordLength(3);

    auto assetPath = server::PlatformUtil::getAssetPath(server::PlatformUtil::getModulePath(), "assets");
    auto dicPath = assetPath + "/dictionaries/sowpods+12d.txt";
    // auto dicPath = assetPath + "/dictionaries/12dicts.txt";
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

    core::BasicBoard bb = {core::Grid({4, 4}), {}};

    // auto rseed = core::PRNG::randomDevice();
    auto rseed = 1998847862;
    cout << "Seeding with: " << rseed << '\n';
    core::PRNG rng(rseed);

    auto addWord = [&](std::string_view str) {
        auto p = core::impl::generateRandomEmptyPath(str.length(), bb.grid, rng);
        if (p.empty()) return false;
        for (size_t i = 0; i < str.length(); ++i) { bb.grid[p[i]] = lang.alphabet()[str[i] - 'a']; }

        return true;
    };

    // int success = -1;
    // for (int i = 0; i < 1000; ++i)
    //{
    //    // std::vector<std::string_view> seedWords = {"ape", "horse", "cow"};
    //    // for (auto w : seedWords)
    //    //{
    //    //    addWord(w);
    //    //}
    //    while (true)
    //    {
    //       auto& word = rng.randomElement(lang.mediumWords()).get();
    //       if (addWord(word.displayString)) cout << "added " << word.displayString << '\n';
    //       else break;
    //    }

    //    auto& ft = lang.alphabetFrequencyTable();
    //    for (auto& e : bb.grid.elements())
    //    {
    //        if (e.empty()) e = rng.randomElement(ft);
    //    }

    //    bb.words = core::impl::findAllWordsInGridTmp(bb.grid, lang.dictionary());

    //    for (auto& w : bb.words) { w.score = core::impl::classicScore(w, bb.grid); }

    //    if (!core::impl::scheckAllCellsUsedTwice(bb))
    //    {
    //        bb.grid.clear();
    //        continue;
    //    }

    //    if (!core::impl::scheckDupWordsSameScore(bb))
    //    {
    //        bb.grid.clear();
    //        cout << "uh-oh\n";
    //        continue;
    //    }

    //    success = i;
    //    break;
    //}

    // if (success == -1)
    //{
    //    cout << "fail\n";
    //    return 0;
    //}

    // cout << "success on iteration " << success << "\n";

    std::string_view gridData =
        // "gore"
        // "aapr"
        // "chto"
        // "osif";
        "nori"
        "hgut"
        "wahp"
        "resy";
    // "dona"
    // "awer"
    // "isef"
    // "reso";

    for (uint32_t i = 0; i < 16; ++i)
    {
        auto c = gridData[i];
        auto& ab = lang.alphabet();
        for (auto& a : ab)
        {
            if (a.front() == c)
            {
                bb.grid[i] = a;
                break;
            }
        }
    }
    bb.words = core::impl::findAllWordsInGridTmp(bb.grid, lang.dictionary());
    for (auto& w : bb.words) { w.score = core::impl::classicScore(w, bb.grid); }

    for (uint8_t y = 0; y < bb.grid.dim().h; ++y)
    {
        for (uint8_t x = 0; x < bb.grid.dim().w; ++x) { cout << char(bb.grid[core::GridCoord{x, y}][0]); }
        cout << '\n';
    }

    itlib::flat_map<std::string_view, core::score_t> common;
    core::score_t commonScore = 0;
    itlib::flat_map<std::string_view, core::score_t> uncommon;
    core::score_t uncommonScore = 0;

    for (auto& w : bb.words)
    {
        if (w.uncommon)
        {
            uncommonScore += w.score;
            uncommon[w.displayString] = w.score;
        }
        else
        {
            commonScore += w.score;
            common[w.displayString] = w.score;
        }
    }

    cout << "Found " << (common.size() + uncommon.size()) << " words. Total score: " << (commonScore + uncommonScore) << "\n";

    cout << "\n\nCommon words: " << common.size() << ". Score: " << commonScore << '\n';
    for (auto& w : common) { cout << w.first << '(' << w.second << "), "; }
    cout << "\n\nUncommon words: " << uncommon.size() << ". Score: " << uncommonScore << '\n';
    for (auto& w : uncommon) { cout << w.first << '(' << w.second << "), "; }

    cout << endl;

    return 0;
}
