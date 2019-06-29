#pragma once

#include "Types.hpp"
#include "GridElement.hpp"

#include <chobo/memory_view.hpp>
#include <vector>
#include <cstdlib>

namespace core
{

class Grid
{
public:
    Grid(size_t w, size_t h, chobo::const_memory_view<GridElement> elements = {});
    ~Grid();

    size_t w() const { return m_width; }
    size_t h() const { return m_height; }

    void acquireElementOwnership();

    struct Coord
    {
        uint32_t x;
        uint32_t y;
    };

    // tests a pattern (word)
    // return length in elements if the word is found on the grid
    // supply an output argument with coordinates which will be filled with the pattern coordinates in the grid
    size_t testPattern(chobo::const_memory_view<letter> pattern, chobo::memory_view<Coord> coords) const;

    size_t indexOf(const Coord& c) const { return m_width * c.y + c.x; }
    Coord coordOf(size_t i) const {
        auto dm = std::div(int(i), int(m_width));
        return {uint32_t(dm.quot), uint32_t(dm.rem)};
    }
    const GridElement& at(const Coord& c) const { return m_elements[indexOf(c)]; }
    const GridElement& at(size_t index) const { return m_elements[index]; }

private:
    size_t testPatternR(chobo::const_memory_view<letter> pattern, chobo::memory_view<Coord>& coords, size_t length) const;

    const size_t m_width = 0, m_height = 0;
    chobo::const_memory_view<GridElement> m_elements;
    std::vector<GridElement> m_ownedElements; // the grid can optionally own the elements, or just serve as a view
};

inline bool operator==(const Grid::Coord& a, const Grid::Coord& b)
{
    return a.x == b.x && a.y == b.y;
}

}