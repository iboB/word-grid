// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"

#include <vector>
#include <chobo/memory_view.hpp>

namespace core
{

class DictionarySearch;

class Word;

class Dictionary
{
public:
    ~Dictionary();

    Dictionary(Dictionary&&) noexcept;
    Dictionary& operator=(Dictionary&&) noexcept;

    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

    // load words from UTF8 buffer separated by newlines
    static Dictionary fromUtf8Buffer(chobo::const_memory_view<uint8_t> buffer);

    // loads words from vector of words. consumes the vector
    static Dictionary fromVector(std::vector<Word>&& words);

    const std::vector<Word>& words() const { return m_words; }

    bool hasWord(const Word& w) const;

    enum class SearchResult
    {
        None,
        Partial,
        Exact,
    };
    // searches for a letter appended to the word in the search
    // changes the inout argument with the bounds of the new letter
    SearchResult search(DictionarySearch& inoutSearch, letter l) const;

private:
    Dictionary();

    void sortWords();
    std::vector<Word> m_words;
};

}