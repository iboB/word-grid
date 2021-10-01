// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "GridCoord.hpp"
#include "GridElement.hpp"

#include <itlib/memory_view.hpp>

#include <cstdlib>
#include <vector>

namespace core
{

class Grid
{
public:
    Grid(size_t w, size_t h)
        : m_width(w)
        , m_height(h)
        , m_elements(w* h)
    {}

    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    Grid(Grid&&) noexcept = default;
    Grid& operator=(Grid&&) noexcept = default;

    size_t w() const { return m_width; }
    size_t h() const { return m_height; }

    size_t indexOf(const GridCoord& c) const { return m_width * c.y + c.x; }
    GridCoord coordOf(size_t i) const
    {
        auto dm = std::div(int(i), int(m_width));
        return {uint8_t(dm.rem), uint8_t(dm.quot)};
    }
    const GridElement& operator[](const GridCoord& c) const { return m_elements[indexOf(c)]; }
    GridElement& operator[](const GridCoord& c) { return m_elements[indexOf(c)]; }
    const GridElement& operator[](size_t index) const { return m_elements[index]; }
    GridElement& operator[](size_t index) { return m_elements[index]; }

    using ElementsVector = std::vector<GridElement>;
    using MutableElementsView = itlib::memory_view<GridElement>;
    const ElementsVector& elements() const { return m_elements; }
    MutableElementsView elements() { return itlib::make_memory_view(m_elements); }

    using ElementsView = itlib::const_memory_view<GridElement>;
    ElementsView row(size_t y) const { return itlib::make_memory_view(rowPtr(y), m_width); }
    MutableElementsView row(size_t y) { return itlib::make_memory_view(rowPtr(y), m_width); }

private:
    const GridElement* rowPtr(size_t y) const { return m_elements.data() + m_width * y; }
    GridElement* rowPtr(size_t y) { return m_elements.data() + m_width * y; }

    size_t m_width = 0, m_height = 0;
    ElementsVector m_elements;
};

} // namespace core
