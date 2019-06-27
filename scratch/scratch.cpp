#include <iostream>
#include <string>

#include <core/Grid.h>

using namespace std;

int main()
{
    // abcd
    // efgh
    // ijkl
    std::vector<core::letter> letters(16);
    for (unsigned i = 0; i < 16; ++i)
    {
        letters[i] = 'a' + i;
    }

    auto mv = chobo::make_memory_view(letters);
    core::Grid grid(4, 4, mv);
    grid.acquireLetterOwnership();

    vector<core::Grid::Coord> coords(50);

    string sword = "abeje";
    const vector<core::letter> word(sword.begin(), sword.end());

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
        cout << "no :(\b";
    }

    return 0;
}