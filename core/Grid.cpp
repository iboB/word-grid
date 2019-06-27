#include "Grid.h"

namespace core
{

Grid::Grid(size_t w, size_t h)
    : m_width(w)
    , m_height(h)
    , m_letters(w * h)
{}

Grid::~Grid() = default;


bool Grid::testPattern(chobo::const_memory_view<letter> pattern, chobo::memory_view<Grid::Coord> coords) const
{
    assert(coords.size() >= pattern.size());
    if (pattern.empty()) return true;

    Coord c;
    for (c.y=0; c.y<m_height; ++c.y)
    {
        for (c.x=0; c.x<m_width; ++c.x)
        {
            if (at(c) != pattern.front()) continue;

            coords.front() = c;

            if (pattern.size() == 1)
            {
                return true;
            }

            auto up = chobo::make_memory_view(pattern.data() + 1, pattern.size() - 1);

            if (testPatternR(up, coords, 1))
            {
                return true;
            }
        }
    }

    return false;
}

bool Grid::testPatternR(chobo::const_memory_view<letter> pattern, chobo::memory_view<Grid::Coord>& coords, size_t length) const
{
    const Coord& base = coords[length - 1];

    for (int y=-1; y<=1; ++y)
    {
        Coord c;
        c.y = base.y + y;
        if (c.y >= m_height) continue;
        for (int x=-1; x<=1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = base.x+x;
            if (c.x >= m_width) continue;

            if (at(c) != pattern.front()) continue;

            bool alreadyUsed = [&c, &coords, length]()
            {
                for (size_t i=0; i<length; ++i)
                {
                    if (coords[i] == c) return true;
                }
                return false;
            }();

            if (alreadyUsed) continue;

            coords[length] = c;

            if (pattern.size() == 1)
            {
                return true;
            }

            auto up = chobo::make_memory_view(pattern.data() + 1, pattern.size() - 1);

            if (testPatternR(up, coords, length + 1))
            {
                return true;
            }
        }
    }

    return false;
}

}