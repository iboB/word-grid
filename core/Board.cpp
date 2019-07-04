#include "Board.hpp"

namespace core
{

Board::Board(Grid&& grid, const Scoring& scoring, Dictionary&& dictionary)
    : m_grid(std::move(grid))
    , m_scoring(scoring)
    , m_dictionary(std::move(dictionary))
{}

Board::~Board() = default;

Board::Board(Board&&) noexcept = default;
Board& Board::operator=(Board&&) noexcept = default;


}