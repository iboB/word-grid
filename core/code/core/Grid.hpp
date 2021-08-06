// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
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
#include "GridPath.hpp"

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

    size_t indexOf(const GridCoord& c) const { return m_width * c.y + c.x; }
    GridCoord coordOf(size_t i) const {
        auto dm = std::div(int(i), int(m_width));
        return {uint8_t(dm.quot), uint8_t(dm.rem)};
    }
    const WordElement& at(const GridCoord& c) const { return m_elements[indexOf(c)]; }
    const WordElement& at(size_t index) const { return m_elements[index]; }

    const std::vector<WordElement>& elements() const { return m_elements; }

private:
    size_t m_width = 0, m_height = 0;
    std::vector<WordElement> m_elements;
};

}
