// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "GridDimensions.hpp"
#include "GridElement.hpp"

#include <itlib/span.hpp>

#include <vector>

namespace core
{

class Grid
{
public:
    explicit Grid(GridDimensions dim)
        : m_dim(dim)
        , m_elements(dim.area())
    {}

    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    Grid(Grid&&) noexcept = default;
    Grid& operator=(Grid&&) noexcept = default;

    const GridDimensions& dim() const { return m_dim; }

    const GridElement& at(const GridCoord& c) const { return m_elements[m_dim.indexOf(c)]; }
    GridElement& at(const GridCoord& c) { return m_elements[m_dim.indexOf(c)]; }
    const GridElement& operator[](const GridCoord& c) const { return at(c); }
    GridElement& operator[](const GridCoord& c) { return at(c); }
    const GridElement& operator[](uint32_t index) const { return m_elements[index]; }
    GridElement& operator[](uint32_t index) { return m_elements[index]; }

    using ElementsVector = std::vector<GridElement>;
    using MutableElementsView = itlib::span<GridElement>;
    const ElementsVector& elements() const { return m_elements; }
    MutableElementsView elements() { return m_elements; }

    using ElementsView = itlib::span<const GridElement>;
    ElementsView row(uint32_t y) const { return itlib::make_span(rowPtr(y), m_dim.w); }
    MutableElementsView row(uint32_t y) { return itlib::make_span(rowPtr(y), m_dim.w); }

    // resets all elements but doesn't affect dimensions
    void clear()
    {
        for (auto& e : m_elements) e.clear();
    }

private:
    const GridElement* rowPtr(uint32_t y) const { return m_elements.data() + m_dim.w * y; }
    GridElement* rowPtr(uint32_t y) { return m_elements.data() + m_dim.w * y; }

    GridDimensions m_dim;
    ElementsVector m_elements;
};

} // namespace core
