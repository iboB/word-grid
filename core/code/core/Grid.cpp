// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Grid.hpp"

#include "Word.hpp"
#include "Dictionary.hpp"
#include "DictionarySearch.hpp"
#include "ScoredDictionary.hpp"

#include <array>

namespace core
{

Grid::Grid(size_t w, size_t h, itlib::const_memory_view<WordElement> elements)
    : m_width(w)
    , m_height(h)
{
    if (elements.empty())
    {
        m_elements.resize(w * h);
    }
    else
    {
        assert(elements.size() >= w * h);
        m_elements.assign(elements.begin(), elements.begin() + w*h);
    }
}

Grid::~Grid() = default;

Grid::Grid(Grid&&) noexcept = default;
Grid& Grid::operator=(Grid&&) noexcept = default;

}
