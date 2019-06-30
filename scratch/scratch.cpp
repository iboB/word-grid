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
arc
amoeba
amphore
bee
baz
foo
fathom
)d1c";

int main()
{
    auto d = Dictionary::fromUtf8Buffer(chobo::make_memory_view(d1, sizeof(d1)));

    auto& words = d.words();

    for (auto& w : words) cout << w << ' ';
    cout << endl;

    auto a1 = std::lower_bound(words.begin(), words.end(), Word::fromAscii("az"));
    if (a1 == words.end())
    {
        cout << "End\n";
    }
    else
    {
        cout << *a1 << endl;
    }

    return 0;
}