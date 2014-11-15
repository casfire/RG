TARGET=hello
CFLAGS=-Wall -Wextra -std=c++11 -DSFML_STATIC
LFLAGS=-static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

FILES_GRAPHICS_GL=gl_core_3_3.c Common.cpp Shader.cpp Program.cpp Buffer.cpp Texture.cpp
FILES_GRAPHICS_ASSET=Common.cpp GLProgram.cpp
FILES_MAIN=main.cpp
FILES=$(FILES_MAIN) $(patsubst %,Graphics/GL/%,$(FILES_GRAPHICS_GL)) $(patsubst %,Graphics/Asset/%,$(FILES_GRAPHICS_ASSET))

OBJS=$(patsubst %,build/%.o,$(basename $(FILES)))
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(@D)
	@g++ $(OBJS) $(LFLAGS) -o $(TARGET)
	@echo "Done."
build/%.o: src/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
build/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
src/%.cpp : src/%.hpp
src/%.c : src/%.h
clean:
	@rm -rf *.o $(TARGET) $(TARGET).exe build/
	@echo "Cleaned."
