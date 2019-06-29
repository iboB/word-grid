#include "Grid.hpp"

namespace core
{

Grid::Grid(size_t w, size_t h, chobo::const_memory_view<GridElement> letters)
    : m_width(w)
    , m_height(h)
{
    if (letters.empty())
    {
        m_ownedElements.resize(w * h);
        acquireElementOwnership();
    }
    else
    {
        assert(letters.size() >= w * h);
        m_elements = letters;
    }
}

Grid::~Grid() = default;

void Grid::acquireElementOwnership()
{
    assert(m_ownedElements.empty() || m_elements.data() != m_ownedElements.data());
    m_ownedElements.resize(m_width * m_height);
    m_ownedElements.assign(m_elements.begin(), m_elements.begin() + m_ownedElements.size());
    m_elements.reset(m_ownedElements.data(), m_ownedElements.size());
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
            auto& elem = at(c);
            if (!elem.matches(pattern, 0)) continue;

            coords.front() = c;

            if (pattern.size() == elem.length())
            {
                return true;
            }

            auto up = chobo::make_memory_view(pattern.data() + elem.length(), pattern.size() - elem.length());

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

            auto& elem = at(c);
            if (!elem.matches(pattern, length)) continue;

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

            if (pattern.size() == elem.length())
            {
                return true;
            }

            auto up = chobo::make_memory_view(pattern.data() + elem.length(), pattern.size() - elem.length());

            if (testPatternR(up, coords, length + 1))
            {
                return true;
            }
        }
    }

    return false;
}

}