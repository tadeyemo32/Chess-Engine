#include <iostream>
#include <string>
#include "engine.h"
#include "game.h"
#include "constants.h"
#include "grid.h"
#include "raylib.h"
#include <unistd.h>
#include <limits.h>

Engine::Engine_Difficulty diffculty;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "Invalid Number of Arguments\n";
    return -1;
  }

  std::string arg = argv[1];
  if (arg != "easy" && arg != "medium" && arg != "hard")
  {
    std::cout << "Invalid argument\n";
    return 1;
  }
  diffculty = getDifficulty(arg);

  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(WindowWidth, WindowHeight, GAMEWINDOWNAME);
  InitAudioDevice();
  SetTargetFPS(GAMEFPS);

  Grid::initGrid();

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Grid::drawGrid();
    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();

  return 0;
}
