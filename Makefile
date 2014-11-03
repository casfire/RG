TARGET=hello
CFLAGS=-Wall -Wextra -std=c++11 -DSFML_STATIC
LFLAGS=-static -static-libgcc -static-libstdc++ -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

DIRS=graphics
FILES_GRAPHICS=graphics/gl_core_3_3.c graphics/Shader.cpp
FILES_MAIN=main.cpp
FILES=$(FILES_GRAPHICS) $(FILES_MAIN)


OBJDIRS=$(patsubst %,obj/%,$(DIRS))
OBJS=$(patsubst %,obj/%.o,$(basename $(FILES)))
.PHONY: all clean obj/
all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Linking..."
	@g++ $(OBJS) $(LFLAGS) -o $(TARGET)
	@echo "Done."
obj/%.o: src/%.cpp obj/
	@echo "Compiling $<"
	@g++ -c $< $(CFLAGS) -o $@
obj/%.o: src/%.c obj/
	@echo "Compiling $<"
	@g++ -c $< $(CFLAGS) -o $@
obj/:
	@echo "Creating obj/ directory"
	@mkdir -p obj/ $(OBJDIRS)
clean:
	@rm -rf *.o $(TARGET) $(TARGET).exe obj/ $(OBJDIRS)
	@echo "Cleaned."
