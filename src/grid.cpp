#include "raylib.h"
#include <iostream>
#include "constants.h"
#include "grid.h"

namespace Grid
{
  static Grid::Cell grid[8][8];

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
}
