#pragma once

#include <cstdint>

namespace core
{

struct GridCoord
{
    uint32_t x;
    uint32_t y;
};

inline bool operator==(const GridCoord& a, const GridCoord& b)
{
    return a.x == b.x && a.y == b.y;
}

}