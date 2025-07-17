#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include <iostream>
#include <string>

enum PieceType
{
  PAWN = 0,
  KNIGHT = 1,
  BISHOP = 2,
  ROOK = 3,
  QUEEN = 4,
  KING = 5
};

inline bool operator==(const Color &a, const Color &b)
{
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

inline bool operator!=(const Color &a, const Color &b)
{
  return !(a == b);
}

namespace Game
{
  enum class GameState
  {
    PLAYING,
    PAUSED,
  };
}

class Piece
{
public:
  Vector2 pos;
  Texture2D texture;
  Color color;
  int type;
  bool hasMoved = false;

  Piece() {}
  Piece(Texture2D &texture, Vector2 pos, Color c) : pos(pos), texture(texture), color(c) {}
  virtual ~Piece() {}
};

class Pawn : public Piece
{
public:
  Pawn(Texture2D &text, Vector2 pos, Color c) : Piece(text, pos, c) { type = PAWN; }
};
class Knight : public Piece
{
public:
  Knight(Texture2D &text, Vector2 pos, Color c) : Piece(text, pos, c) { type = KNIGHT; }
};
class Bishop : public Piece
{
public:
  Bishop(Texture2D &text, Vector2 pos, Color c) : Piece(text, pos, c) { type = BISHOP; }
};
class Rook : public Piece
{
public:
  Rook(Texture2D &text, Vector2 pos, Color c) : Piece(text, pos, c) { type = ROOK; }
};
class Queen : public Piece
{
public:
  Queen(Texture2D &text, Vector2 pos, Color c) : Piece(text, pos, c) { type = QUEEN; }
};
class King : public Piece
{
public:
  King(Texture2D &text, Vector2 pos, Color c) : Piece(text, pos, c) { type = KING; }
};

extern Game::GameState gameState;
extern std::vector<Piece *> gamePieces;

void initBoard();
void drawBoard();
void unloadTextures();
bool movePiece();

#endif