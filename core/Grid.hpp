#pragma once

#include "Types.hpp"
#include "WordElement.hpp"
#include "GridCoord.hpp"
#include "Dictionary.hpp"

#include <chobo/memory_view.hpp>
#include <vector>
#include <cstdlib>

namespace core
{

class Grid
{
public:
    Grid(size_t w, size_t h, chobo::const_memory_view<WordElement> elements = {});
    ~Grid();

    size_t w() const { return m_width; }
    size_t h() const { return m_height; }

    void acquireElementOwnership();

    // tests a pattern (word)
    // return length in elements if the word is found on the grid
    // supply an output argument with coordinates which will be filled with the pattern coordinates in the grid
    size_t testPattern(chobo::const_memory_view<letter> pattern, chobo::memory_view<GridCoord> coords) const;

    size_t indexOf(const GridCoord& c) const { return m_width * c.y + c.x; }
    GridCoord coordOf(size_t i) const {
        auto dm = std::div(int(i), int(m_width));
        return {uint32_t(dm.quot), uint32_t(dm.rem)};
    }
    const WordElement& at(const GridCoord& c) const { return m_elements[indexOf(c)]; }
    const WordElement& at(size_t index) const { return m_elements[index]; }

    Dictionary findAllWords(const Dictionary& d) const;

private:
    size_t testPatternR(chobo::const_memory_view<letter> pattern, chobo::memory_view<GridCoord>& coords, size_t length) const;

    const size_t m_width = 0, m_height = 0;
    chobo::const_memory_view<WordElement> m_elements;
    std::vector<WordElement> m_ownedElements; // the grid can optionally own the elements, or just serve as a view
};

}