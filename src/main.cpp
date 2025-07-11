#include <iostream>
#include <string>
#include "engine.h"
#include "game.h"
#include "constants.h"
#include "grid.h"
#include "raylib.h"
#include <unistd.h>
#include <limits.h>

namespace troubleShoot
{

  void checkMousePostion()
  {
    std::cout << "X: " << GetMousePosition().x << " Y: " << GetMousePosition().y << " \n";
  }

}

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
  initBoard();
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Grid::drawGrid(); // draw the gird

    drawBoard();
    // draw

    // error checking
    // troubleShoot::checkMousePostion();
    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();
  unloadTextures();
  return 0;
}
