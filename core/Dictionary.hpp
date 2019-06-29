#pragma once

#include <vector>
#include <chobo/memory_view.hpp>

namespace core
{

class Word;

class Dictionary
{
public:
    Dictionary();
    ~Dictionary();

    // load words from UT
    void loadFromUtf8Buffer(chobo::const_memory_view<uint8_t> buffer);

    const std::vector<Word>& words() const { return m_words; }

private:
    std::vector<Word> m_words;
};

}