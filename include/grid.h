#ifndef GRID_H
#define GRID_H

#include "constants.h"
#include "raylib.h"
#include "game.h"
#include <string>
#include <vector>

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
  extern Vector2 selectedCell;
  extern Piece *selectedPiece;
  extern Color currentTurn;
  extern Color selectedColor;
  extern std::vector<Vector2> possibleMoves;

  void initGrid();
  void drawGrid();
  Vector2 handleCellClick(Vector2 mousePos);
  std::string indexToNotation(int row, int col);
  void resetSelection();
  bool isCellSelected();
  Vector2 getSelectedCell();
  Cell &getCell(int row, int col);
  bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol);
  bool isPathClear(int fromRow, int fromCol, int toRow, int toCol);
  void calculatePossibleMoves(int row, int col);
  void drawPossibleMoves();
  bool isInCheck(Color color);
  bool isCheckmate(Color color);
  bool canCastle(int row, int col, int toRow, int toCol);
}
#endif