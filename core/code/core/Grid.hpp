// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "Types.hpp"
#include "WordElement.hpp"
#include "GridCoord.hpp"

#include <itlib/memory_view.hpp>
#include <vector>
#include <cstdlib>

namespace core
{
class Dictionary;
class ScoredDictionary;

class CORE_API Grid
{
public:
    Grid(size_t w, size_t h, itlib::const_memory_view<WordElement> elements = {});
    ~Grid();

    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    Grid(Grid&&) noexcept;
    Grid& operator=(Grid&&) noexcept;

    size_t w() const { return m_width; }
    size_t h() const { return m_height; }

    void acquireElementOwnership();

    // tests a pattern (word)
    // return length in elements if the word is found on the grid or 0 if it's not
    // supply an output argument with coordinates which will be filled with the pattern coordinates in the grid
    size_t testPattern(itlib::const_memory_view<letter_t> pattern, itlib::memory_view<GridCoord> coords) const;

    // test a set of coords
    // bool testPath(itlib::const_memory_view<GridCoord> coords, Word& word) const;

    size_t indexOf(const GridCoord& c) const { return m_width * c.y + c.x; }
    GridCoord coordOf(size_t i) const {
        auto dm = std::div(int(i), int(m_width));
        return {uint8_t(dm.quot), uint8_t(dm.rem)};
    }
    const WordElement& at(const GridCoord& c) const { return m_elements[indexOf(c)]; }
    const WordElement& at(size_t index) const { return m_elements[index]; }

    const itlib::const_memory_view<WordElement>& elements() const { return m_elements; }

    void findAllWords(const Dictionary& d, ScoredDictionary& out) const;

private:
    template <typename Visitor>
    void visitAll(Visitor& v, itlib::memory_view<GridCoord> coords) const;
    template <typename Visitor>
    bool visitAllR(Visitor& v, itlib::memory_view<GridCoord>& coords, size_t length) const;

    size_t m_width = 0, m_height = 0;
    itlib::const_memory_view<WordElement> m_elements;
    std::vector<WordElement> m_ownedElements; // the grid can optionally own the elements, or just serve as a view
};

}
