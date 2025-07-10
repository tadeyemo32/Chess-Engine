#ifndef GAME_H
#define GAME_H
#include <vector>
#include "raylib.h"
namespace Game
{
  enum class GameState
  {
    PLAYING,
    PAUSED,
  };
}

// Global game state
extern Game::GameState gameState;

#endif // GAME_H
