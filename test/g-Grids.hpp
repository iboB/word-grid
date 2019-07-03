#pragma once

#include <core/Grid.hpp>
#include <core/Word.hpp>

namespace test
{

// generates an alphabetical grid
// example
// abcd
// efgh
// ijkl
// mnop
inline core::Grid Grid_alphabetical(size_t w = 4, size_t h = 4)
{
    const auto size = w * h;
    std::vector<core::WordElement> elems(size);
    core::letter letter = 'a';
    for (auto& e : elems)
    {
        e.push_back(letter++);
        if (letter == 'z' + 1) throw 0;
    }

    core::Grid g(w, h, make_memory_view(elems));
    g.acquireElementOwnership();
    return g;
}

// a  b  c    d
// zy f  beg- h
// i  j  k    l
// m  n  o    -end
inline core::Grid Grid_fancy()
{
    using namespace core;
    std::vector<WordElement> elems(16);
    for (int i=0; i<16; ++i)
    {
        elems[i].push_back('a' + i);
    }

    elems[4] = WordElement::fromAscii("zy");
    elems[6] = WordElement::fromAscii("beg-");
    elems[15] = WordElement::fromAscii("-end");

    core::Grid g(4, 4, make_memory_view(elems));
    g.acquireElementOwnership();
    return g;
}
}