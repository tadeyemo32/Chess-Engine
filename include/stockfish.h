#ifndef STOCKFISH_H
#define STOCKFISH_H

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class Stockfish
{
public:
  Stockfish();
  ~Stockfish();
  std::string getBestMove(const std::string &fen, int difficulty);

private:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);
  CURL *curl;
};

#endif