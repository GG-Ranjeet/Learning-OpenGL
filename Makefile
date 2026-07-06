CXX = C:/msys64/mingw32/bin/g++.exe
CC = C:/msys64/mingw32/bin/gcc.exe
CXXFLAGS = -fdiagnostics-color=always -g -Iinclude -Isrc/vendor/glm/ -Isrc/vendor/stb_image/ -Isrc/vendor/imgui/
CFLAGS = -g -Iinclude

LDFLAGS = -Llib -lglfw3 -lgdi32 -lopengl32

SRC_CPP = $(wildcard src/*.cpp) $(wildcard src/vendor/imgui/*.cpp)
SRC_C = src/glad.c

OBJ = $(SRC_CPP:.cpp=.o) $(SRC_C:.c=.o)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o src/vendor/imgui/*.o src/glad.o $(TARGET)
