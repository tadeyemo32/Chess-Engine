#include "game.h"
#include <type_traits>
std::vector<Piece *> gamePieces;
Game::GameState gameState = Game::GameState::PLAYING;
const int offsetX = 10;
const int offsetY = 15;

void initBoard()
{
  Texture2D pawnBlack = LoadTexture("../assets/black-pawn.png");
  Texture2D rookBlack = LoadTexture("../assets/black-rook.png");
  Texture2D knightBlack = LoadTexture("../assets/black-knight.png");
  Texture2D bishopBlack = LoadTexture("../assets/black-bishop.png");
  Texture2D kingBlack = LoadTexture("../assets/black-king.png");
  Texture2D queenBlack = LoadTexture("../assets/black-queen.png");

  int squareSize = GetScreenWidth() / 8;
  // Create black pawns
  Vector2 pos;
  for (int i = 0; i < 8; i++)
  {
    pos.x = (i * squareSize) - offsetX;
    pos.y = squareSize - offsetY; // row 2 (index 1)
    std::cout << pos.x << "\n";
    std::cout << pos.y << "\n";
    Pawn *newPawn = new Pawn(pawnBlack, pos, BLACK);
    gamePieces.push_back(newPawn);
  }
  // king
  pos.x = (4 * squareSize) - offsetX;
  pos.y = -offsetY;
  King *newKing = new King(kingBlack, pos, BLACK);
  gamePieces.push_back(newKing);

  // queen
  pos.x = (3 * squareSize) - offsetX;
  Queen *newQueen = new Queen(queenBlack, pos, BLACK);
  gamePieces.push_back(newQueen);

  // bishop
  pos.x = (2 * squareSize) - offsetX;
  Bishop *newBishopLeft = new Bishop(bishopBlack, pos, BLACK);
  gamePieces.push_back(newBishopLeft);

  pos.x = (5 * squareSize) - offsetX;
  Bishop *newBishopRight = new Bishop(bishopBlack, pos, BLACK);
  gamePieces.push_back(newBishopRight);

  // Knight
  pos.x = pos.x = (1 * squareSize) - offsetX;
  Knight *newKnightLeft = new Knight(knightBlack, pos, BLACK);
  gamePieces.push_back(newKnightLeft);

  pos.x = (6 * squareSize) - offsetX;
  Knight *newKnightRight = new Knight(knightBlack, pos, BLACK);
  gamePieces.push_back(newKnightRight);

  // Rook
  pos.x = (0 * squareSize) - offsetX;
  Rook *newRookLeft = new Rook(rookBlack, pos, BLACK);
  gamePieces.push_back(newRookLeft);

  pos.x = (7 * squareSize) - offsetX;
  Rook *newRookRight = new Rook(rookBlack, pos, BLACK);
  gamePieces.push_back(newRookRight);

  ///////
  int height = GetScreenHeight();
  Texture2D pawnWhite = LoadTexture("../assets/white-pawn.png");
  Texture2D rookWhite = LoadTexture("../assets/white-rook.png");
  Texture2D knightWhite = LoadTexture("../assets/white-knight.png");
  Texture2D bishopWhite = LoadTexture("../assets/white-bishop.png");
  Texture2D kingWhite = LoadTexture("../assets/white-king.png");
  Texture2D queenWhite = LoadTexture("../assets/white-queen.png");

  for (int i = 0; i < 8; i++)
  {
    pos.x = (i * squareSize) - offsetX;
    pos.y = (height - (2 * squareSize)) - offsetY; // row 2 (index 1)
    std::cout << pos.x << "\n";
    std::cout << pos.y << "\n";
    Pawn *newPawn = new Pawn(pawnWhite, pos, WHITE);
    gamePieces.push_back(newPawn);
  }
  // king
  pos.x = (4 * squareSize) - offsetX;
  pos.y = height - squareSize - offsetY;
  King *newKingWhiteLeft = new King(kingWhite, pos, WHITE);
  gamePieces.push_back(newKingWhiteLeft);

  // queen
  pos.x = (3 * squareSize) - offsetX;
  Queen *newQueenWhiteLeft = new Queen(queenWhite, pos, WHITE);
  gamePieces.push_back(newQueenWhiteLeft);

  // bishop
  pos.x = (2 * squareSize) - offsetX;
  Bishop *newBishopLeftWhite = new Bishop(bishopWhite, pos, WHITE);
  gamePieces.push_back(newBishopLeftWhite);

  pos.x = (5 * squareSize) - offsetX;
  Bishop *newBishopRightWhite = new Bishop(bishopWhite, pos, WHITE);
  gamePieces.push_back(newBishopRightWhite);

  // Knight
  pos.x = pos.x = (1 * squareSize) - offsetX;
  Knight *newKnightLeftWhite = new Knight(kingWhite, pos, WHITE);
  gamePieces.push_back(newKnightLeftWhite);

  pos.x = (6 * squareSize) - offsetX;
  Knight *newKnightRightWhite = new Knight(knightWhite, pos, WHITE);
  gamePieces.push_back(newKnightRightWhite);

  // Rook
  pos.x = (0 * squareSize) - offsetX;
  Rook *newRookLeftWhite = new Rook(rookWhite, pos, WHITE);
  gamePieces.push_back(newRookLeftWhite);

  pos.x = (7 * squareSize) - offsetX;
  Rook *newRookRightWhite = new Rook(rookWhite, pos, WHITE);
  gamePieces.push_back(newRookRightWhite);
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
