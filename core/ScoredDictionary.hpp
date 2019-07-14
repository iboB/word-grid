#pragma once

#include "ScoredWord.hpp"

#include <vector>

namespace core
{
class Scoring;
class Grid;

// dictionary which also includes scores for each word
class ScoredDictionary
{
public:
    ScoredDictionary();
    ~ScoredDictionary();

    ScoredDictionary(const ScoredDictionary&) = delete;
    ScoredDictionary& operator=(const ScoredDictionary&) = delete;

    ScoredDictionary(ScoredDictionary&&) noexcept;
    ScoredDictionary& operator=(ScoredDictionary&&) noexcept;

    // building ops
    void clear();
    void addWord(const Word& word, chobo::const_memory_view<GridCoord> coords);
    void scoreWords(const Grid& g, const Scoring& s);

    // query ops
    const std::vector<ScoredWord>& words() const { return m_words; }
    const ScoredWord* getWord(const Word& w) const;
private:
    std::vector<ScoredWord> m_words;
};

}
