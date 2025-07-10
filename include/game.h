#ifndef GAME_H
#define GAME_H
#include "raylib.h"

namespace Game
{
  enum class gameState
  {
    running,
    notRunning,
    pause,
  };

}

extern Game::gameState gameState;

#endif