#include <iostream>
#include <string>
#include <algorithm>

#include <core/Grid.hpp>
#include <core/Word.hpp>
#include <core/Dictionary.hpp>

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

vector<WordElement> elements = {
    WordElement::fromAscii("r"), WordElement::fromAscii("t"), WordElement::fromAscii("e"), WordElement::fromAscii("t"),
    WordElement::fromAscii("h"), WordElement::fromAscii("o"), WordElement::fromAscii("d"), WordElement::fromAscii("e"),
    WordElement::fromAscii("o"), WordElement::fromAscii("e"), WordElement::fromAscii("a"), WordElement::fromAscii("s"),
    WordElement::fromAscii("e"), WordElement::fromAscii("r"), WordElement::fromAscii("t"), WordElement::fromAscii("s"),
};

int main()
{
    auto buf = readFile("words_alpha.txt");
    auto d = Dictionary::fromUtf8Buffer(chobo::make_memory_view(buf));

    cout << "dic" << endl;
    Grid grid(4, 4, make_memory_view(elements));

    auto d2 = grid.findAllWords(d);
    cout << "find" << endl;

    auto copy = d2.words();
    std::sort(copy.begin(), copy.end(), [](const Word& a, const Word& b) { return a.length() > b.length(); });

    for (auto& w : copy)
    {
        cout << w << ' ';
    }
    cout << endl;

    return 0;
}