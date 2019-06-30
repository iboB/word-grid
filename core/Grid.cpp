#include "Grid.hpp"
#include "Word.hpp"
#include "DictionarySearch.hpp"

namespace core
{

Grid::Grid(size_t w, size_t h, chobo::const_memory_view<WordElement> letters)
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

size_t Grid::testPattern(chobo::const_memory_view<letter> pattern, chobo::memory_view<GridCoord> coords) const
{
    assert(coords.size() >= pattern.size());
    if (pattern.empty()) return 0;

    GridCoord c;
    for (c.y=0; c.y<m_height; ++c.y)
    {
        for (c.x=0; c.x<m_width; ++c.x)
        {
            auto& elem = at(c);
            if (!elem.matches(pattern)) continue;

            coords.front() = c;

            const auto matchLength = elem.matchLength();
            if (pattern.size() == matchLength)
            {
                return 1;
            }

            if (elem.backOnly())
            {
                return 0;
            }

            auto up = chobo::make_memory_view(pattern.data() + matchLength, pattern.size() - matchLength);

            if (auto length = testPatternR(up, coords, 1))
            {
                return length;
            }
        }
    }

    return 0;
}

size_t Grid::testPatternR(chobo::const_memory_view<letter> pattern, chobo::memory_view<GridCoord>& coords, size_t length) const
{
    // skip hyphens
    if (pattern.front() == '-')
    {
        if (pattern.size() == 1) return 0; // ends with hyphen?
        pattern = chobo::make_memory_view(pattern.data() + 1, pattern.size() - 1);
    }

    const auto& base = coords[length - 1];

    for (int y=-1; y<=1; ++y)
    {
        GridCoord c;
        c.y = base.y + y;
        if (c.y >= m_height) continue;
        for (int x=-1; x<=1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = base.x+x;
            if (c.x >= m_width) continue;

            auto& elem = at(c);
            if (elem.frontOnly()) continue;
            if (!elem.matches(pattern)) continue;

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

            const auto matchLength = elem.matchLength();
            if (pattern.size() == matchLength)
            {
                return length + 1;
            }

            if (elem.backOnly())
            {
                return 0;
            }

            auto up = chobo::make_memory_view(pattern.data() + matchLength, pattern.size() - matchLength);

            if (auto l = testPatternR(up, coords, length + 1))
            {
                return l;
            }
        }
    }

    return 0;
}

Dictionary Grid::findAllWords(const Dictionary& d) const
{
    DictionarySearch search;
    return Dictionary::fromVector({});
}

}