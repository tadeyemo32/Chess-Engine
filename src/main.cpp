#include <iostream>
#include <string>
#include "engine.h"
#include "game.h"
#include "constants.h"
#include "grid.h"
#include "raylib.h"

Engine::Engine_Difficulty diffculty;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " [easy|medium|hard]\n";
    return -1;
  }

  std::string arg = argv[1];
  if (arg != "easy" && arg != "medium" && arg != "hard")
  {
    std::cout << "Invalid difficulty\n";
    return 1;
  }
  diffculty = getDifficulty(arg);

  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(WindowWidth, WindowHeight, GAMEWINDOWNAME);
  SetTargetFPS(GAMEFPS);

  Grid::initGrid();
  initBoard();

  while (!WindowShouldClose())
  {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      movePiece();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    Grid::drawGrid();
    Grid::drawPossibleMoves();
    drawBoard();
    EndDrawing();
  }

  CloseWindow();
  unloadTextures();
  return 0;
}