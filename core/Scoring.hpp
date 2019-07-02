#pragma once

#include "WordElement.hpp"
#include "GridCoord.hpp"

#include <chobo/memory_view.hpp>
#include <chobo/flat_map.hpp>

namespace core
{

class Grid;

class Scoring
{
public:
    virtual ~Scoring() = default;

    // both functions assume
    score_t score(const Grid& grid, chobo::const_memory_view<GridCoord> coords) const;
    score_t score(chobo::const_memory_view<WordElement> word) const;

    // the score functions create a word view of the word that needs to be scored
    // traverse the word view in
    class WordView
    {
    public:
        virtual size_t size() const = 0;
        virtual const WordElement& at(size_t i) const = 0;
    protected:
        friend class Scoring;
        // intentionally not virtual Scoring::score are the only functions which create it
        ~WordView() {}
    };
protected:
    virtual score_t calcScore(const WordView& view) const = 0;
};

}