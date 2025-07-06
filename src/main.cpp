#include <iostream>
#include <string.h>
#include "engine.h"
Engine::Engine_Difficulty diffculty; // initialize the engine difficulty to easy

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
    std::cout << "Invalid argument" << "\n";
    return 1;
  }

  diffculty = getDifficulty(std::string(argv[1]));

  return 0;
}