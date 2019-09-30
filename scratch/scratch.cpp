#include <iostream>
#include <string>
#include <algorithm>
#include <thread>

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
    enum Phase
    {
        Phase_New,
        Phase_IdChosen,
        Phase_HasId,
        Phase_HasGameDatas,
        Phase_GameRequested,
        Phase_HasGame,
    };

    Phase phase() const { return m_phase; }

    void chooseId(std::string&& id)
    {
        m_phase = Phase_IdChosen;
        onSetId(std::move(id));
    }

    void chooseGame(size_t n)
    {
        if (n >= m_gameDatas.size()) {
            cout << "No such game. Try again: ";
            return;
        }

        m_phase = Phase_GameRequested;
        string gameId = m_gameDatas[n].id;
        onChooseGame(std::move(gameId));
    }

    void playWord(const std::string& word)
    {
        onPlayWord(Word::fromAscii(word.c_str()));
    }
private:
    std::vector<core::GameData> m_gameDatas;

    virtual void sendDatas(const std::vector<core::GameData>& datas) override
    {
        m_phase = Phase_HasGameDatas;
        for (size_t i=0; i<datas.size(); ++i)
        {
            auto& data = datas[i];
            cout << '(' << i << ") " << data.id << " with " << data.numPlayers << " players\n";
        }

        m_gameDatas = datas;
    }
    virtual void sendErrorBadId(std::string&& id) override
    {
        m_phase = Phase_New;
        cout << "Bad id " << id << '\n';
    }
    virtual void sendAcceptId(std::string&& id) override
    {
        m_phase = Phase_HasId;
        cout << "Id " << id << " accepted\n";
    }
    virtual void sendFatalError(std::string&& message) override
    {
        if (m_phase != Phase_New) m_phase = Phase_HasId;
        cout << "FATAL ERROR: " << message << '\n';
    }
    virtual void sendRound(const core::Board& curBoard, core::duration /*rest*/, const core::Board* /*prevBoard*/) override
    {
        m_phase = Phase_HasGame;
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

    Phase m_phase = Phase_New;
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
            WordElement::fromAscii("o"), WordElement::fromAscii("p"), WordElement::fromAscii("w"), WordElement::fromAscii("g"),
            WordElement::fromAscii("t"), WordElement::fromAscii("s"), WordElement::fromAscii("-y"), WordElement::fromAscii("e"),
            WordElement::fromAscii("d-"), WordElement::fromAscii("i"), WordElement::fromAscii("t"), WordElement::fromAscii("r"),
            WordElement::fromAscii("e"), WordElement::fromAscii("n"), WordElement::fromAscii("s"), WordElement::fromAscii("e"),
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
    //auto commonDicPath = assetPath + "/dictionaries/words_alpha.txt";
    auto commonDicData = readFile(commonDicPath.c_str());
    Dictionary dictionary = Dictionary::fromUtf8Buffer(chobo::make_memory_view(commonDicData));
    cout << "Dictionary words: " << dictionary.words().size() << endl;

    TestProducer producer(dictionary);

    auto game = std::make_unique<Game>("test", 45000, producer);

    Universe universe;
    universe.addGame(std::move(game));

    auto p = std::make_shared<SinglePlayer>();
    p->setUniverse(universe);
    universe.onNewPlayer(p);

    while (true)
    {
        switch(p->phase()) {
        case SinglePlayer::Phase_New:
        {
            std::string id;
            cout << "choose id: ";
            cin >> id;
            p->chooseId(std::move(id));
        }
        break;
        case SinglePlayer::Phase_HasGameDatas:
        {
            cout << "Choose game: ";
            size_t n;
            cin >> n;

            p->chooseGame(n);
        }
        break;
        case SinglePlayer::Phase_HasGame:
        {
            std::string word;
            cout << "play: ";
            cin >> word;
            if (word == "qqq")
            {
                return 0;
            }
            p->playWord(word);
        }
        break;
        case SinglePlayer::Phase_HasId:
        case SinglePlayer::Phase_IdChosen:
        case SinglePlayer::Phase_GameRequested:
            std::this_thread::yield();
        break;
        }
    }

    return 0;
}