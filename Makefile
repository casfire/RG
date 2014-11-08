TARGET=hello
CFLAGS=-Wall -Wextra -std=c++11 -DSFML_STATIC
LFLAGS=-static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

FILES_GRAPHICS_GL=gl_core_3_3.c Common.cpp Shader.cpp Program.cpp
FILES_MAIN=main.cpp
FILES=$(patsubst %,Graphics/GL/%,$(FILES_GRAPHICS_GL)) $(FILES_MAIN)

OBJS=$(patsubst %,build/%.o,$(basename $(FILES)))
.PHONY: all clean
all: bin/$(TARGET)
bin/$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(@D)
	@g++ $(OBJS) $(LFLAGS) -o bin/$(TARGET)
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
	@rm -rf *.o bin/$(TARGET) bin/$(TARGET).exe build/
	@echo "Cleaned."
