#include <iostream>

#include <core/BasicBoard.hpp>
#include <core/BoardUtils.hpp>
#include <core/Grid.hpp>
#include <core/GridUtils.hpp>
#include <core/Language.hpp>
#include <core/PRNG.hpp>
#include <core/ScoreUtils.hpp>
#include <core/ScoredWord.hpp>

#include <server/PlatformUtil.hpp>
#include <server/util/LoadLanguageFromDir.hpp>

#include <set>

using namespace std;

int main()
{
    auto assetPath = server::PlatformUtil::getAssetPath(server::PlatformUtil::getModulePath(), "assets");
    auto engPath = assetPath + "/languages/english";

    auto lang = server::util::loadLanguageFromDir(engPath);

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
        "gore"
        "aapr"
        "chto"
        "osif";
        //"nori"
        //"hgut"
        //"wahp"
        //"resy";
        //"dona"
        //"awer"
        //"isef"
        //"reso";

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
