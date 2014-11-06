TARGET=hello
CFLAGS=-std=c++11 -DSFML_STATIC
LFLAGS=-static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

FILES_GRAPHICS=graphics/gl_core_3_3.c graphics/Shader.cpp
FILES_MAIN=main.cpp
FILES=$(FILES_GRAPHICS) $(FILES_MAIN)

OBJS=$(patsubst %,obj/%.o,$(basename $(FILES)))
.PHONY: all clean
all: bin/$(TARGET)
bin/$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(@D)
	@g++ $(OBJS) $(LFLAGS) -o bin/$(TARGET)
	@echo "Done."
obj/%.o: src/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
obj/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
clean:
	@rm -rf *.o bin/$(TARGET) bin/$(TARGET).exe obj/
	@echo "Cleaned."
