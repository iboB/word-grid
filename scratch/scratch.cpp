#include <iostream>
#include <string>

#include <core/Grid.hpp>
#include <core/Word.hpp>

using namespace std;
using namespace core;

int main()
{
    // abcd
    // efgh
    // ijkl
    // mnop
    std::vector<WordElement> elements(16);
    for (unsigned i = 0; i < 16; ++i)
    {
        elements[i].push_back('a' + i);
    }

    auto mv = chobo::make_memory_view(elements);
    Grid grid(4, 4, mv);
    grid.acquireElementOwnership();

    vector<GridCoord> coords(50);

    auto word = Word::fromAscii("dgjnka");

    auto b = grid.testPattern(chobo::make_memory_view(word), chobo::make_memory_view(coords));

    if (b)
    {
        for (size_t i = 0; i < word.size(); ++i)
        {
            auto& c = coords[i];
            cout << "(" << c.x << ", " << c.y << ")\n";
        }
    }
    else
    {
        cout << "no :(\n";
    }

    return 0;
}