#pragma once
#include "Territory.h"
#include "qpainter.h"
#include <vector>
#include <optional>

class Board
{
public:
    using Position = std::pair<uint8_t, uint8_t>;

public:
    Board(const std::size_t& width, const std::size_t& height);

    // Setters:
    std::optional<Territory>& operator[] (Position pos);
    
    // Getters:
    const std::optional<Territory>& operator[] (Position pos) const;

    // Operators:
    friend std::ostream& operator<< (std::ostream& out, const Board& b);


    void PrintBoard(QPaintDevice* device);
    std::vector<std::optional<Territory>> GetTerritoies() const;
private:
    void SetCoordinates();

private:
    // Constants:
    const std::size_t kWidth;
    const std::size_t kHeight;
    const std::size_t kSize = kWidth * kHeight;
    const int m_xPos = 300;
    const int m_yPos = 350;

private:
    std::vector<std::optional<Territory>> m_board{ kSize };
};

