#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include <iostream>

// Global texture declarations
extern Texture2D PawnWhite;
extern Texture2D KnightWhite;
extern Texture2D RookWhite;
extern Texture2D BishopWhite;
extern Texture2D QueenWhite;
extern Texture2D KingWhite;

extern Texture2D PawnBlack;
extern Texture2D KnightBlack;
extern Texture2D RookBlack;
extern Texture2D BishopBlack;
extern Texture2D QueenBlack;
extern Texture2D KingBlack;

namespace Game
{
  enum class GameState
  {
    PLAYING,
    PAUSED,
  };
}

// Base class for all pieces
class Piece
{
public:
  Vector2 pos;
  Texture2D texture;
  Color color;

  Piece() {}

  Piece(Texture2D &text, Vector2 vectorPosition, Color c)
      : pos(vectorPosition), texture(text), color(c) {}

  virtual ~Piece() {}
};

// Derived piece classes
class Pawn : public Piece
{
public:
  int type = 0;

  Pawn(Texture2D &text, Vector2 vectorPosition, Color c)
      : Piece(text, vectorPosition, c) {}
};

class Knight : public Piece
{
public:
  int type = 1;

  Knight(Texture2D &text, Vector2 vectorPosition, Color c)
      : Piece(text, vectorPosition, c) {}
};

class Bishop : public Piece
{
public:
  int type = 2;

  Bishop(Texture2D &text, Vector2 vectorPosition, Color c)
      : Piece(text, vectorPosition, c) {}
};

class Rook : public Piece
{
public:
  int type = 3;

  Rook(Texture2D &text, Vector2 vectorPosition, Color c)
      : Piece(text, vectorPosition, c) {}
};

class Queen : public Piece
{
public:
  int type = 4;

  Queen(Texture2D &text, Vector2 vectorPosition, Color c)
      : Piece(text, vectorPosition, c) {}
};

class King : public Piece
{
public:
  int type = 5;

  King(Texture2D &text, Vector2 vectorPosition, Color c)
      : Piece(text, vectorPosition, c) {}
};

// Global game state and game pieces list
extern Game::GameState gameState;
extern std::vector<Piece *> gamePieces;

// Game logic
void initBoard();
void drawBoard();
void unloadTextures();

#endif // GAME_H
