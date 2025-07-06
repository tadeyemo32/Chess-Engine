#include "engine.h"
#include <string.h>
#include <iostream>

Engine::Engine_Difficulty getDifficulty(std::string s)
{

  if (s == "easy")
  {
    std::cout << "Valid Argument Difficulty set to Easy" << "\n";
    return Engine::Engine_Difficulty::EASY;
  }
  else if (s == "medium")

  {
    std::cout << "Valid Argument Difficulty set to Medium" << "\n";
    return Engine::Engine_Difficulty::EASY;
  }
  else
  {
    std::cout << "Valid Argument Difficulty set to Hard" << "\n";
    return Engine::Engine_Difficulty::HARD;
  }
}
