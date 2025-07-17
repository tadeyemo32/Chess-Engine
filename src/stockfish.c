#include "stockfish.h"
#include <iostream>

Stockfish::Stockfish() {
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }
}

Stockfish::~Stockfish() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

size_t Stockfish::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch(std::bad_alloc &e) {
        return 0;
    }
    return newLength;
}

std::string Stockfish::getBestMove(const std::string& fen, int difficulty) {
    if (!curl) return "";
    
    std::string url = "https://stockfish.online/api/s/v2.php?fen=" + fen + 
                     "&depth=" + std::to_string(difficulty);
    
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return "";
    }
    
    try {
        auto json = nlohmann::json::parse(response);
        if (json.contains("success") && json["success"] && json.contains("data") && json["data"].contains("move")) {
            return json["data"]["move"];
        }
    } catch (...) {
        std::cerr << "Error parsing JSON response" << std::endl;
    }
    
    return "";
}