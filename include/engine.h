#ifndef ENGINE_H
#define ENGINE_H
#include <string.h>
#include <iostream>

namespace Engine
{
  enum class Engine_Difficulty
  {

    EASY,
    MEDIUM,
    HARD,

  };
}
extern Engine::Engine_Difficulty diffculty;

Engine::Engine_Difficulty getDifficulty(std::string s);

#endif