#ifndef GAME_H
#define GAME_H

#include "raylib.h"

namespace Game
{
  enum class GameState
  {
    PLAYING,
    PAUSED,
  };
}

// Namespace for pieces
namespace Piece
{
  class Pawn
  {
  public:
    bool isBlack;
    Vector2 pos;
    Texture2D texture;

    Pawn(bool black, Vector2 position, const Texture2D &tex)
        : isBlack(black), pos(position), texture(tex) {}

    void Draw() const
    {
      DrawTexture(texture, static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
    }
  };

  class Knight
  {
  public:
    bool isBlack;
    Vector2 pos;
    Texture2D texture;

    Knight(bool black, Vector2 position, const Texture2D &tex)
        : isBlack(black), pos(position), texture(tex) {}

    void Draw() const
    {
      DrawTexture(texture, static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
    }
  };

  class Bishop
  {
  public:
    bool isBlack;
    Vector2 pos;
    Texture2D texture;

    Bishop(bool black, Vector2 position, const Texture2D &tex)
        : isBlack(black), pos(position), texture(tex) {}

    void Draw() const
    {
      DrawTexture(texture, static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
    }
  };

  class Rook
  {
  public:
    bool isBlack;
    Vector2 pos;
    Texture2D texture;

    Rook(bool black, Vector2 position, const Texture2D &tex)
        : isBlack(black), pos(position), texture(tex) {}

    void Draw() const
    {
      DrawTexture(texture, static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
    }
  };

  class King
  {
  public:
    bool isBlack;
    Vector2 pos;
    Texture2D texture;

    King(bool black, Vector2 position, const Texture2D &tex)
        : isBlack(black), pos(position), texture(tex) {}

    void Draw() const
    {
      DrawTexture(texture, static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
    }
  };

  class Queen
  {
  public:
    bool isBlack;
    Vector2 pos;
    Texture2D texture;

    Queen(bool black, Vector2 position, const Texture2D &tex)
        : isBlack(black), pos(position), texture(tex) {}

    void Draw() const
    {
      DrawTexture(texture, static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
    }
  };
}

namespace TextureManager
{
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

  void LoadAllTextures();
  void UnloadAllTextures();
}

// Global game state
extern Game::GameState gameState;

#endif // GAME_H
