#include <iostream>
#include <string>
#include <algorithm>

#include <server/Universe.hpp>
#include <server/Game.hpp>
#include <server/Player.hpp>
#include <server/BoardProducer.hpp>

#include <core/Grid.hpp>
#include <core/Word.hpp>
#include <core/Dictionary.hpp>
#include <core/GameData.hpp>
#include <core/Scoring.hpp>
#include <core/Board.hpp>
#include <core/ScoredDictionary.hpp>

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

std::vector<uint8_t> readFile(const char* path)
{
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

class SinglePlayer final : public server::Player
{
public:
    virtual void sendDatas(const std::vector<core::GameData>& datas) override
    {
        for (size_t i=0; i<datas.size(); ++i)
        {
            auto& data = datas[i];
            cout << '(' << i << ") " << data.id << " with " << data.numPlayers << " players\n";
        }

        cout << "Choose game: ";
        size_t n;
        while (true)
        {
            cin >> n;
            if (n < datas.size()) break;
            cout << "No such game. Try again: ";
        }

        string gameId = datas[n].id;
        onChooseGame(std::move(gameId));
    }
    virtual void sendErrorBadId(std::string&& id) override
    {
        cout << "Bad id " << id << '\n';
    }
    virtual void sendAcceptId(std::string&& id) override
    {
        cout << "Id " << id << " accepted\n";
    }
    virtual void sendFatalError(std::string&& message) override
    {
        cout << "FATAL ERROR: " << message << '\n';
    }
    virtual void sendRound(const core::Board& curBoard, core::duration rest, const core::Board* prevBoard) override
    {
        auto pad = [](const core::WordElement& e)
        {
            if (e.length() < 5)
            {
                for (size_t i = 0; i < 5 - e.length(); ++i)
                {
                    cout.put(' ');
                }
            }
            cout << e;
        };

        auto& grid = curBoard.grid();
        for (uint8_t y = 0; y < grid.h(); ++y)
        {
            for (uint8_t x = 0; x < grid.w(); ++x)
            {
                pad(grid.at({ x, y }));
            }
            cout << '\n';
        }

        cout << endl;
        for (auto& w : curBoard.dictionary().words())
        {
            cout << w.word << ' ';
        }

        cout << endl;
    }
    virtual void sendPlayWordResponse(PlayWordResponse r, const core::Word& w, core::score_t score) override
    {
        switch (r)
        {
        case PlayWordResponse::Accept:
            cout << w << ": " << score << " points\n";
            break;
        case PlayWordResponse::AlreadyPlayed:
            cout << w << " was already played\n";
            break;
        case PlayWordResponse::NoSuchWord:
            cout << "No such word " << w << "\n";
            break;
        case PlayWordResponse::Error:
            cout << "Error!\n";
            break;
        }
    }
};

class TestProducer final : public BoardProducer
{
public:
    TestProducer(const Dictionary& d)
        : m_dictionary(d)
    {}

    virtual void addGame(Game&) override {}
    virtual core::Board getBoard(const Game*) override
    {
        std::vector<WordElement> gridElements = {
            WordElement::fromAscii("a"), WordElement::fromAscii("z"), WordElement::fromAscii("b"), WordElement::fromAscii("i"),
            WordElement::fromAscii("f"), WordElement::fromAscii("e"), WordElement::fromAscii("t"), WordElement::fromAscii("m"),
            WordElement::fromAscii("e"), WordElement::fromAscii("e"), WordElement::fromAscii("s"), WordElement::fromAscii("d"),
            WordElement::fromAscii("g"), WordElement::fromAscii("n"), WordElement::fromAscii("r"), WordElement::fromAscii("e"),
        };

        Grid g(4, 4, chobo::make_memory_view(gridElements));
        g.acquireElementOwnership();

        ScoredDictionary sd;
        g.findAllWords(m_dictionary, sd);

        auto scoring = Scoring::flat(13);
        sd.scoreWords(g, scoring);

        return Board(std::move(g), std::move(sd), 60000);
    }
private:
    const Dictionary& m_dictionary;
};

int main()
{
    auto mpath = PlatformUtil::getModulePath();
    auto assetPath = PlatformUtil::getAssetPath(std::move(mpath), "assets");
    auto commonDicPath = assetPath + "/dictionaries/common-en.txt";
    auto commonDicData = readFile(commonDicPath.c_str());
    Dictionary dictionary = Dictionary::fromUtf8Buffer(chobo::make_memory_view(commonDicData));
    cout << "Dictionary words: " << dictionary.words().size() << endl;

    TestProducer producer(dictionary);

    auto game = std::make_unique<Game>("test", 45000, producer);

    Universe universe;
    universe.addGame(std::move(game));

    auto p = std::make_shared<SinglePlayer>();
    p->setUniverse(universe);
    p->onSetId("pipi");

    while (true)
    {
        std::string str;
        cout << "Play: ";
        cin >> str;

        if (str == "qqqq")
        {
            break;
        }

        p->onPlayWord(Word::fromAscii(str.c_str()));
    }

    return 0;
}