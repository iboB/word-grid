#include "Scoring.hpp"
#include "Grid.hpp"

namespace core
{

namespace
{
struct GridCoordView final : public Scoring::WordView {
    GridCoordView(const Grid& g, chobo::const_memory_view<GridCoord>& c)
        : grid(g), coords(c)
    {}

    virtual size_t size() const override
    {
        return coords.size();
    }

    virtual const WordElement& at(size_t i) const override
    {
        return grid.at(coords[i]);
    }

    const Grid& grid;
    chobo::const_memory_view<GridCoord> coords;
};

struct WordElementView : public Scoring::WordView {
    WordElementView(const chobo::const_memory_view<WordElement>& w)
        : word(w)
    {}

    virtual size_t size() const override
    {
        return word.size();
    }

    virtual const WordElement& at(size_t i) const override
    {
        return word.at(i);
    }

    chobo::const_memory_view<WordElement> word;
};
}

score_t Scoring::score(const Grid& grid, chobo::const_memory_view<GridCoord> coords) const
{
    return calcScore(GridCoordView(grid, coords));
}

score_t Scoring::score(chobo::const_memory_view<WordElement> word) const
{
    return calcScore(WordElementView(word));
}

}
