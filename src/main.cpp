#include <iostream>
#include <string.h>
#include "engine.h"
Engine::Engine_Difficulty diffculty = Engine::Engine_Difficulty::EASY; // initialize the engine difficulty to easy

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    std::cout << "Invalid Number of Arguments\n";
    return -1;
  }

  return 0;
}