# === Compiler and Flags ===
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I/opt/homebrew/include -Wall -Wextra -pedantic
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# === Directories ===
SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/main

# === Source and Object Files ===
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# === Default Target ===
all: $(BIN)

# === Link object files into the final binary ===
$(BIN): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# === Compile .cpp files to .o files ===
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === Clean Build Artifacts ===
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
