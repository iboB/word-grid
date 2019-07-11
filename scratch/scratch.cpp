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
};

class TestProducer final : public BoardProducer
{
public:
    TestProducer(Dictionary&& d)
        : m_dictionary(std::move(d))
        , m_scoring(Scoring::flat(13))
        , m_gridElements{
            WordElement::fromAscii("a"), WordElement::fromAscii("z"), WordElement::fromAscii("b"), WordElement::fromAscii("i"),
            WordElement::fromAscii("f"), WordElement::fromAscii("e"), WordElement::fromAscii("t"), WordElement::fromAscii("m"),
            WordElement::fromAscii("e"), WordElement::fromAscii("e"), WordElement::fromAscii("s"), WordElement::fromAscii("d"),
            WordElement::fromAscii("g"), WordElement::fromAscii("n"), WordElement::fromAscii("r"), WordElement::fromAscii("e"),
        }
    {
    }

    virtual void addGame(Game&) override {}
    virtual core::Board getBoard(const Game*) override
    {
        return { {4, 4, chobo::make_memory_view(m_gridElements)}, m_scoring, std::move(m_dictionary) };
    }
private:
    Dictionary m_dictionary;
    Scoring m_scoring;
    std::vector<WordElement> m_gridElements;
};

int main()
{
    auto mpath = PlatformUtil::getModulePath();
    auto assetPath = PlatformUtil::getAssetPath(std::move(mpath), "assets");
    auto commonDicPath = assetPath + "/dictionaries/common-en.txt";
    auto commonDicData = readFile(commonDicPath.c_str());
    Dictionary dictionary = Dictionary::fromUtf8Buffer(chobo::make_memory_view(commonDicData));
    cout << "Dictionary words: " << dictionary.words().size() << endl;

    TestProducer producer(std::move(dictionary));

    auto game = std::make_unique<Game>("test", producer);

    Universe universe;
    universe.addGame(std::move(game));

    auto p = std::make_shared<SinglePlayer>();
    p->setUniverse(universe);
    p->onSetId("pipi");

    return 0;
}