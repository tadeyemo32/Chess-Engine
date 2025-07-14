#include "game.h"
#include "grid.h"
#include <type_traits>
#include <string>
#include "raylib.h"

inline bool operator==(Color a, Color b)
{
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

std::vector<Piece *> gamePieces;
Game::GameState gameState = Game::GameState::PLAYING;
const int offsetX = 10;
const int offsetY = 15;
// Add these at the top of game.cpp or inside an anonymous namespace
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

  // ===== Black Pawns =====
  for (int i = 0; i < 8; i++)
  {
    pos.x = (i * squareSize) - offsetX;
    pos.y = squareSize - offsetY;

    Pawn *newPawn = new Pawn(pawnBlack, pos, BLACK);
    newPawn->type = 0;
    gamePieces.push_back(newPawn);

    Grid::grid[1][i].piece = newPawn;
    Grid::grid[1][i].isOccupied = true;
  }

  // ===== Black Back Rank =====
  struct PieceInfo
  {
    int col;
    int type;
    Piece *(*create)(Texture2D, Vector2, Color);
    Texture2D tex;
  };

  PieceInfo blackPieces[] = {
      {0, 5, CreateRook, rookBlack},
      {1, 3, CreateKnight, knightBlack},
      {2, 2, CreateBishop, bishopBlack},
      {3, 4, CreateQueen, queenBlack},
      {4, 1, CreateKing, kingBlack},
      {5, 2, CreateBishop, bishopBlack},
      {6, 3, CreateKnight, knightBlack},
      {7, 5, CreateRook, rookBlack}};

  for (auto &info : blackPieces)
  {
    pos.x = (info.col * squareSize) - offsetX;
    pos.y = 0 - offsetY;

    Piece *p = info.create(info.tex, pos, BLACK);
    p->type = info.type;
    gamePieces.push_back(p);

    Grid::grid[0][info.col].piece = p;
    Grid::grid[0][info.col].isOccupied = true;
  }

  // ===== White Pawns =====
  for (int i = 0; i < 8; i++)
  {
    pos.x = (i * squareSize) - offsetX;
    pos.y = (height - (2 * squareSize)) - offsetY;

    Pawn *newPawn = new Pawn(pawnWhite, pos, WHITE);
    newPawn->type = 0;
    gamePieces.push_back(newPawn);

    Grid::grid[6][i].piece = newPawn;
    Grid::grid[6][i].isOccupied = true;
  }

  // ===== White Back Rank =====
  PieceInfo whitePieces[] = {
      {0, 5, CreateRook, rookWhite},
      {1, 3, CreateKnight, knightWhite},
      {2, 2, CreateBishop, bishopWhite},
      {3, 4, CreateQueen, queenWhite},
      {4, 1, CreateKing, kingWhite},
      {5, 2, CreateBishop, bishopWhite},
      {6, 3, CreateKnight, knightWhite},
      {7, 5, CreateRook, rookWhite}};

  for (auto &info : whitePieces)
  {
    pos.x = (info.col * squareSize) - offsetX;
    pos.y = (height - squareSize) - offsetY;

    Piece *p = info.create(info.tex, pos, WHITE);
    p->type = info.type;
    gamePieces.push_back(p);

    Grid::grid[7][info.col].piece = p;
    Grid::grid[7][info.col].isOccupied = true;
  }
}

void drawBoard()
{
  for (auto i : gamePieces)
  {
    DrawTexture(i->texture, i->pos.x, i->pos.y, i->color);
  }
}

void unloadTextures()
{
  for (Piece *piece : gamePieces)
  {
    UnloadTexture(piece->texture);
    std::cout << piece << " Removed \n";
    delete piece;
  }
  gamePieces.clear();
}

bool movePiece()
{
  using namespace Grid;
  using namespace std;

  Vector2 mousePos = GetMousePosition();
  Vector2 val = handleCellClick(mousePos);
  int row = val.x;
  int col = val.y;

  if (row < 0 || row >= 8 || col < 0 || col >= 8)
  {
    cout << "Clicked outside the board\n";
    return false;
  }

  cout << "Selected: " << indexToNotation(row, col) << " - ";

  Piece *currentPiece = grid[row][col].piece;
  if (currentPiece == nullptr)
  {
    cout << "Empty square\n";
    return false;
  }

  // Print piece type
  switch (currentPiece->type)
  {
  case 0:
    cout << "Pawn";
    break;
  case 1:
    cout << "King";
    break;
  case 2:
    cout << "Bishop";
    break;
  case 3:
    cout << "Knight";
    break;
  case 4:
    cout << "Queen";
    break;
  case 5:
    cout << "Rook";
    break;
  default:
    cout << "Unknown";
    break;
  }
  cout << endl;

  return true;
}