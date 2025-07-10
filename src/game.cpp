#include "raylib.h"
#include "game.h"
#include "grid.h"
#include <iostream>

namespace TextureManager
{
  Texture2D PawnWhite;
  Texture2D KnightWhite;
  Texture2D RookWhite;
  Texture2D BishopWhite;
  Texture2D QueenWhite;
  Texture2D KingWhite;

  Texture2D PawnBlack;
  Texture2D KnightBlack;
  Texture2D RookBlack;
  Texture2D BishopBlack;
  Texture2D QueenBlack;
  Texture2D KingBlack;

  Texture2D loadTextureChecked(const char *path)
  {
    Texture2D tex = LoadTexture(path);
    if (tex.id == 0)
    {
      std::cerr << "Failed to load texture: " << path << std::endl;
    }
    return tex;
  }

  void LoadAllTextures()
  {
    PawnWhite = loadTextureChecked("../assets/white-pawn.png");
    KnightWhite = loadTextureChecked("../assets/white-knight.png");
    RookWhite = loadTextureChecked("../assets/white-rook.png");
    BishopWhite = loadTextureChecked("../assets/white-bishop.png");
    QueenWhite = loadTextureChecked("../assets/white-queen.png");
    KingWhite = loadTextureChecked("../assets/white-king.png");

    PawnBlack = loadTextureChecked("../assets/black-pawn.png");
    KnightBlack = loadTextureChecked("../assets/black-knight.png");
    RookBlack = loadTextureChecked("../assets/black-rook.png");
    BishopBlack = loadTextureChecked("../assets/black-bishop.png");
    QueenBlack = loadTextureChecked("../assets/black-queen.png");
    KingBlack = loadTextureChecked("../assets/black-king.png");
  }

  void UnloadAllTextures()
  {
    UnloadTexture(PawnWhite);
    UnloadTexture(KnightWhite);
    UnloadTexture(RookWhite);
    UnloadTexture(BishopWhite);
    UnloadTexture(QueenWhite);
    UnloadTexture(KingWhite);

    UnloadTexture(PawnBlack);
    UnloadTexture(KnightBlack);
    UnloadTexture(RookBlack);
    UnloadTexture(BishopBlack);
    UnloadTexture(QueenBlack);
    UnloadTexture(KingBlack);
  }
}
