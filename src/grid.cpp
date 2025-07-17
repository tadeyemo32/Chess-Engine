#include "raylib.h"
#include <iostream>
#include "constants.h"
#include "grid.h"
#include "game.h"
#include <algorithm>

namespace Grid
{
  Cell grid[8][8];
  Vector2 selectedCell = {-1, -1};
  Piece *selectedPiece = nullptr;
  Color currentTurn = WHITE;
  Color selectedColor = {255, 255, 0, 100};
  std::vector<Vector2> possibleMoves;

  void initGrid()
  {
    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        grid[row][col].color = (row + col) % 2 == 0 ? DARKBROWN : LIGHTGRAY;
        grid[row][col].isOccupied = false;
        grid[row][col].piece = nullptr;
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

        if (selectedCell.x == row && selectedCell.y == col)
        {
          DrawRectangle(x, y, squareSize, squareSize, selectedColor);
          DrawRectangleLines(x, y, squareSize, squareSize, YELLOW);
        }
      }
    }
  }

  void drawPossibleMoves()
  {
    int squareSize = GetScreenWidth() / 8;
    for (const auto &move : possibleMoves)
    {
      int x = move.y * squareSize;
      int y = move.x * squareSize;
      DrawCircle(x + squareSize / 2, y + squareSize / 2, squareSize / 6, {0, 255, 0, 150});
    }
  }

  std::string indexToNotation(int row, int col)
  {
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
      return "??";
    return std::string(1, 'a' + col) + std::to_string(8 - row);
  }

  bool isPathClear(int fromRow, int fromCol, int toRow, int toCol)
  {
    int rowStep = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1
                                                            : 0;
    int colStep = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1
                                                            : 0;

    int row = fromRow + rowStep;
    int col = fromCol + colStep;

    while (row != toRow || col != toCol)
    {
      if (grid[row][col].isOccupied)
        return false;
      row += rowStep;
      col += colStep;
    }
    return true;
  }

  bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    Piece *pawn = grid[fromRow][fromCol].piece;
    if (!pawn || pawn->type != PAWN)
      return false;

    int direction = (pawn->color == WHITE) ? -1 : 1;
    int startRow = (pawn->color == WHITE) ? 6 : 1;

    // Forward move
    if (fromCol == toCol)
    {
      // Single step forward
      if (toRow == fromRow + direction && !grid[toRow][toCol].piece)
        return true;
      // Double step from starting position
      if (fromRow == startRow && toRow == fromRow + 2 * direction &&
          !grid[fromRow + direction][fromCol].piece &&
          !grid[toRow][toCol].piece)
        return true;
    }
    // Capture move
    else if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction)
    {
      if (grid[toRow][toCol].piece && grid[toRow][toCol].piece->color != pawn->color)
        return true;
      // TODO: Add en passant
    }

    return false;
  }

  bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
  }

  bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    if (abs(fromRow - toRow) != abs(fromCol - toCol))
      return false;
    return isPathClear(fromRow, fromCol, toRow, toCol);
  }

  bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    if (fromRow != toRow && fromCol != toCol)
      return false;
    return isPathClear(fromRow, fromCol, toRow, toCol);
  }

  bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    return isValidBishopMove(fromRow, fromCol, toRow, toCol) ||
           isValidRookMove(fromRow, fromCol, toRow, toCol);
  }

  bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    // Normal king move
    if (rowDiff <= 1 && colDiff <= 1)
      return true;

    // TODO: Add castling logic
    return false;
  }

  bool canCastle(int row, int col, int toRow, int toCol)
  {
    // TODO: Implement castling logic
    return false;
  }

  bool isValidMove(int fromRow, int fromCol, int toRow, int toCol)
  {
    if (fromRow == toRow && fromCol == toCol)
      return false;
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
      return false;

    Piece *piece = grid[fromRow][fromCol].piece;
    if (!piece || piece->color != currentTurn)
      return false;

    if (grid[toRow][toCol].piece && grid[toRow][toCol].piece->color == piece->color)
      return false;

    switch (piece->type)
    {
    case PAWN:
      return isValidPawnMove(fromRow, fromCol, toRow, toCol);
    case KNIGHT:
      return isValidKnightMove(fromRow, fromCol, toRow, toCol);
    case BISHOP:
      return isValidBishopMove(fromRow, fromCol, toRow, toCol);
    case ROOK:
      return isValidRookMove(fromRow, fromCol, toRow, toCol);
    case QUEEN:
      return isValidQueenMove(fromRow, fromCol, toRow, toCol);
    case KING:
      return isValidKingMove(fromRow, fromCol, toRow, toCol) ||
             canCastle(fromRow, fromCol, toRow, toCol);
    default:
      return false;
    }
  }

  void calculatePossibleMoves(int row, int col)
  {
    possibleMoves.clear();
    for (int r = 0; r < 8; r++)
    {
      for (int c = 0; c < 8; c++)
      {
        if (isValidMove(row, col, r, c))
          possibleMoves.push_back({(float)r, (float)c});
      }
    }
  }

  Vector2 handleCellClick(Vector2 mousePos)
  {
    int squareSize = GetScreenWidth() / 8;
    int col = mousePos.x / squareSize;
    int row = mousePos.y / squareSize;

    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
      if (selectedCell.x == row && selectedCell.y == col)
      {
        resetSelection();
        return {(float)row, (float)col};
      }

      if (!selectedPiece && grid[row][col].piece && grid[row][col].piece->color == currentTurn)
      {
        selectedCell = {(float)row, (float)col};
        selectedPiece = grid[row][col].piece;
        calculatePossibleMoves(row, col);
        return {(float)row, (float)col};
      }

      if (selectedPiece && isValidMove(selectedCell.x, selectedCell.y, row, col))
      {
        if (grid[row][col].piece)
        {
          auto it = std::find(gamePieces.begin(), gamePieces.end(), grid[row][col].piece);
          if (it != gamePieces.end())
          {
            gamePieces.erase(it);
            delete grid[row][col].piece;
          }
        }

        grid[(int)selectedCell.x][(int)selectedCell.y].piece = nullptr;
        grid[row][col].piece = selectedPiece;
        selectedPiece->pos = {(float)(col * squareSize - offsetX), (float)(row * squareSize - offsetY)};
        selectedPiece->hasMoved = true;

        currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
        resetSelection();
        possibleMoves.clear();
      }
    }
    else
    {
      resetSelection();
    }

    return {(float)row, (float)col};
  }

  void resetSelection()
  {
    selectedCell = {-1, -1};
    selectedPiece = nullptr;
    possibleMoves.clear();
  }

  bool isCellSelected() { return selectedCell.x >= 0 && selectedCell.y >= 0; }
  Vector2 getSelectedCell() { return selectedCell; }
  Cell &getCell(int row, int col) { return grid[row][col]; }
}