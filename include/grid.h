#ifndef GRID_H
#define GRID_H

#include "constants.h"
#include "raylib.h"
#include "game.h"
#include <string> // Add this for string support

namespace Grid
{
  class Cell
  {
  public:
    bool isOccupied;
    Color color;
    Piece *piece;
  };

  extern Cell grid[8][8];

  // Function declarations - NO Grid:: prefix here
  void initGrid();
  void drawGrid();
  void test(int x, int y);
  Vector2 handleCellClick(Vector2 mousePos); // Proper declaration
  std::string indexToNotation(int row, int col);
  std::pair<int, int> notationToIndex(const std::string &chessNotation);
}

#endif