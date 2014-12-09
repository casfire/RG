TARGET=hello
CFLAGS=-Wall -Wextra -std=c++11 -DSFML_STATIC
LFLAGS=-static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

FILES_ENGINE_OBJ=Objects.cpp Reader.cpp NullReader.cpp TriangleReader.cpp
FILES_ENGINE_GL=gl_core_3_3.c Common.cpp Shader.cpp Program.cpp Buffer.cpp Texture.cpp
FILES_ENGINE_ASSET=Common.cpp Storage.cpp GLProgram.cpp
FILES_ENGINE_ROOT=Transformation.cpp
FILES_MAIN=main.cpp

_FILES_ENGINE_OBJ=$(patsubst %,Engine/Obj/%,$(FILES_ENGINE_OBJ))
_FILES_ENGINE_GL=$(patsubst %,Engine/GL/%,$(FILES_ENGINE_GL))
_FILES_ENGINE_ASSET=$(patsubst %,Engine/Asset/%,$(FILES_ENGINE_ASSET))
_FILES_ENGINE_ROOT=$(patsubst %,Engine/%,$(FILES_ENGINE_ROOT))
_FILES_ENGINE=$(_FILES_ENGINE_GL) $(_FILES_ENGINE_ASSET) $(_FILES_ENGINE_OBJ) $(_FILES_ENGINE_ROOT)

FILES=$(FILES_MAIN) $(_FILES_ENGINE)

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
