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

using namespace std;
using namespace core;

const uint8_t d1[] = R"d1c(
abcc
abfk
aefk
hjnp
klpo
efgh
mnad
zoaj
asdz
mango
)d1c";

int main()
{
    auto d = Dictionary::fromUtf8Buffer(chobo::make_memory_view(d1, sizeof(d1)));

    // abcd
    // efgh
    // ijkl
    // mnop
    vector<WordElement> elements(16);
    for (unsigned i = 0; i < 16; ++i)
    {
        elements[i].push_back('a' + i);
    }
    Grid grid(4, 4, make_memory_view(elements));

    auto d2 = grid.findAllWords(d);

    for (auto& w : d2.words())
    {
        cout << w << endl;
    }

    return 0;
}