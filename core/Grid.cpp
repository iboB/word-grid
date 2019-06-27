#include "Grid.h"

namespace core
{

Grid::Grid(size_t w, size_t h, chobo::const_memory_view<letter> letters)
    : m_width(w)
    , m_height(h)
{
    if (letters.empty())
    {
        m_ownedLetters.resize(w * h);
        acquireLetterOwnership();
    }
    else
    {
        assert(letters.size() >= w * h);
        m_letters = letters;
    }
}

Grid::~Grid() = default;

void Grid::acquireLetterOwnership()
{
    assert(m_letters.data() != m_ownedLetters.data());
    m_ownedLetters.resize(m_width * m_height);
    m_ownedLetters.assign(m_letters.begin(), m_letters.begin() + m_ownedLetters.size());
    m_letters.reset(m_ownedLetters.data(), m_ownedLetters.size());
}

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