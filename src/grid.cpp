#include "raylib.h"
#include <iostream>
#include "constants.h"
#include "grid.h"

namespace Grid
{
  Cell grid[8][8];

  void initGrid()
  {
    std::cout << "Initializing Grid..." << std::endl;
    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        Grid::Cell newCell;
        bool isDark = (row + col) % 2 == 0;
        newCell.color = isDark ? DARKBROWN : LIGHTGRAY;
        newCell.isOccupied = false;
        grid[row][col] = newCell;
      }
    }

    for (int row = 0; row < 2; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        grid[row][col].isOccupied = true; // set top row to cells to be occupied
      }
    }
    for (int row = 0; row < 2; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        grid[row + 6][col].isOccupied = true; // set bottom row to cells to be occupied
      }
    }
  }

  void drawGrid()
  {
    int squareSize = GetScreenWidth() / 8;

    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        int x = col * squareSize;
        int y = row * squareSize;
        DrawRectangle(x, y, squareSize, squareSize, grid[row][col].color);
      }
    }
  }

  void test(int x, int y)
  {
    grid[x][y].color = RED;
  }

  // grid.cpp
#include <cctype> // For tolower()

  // ... other Grid functions ...

  std::string Grid::indexToNotation(int row, int col)
  {
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
    {
      return "??"; // Invalid position
    }

    char file = 'a' + col;
    char rank = '8' - row;
    return std::string(1, file) + rank;
  }

  std::pair<int, int> Grid::notationToIndex(const std::string &chessNotation)
  {
    if (chessNotation.length() != 2)
    {
      return {-1, -1}; // Invalid
    }

    char file = tolower(chessNotation[0]);
    char rank = chessNotation[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
    {
      return {-1, -1}; // Invalid
    }

    int col = file - 'a';
    int row = '8' - rank;
    return {row, col};
  }

  void Grid::handleCellClick(Vector2 mousePos)
  {
    int squareSize = GetScreenWidth() / 8;

    // Convert mouse position to grid indices
    int col = mousePos.x / squareSize;
    int row = mousePos.y / squareSize;

    // Boundary check
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
      // Turn clicked cell red
      grid[row][col].color = RED;

      // Print debug info
      std::cout << "Clicked at: "
                << "Row " << row << ", Col " << col << " | "
                << "Chess notation: " << indexToNotation(row, col) << "\n";
    }
  }

}
