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

template <typename Visitor>
void Grid::visitAll(Visitor& v, chobo::memory_view<GridCoord> coords) const
{
    GridCoord c;
    for (c.y = 0; c.y < m_height; ++c.y)
    {
        for (c.x = 0; c.x < m_width; ++c.x)
        {
            if (!v.push(this->at(c))) continue;

            coords.front() = c;

            if (v.done()) return;

            if (this->visitAllR(v, coords, 1))
            {
                return;
            }

            v.pop();
        }
    }
}

template <typename Visitor>
bool Grid::visitAllR(Visitor& v, chobo::memory_view<GridCoord>& coords, size_t length) const
{
    const auto& base = coords[length - 1];

    for (int y = -1; y <= 1; ++y)
    {
        GridCoord c;
        c.y = base.y + y;
        if (c.y >= m_height) continue;
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = base.x + x;
            if (c.x >= m_width) continue;

            bool alreadyUsed = [&c, &coords, length]()
            {
                for (size_t i = 0; i < length; ++i)
                {
                    if (coords[i] == c) return true;
                }
                return false;
            }();

            if (alreadyUsed) continue;

            if (!v.push(this->at(c))) continue;

            coords[length] = c;

            if (v.done()) return true;

            if (visitAllR(v, coords, length + 1))
            {
                return true;
            }

            v.pop();
        }
    }

    return false;
}

namespace
{
struct TestPatterVisitor
{
    chobo::static_vector<chobo::const_memory_view<letter>, WordTraits::Max_Length + 1> top;
    bool push(const WordElement& elem)
    {
        auto& pattern = top.back();

        // skip hyphens
        if (pattern.front() == '-' && top.size() > 1)
        {
            if (pattern.size() == 1) return false; // ends with hyphen?
            pattern = chobo::make_memory_view(pattern.data() + 1, pattern.size() - 1);
        }

        if (!elem.matches(pattern)) return false;
        if (top.size() != 1 && elem.frontOnly()) return false;


        const auto matchLength = elem.matchLength();

        if (top.size() == 1 && elem.backOnly())
        {
            if (pattern.size() == matchLength)
            {
                top.emplace_back();
            }
            else
            {
                top.back() = {};
            }
        }
        else
        {
            top.emplace_back(chobo::make_memory_view(pattern.data() + matchLength, pattern.size() - matchLength));
        }

        return true;
    }

    bool done() const
    {
        return top.back().empty();
    }

    void pop()
    {
        assert(!top.empty());
        top.pop_back();
    }
};
}

size_t Grid::testPattern(chobo::const_memory_view<letter> pattern, chobo::memory_view<GridCoord> coords) const
{
    assert(coords.size() >= pattern.size());
    TestPatterVisitor v = { {pattern} };
    visitAll(v, coords);
    return v.top.size() - 1;
}

Dictionary Grid::findAllWords(const Dictionary& d) const
{
    DictionarySearch search;
    return Dictionary::fromVector({});
}

}