#include "raylib.h"
#include <iostream>
#include "constants.h"
#include "grid.h"

namespace Grid
{
  Cell grid[8][8];
  Vector2 selectedCell = {-1, -1};

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
        newCell.piece = nullptr;
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

        // Highlight selected cell
        if (selectedCell.x == row && selectedCell.y == col)
        {
          DrawRectangle(x, y, squareSize, squareSize, YELLOW);
        }
        else
        {
          DrawRectangle(x, y, squareSize, squareSize, grid[row][col].color);
        }
      }
    }
  }

  std::string indexToNotation(int row, int col)
  {
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
    {
      return "??"; // Invalid position
    }

    char file = 'a' + col;
    char rank = '8' - row;
    return std::string(1, file) + rank;
  }

  std::pair<int, int> notationToIndex(const std::string &chessNotation)
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

  Vector2 handleCellClick(Vector2 mousePos)
  {
    using namespace std;
    int squareSize = GetScreenWidth() / 8;
    int col = mousePos.x / squareSize;
    int row = mousePos.y / squareSize;

    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
      selectedCell = {(float)row, (float)col};
      cout << "Selected: " << indexToNotation(row, col);
      if (grid[row][col].piece != nullptr)
      {
        cout << " - " << grid[row][col].piece->type;
      }
      cout << endl;
    }
    else
    {
      selectedCell = {-1, -1};
      cout << "Deselected" << endl;
    }

    return {(float)row, (float)col};
  }

  void resetSelection()
  {
    selectedCell = {-1, -1};
  }

  bool isCellSelected()
  {
    return selectedCell.x >= 0 && selectedCell.y >= 0;
  }

  Vector2 getSelectedCell()
  {
    return selectedCell;
  }

  Cell &getCell(int row, int col)
  {
    return grid[row][col];
  }
}