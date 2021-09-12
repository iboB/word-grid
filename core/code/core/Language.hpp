#pragma once
#include "API.h"

#include "DictionaryWord.hpp"

namespace core
{

class CORE_API Language
{
public:
private:
    std::vector<DictionaryWord> m_words;
    std::vector<char> m_dictionaryUtf8Buffer;
};

}
