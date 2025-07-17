#include "game.h"
#include "grid.h"
#include <algorithm>
#include <string>
#include "raylib.h"

std::vector<Piece *> gamePieces;
Game::GameState gameState = Game::GameState::PLAYING;

static Piece *CreateRook(Texture2D t, Vector2 p, Color c) { return new Rook(t, p, c); }
static Piece *CreateKnight(Texture2D t, Vector2 p, Color c) { return new Knight(t, p, c); }
static Piece *CreateBishop(Texture2D t, Vector2 p, Color c) { return new Bishop(t, p, c); }
static Piece *CreateQueen(Texture2D t, Vector2 p, Color c) { return new Queen(t, p, c); }
static Piece *CreateKing(Texture2D t, Vector2 p, Color c) { return new King(t, p, c); }

void initBoard()
{
  // Load textures
  Texture2D pawnBlack = LoadTexture("../assets/black-pawn.png");
  Texture2D rookBlack = LoadTexture("../assets/black-rook.png");
  Texture2D knightBlack = LoadTexture("../assets/black-knight.png");
  Texture2D bishopBlack = LoadTexture("../assets/black-bishop.png");
  Texture2D kingBlack = LoadTexture("../assets/black-king.png");
  Texture2D queenBlack = LoadTexture("../assets/black-queen.png");

  Texture2D pawnWhite = LoadTexture("../assets/white-pawn.png");
  Texture2D rookWhite = LoadTexture("../assets/white-rook.png");
  Texture2D knightWhite = LoadTexture("../assets/white-knight.png");
  Texture2D bishopWhite = LoadTexture("../assets/white-bishop.png");
  Texture2D kingWhite = LoadTexture("../assets/white-king.png");
  Texture2D queenWhite = LoadTexture("../assets/white-queen.png");

  int squareSize = GetScreenWidth() / 8;
  int height = GetScreenHeight();
  Vector2 pos;

  // Black pieces
  for (int i = 0; i < 8; i++)
  {
    pos.x = (i * squareSize) - offsetX;
    pos.y = squareSize - offsetY;
    Pawn *newPawn = new Pawn(pawnBlack, pos, BLACK);
    gamePieces.push_back(newPawn);
    Grid::grid[1][i].piece = newPawn;
    Grid::grid[1][i].isOccupied = true;
  }

  struct PieceInfo
  {
    int col;
    int type;
    Piece *(*create)(Texture2D, Vector2, Color);
    Texture2D tex;
  };

  PieceInfo blackPieces[] = {
      {0, ROOK, CreateRook, rookBlack},
      {1, KNIGHT, CreateKnight, knightBlack},
      {2, BISHOP, CreateBishop, bishopBlack},
      {3, QUEEN, CreateQueen, queenBlack},
      {4, KING, CreateKing, kingBlack},
      {5, BISHOP, CreateBishop, bishopBlack},
      {6, KNIGHT, CreateKnight, knightBlack},
      {7, ROOK, CreateRook, rookBlack}};

  for (auto &info : blackPieces)
  {
    pos.x = (info.col * squareSize) - offsetX;
    pos.y = 0 - offsetY;
    Piece *p = info.create(info.tex, pos, BLACK);
    gamePieces.push_back(p);
    Grid::grid[0][info.col].piece = p;
    Grid::grid[0][info.col].isOccupied = true;
  }

  // White pieces
  for (int i = 0; i < 8; i++)
  {
    pos.x = (i * squareSize) - offsetX;
    pos.y = (height - (2 * squareSize)) - offsetY;
    Pawn *newPawn = new Pawn(pawnWhite, pos, WHITE);
    gamePieces.push_back(newPawn);
    Grid::grid[6][i].piece = newPawn;
    Grid::grid[6][i].isOccupied = true;
  }

  PieceInfo whitePieces[] = {
      {0, ROOK, CreateRook, rookWhite},
      {1, KNIGHT, CreateKnight, knightWhite},
      {2, BISHOP, CreateBishop, bishopWhite},
      {3, QUEEN, CreateQueen, queenWhite},
      {4, KING, CreateKing, kingWhite},
      {5, BISHOP, CreateBishop, bishopWhite},
      {6, KNIGHT, CreateKnight, knightWhite},
      {7, ROOK, CreateRook, rookWhite}};

  for (auto &info : whitePieces)
  {
    pos.x = (info.col * squareSize) - offsetX;
    pos.y = (height - squareSize) - offsetY;
    Piece *p = info.create(info.tex, pos, WHITE);
    gamePieces.push_back(p);
    Grid::grid[7][info.col].piece = p;
    Grid::grid[7][info.col].isOccupied = true;
  }
}

void drawBoard()
{
  for (auto piece : gamePieces)
  {
    DrawTexture(piece->texture, piece->pos.x, piece->pos.y, piece->color);
  }
}

void unloadTextures()
{
  for (Piece *piece : gamePieces)
  {
    UnloadTexture(piece->texture);
    delete piece;
  }
  gamePieces.clear();
}

bool movePiece()
{
  Vector2 mousePos = GetMousePosition();
  Grid::handleCellClick(mousePos);
  return true;
}