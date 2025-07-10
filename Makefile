# ---------------- CONFIG ----------------
CC := clang++
CFLAGS := -Wall -Wextra -std=c++11 -Iinclude

SRCDIR := src
INCDIR := include
BINDIR := build
TARGET := $(BINDIR)/main

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

# Raylib and platform-specific libraries (macOS ARM64)
LDFLAGS := -lraylib -lm -ldl -lpthread -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# ---------------- RULES ----------------
all: $(TARGET)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(BINDIR)/*.o
	rm -f $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: all clean run
