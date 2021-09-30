// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Grid.hpp"

namespace core
{

Grid::Grid(size_t w, size_t h)
    : m_width(w)
    , m_height(h)
{
    m_elements.resize(w * h);
}

Grid::~Grid() = default;

Grid::Grid(Grid&&) noexcept = default;
Grid& Grid::operator=(Grid&&) noexcept = default;

} // namespace core
