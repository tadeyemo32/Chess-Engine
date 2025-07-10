#ifndef GRID_H
#define GRID_H
#include "constants.h"
#include "raylib.h"
#define gridLength (WindowHeight / 8)

namespace Grid
{
  class Cell
  {
  public:
    bool isOccupied;
    Color color;
  };

  void initGrid();

  void drawGrid();

}

#endif