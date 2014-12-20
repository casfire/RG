TARGET=hello
CFLAGS=-Wall -Wextra -std=c++11 -DSFML_STATIC
LFLAGS=-static -static-libgcc -static-libstdc++ -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 

FILES=$(wildcard src/*.cpp) $(wildcard src/*.c)
FILES+=$(wildcard src/*/*.cpp) $(wildcard src/*/*.c)
FILES+=$(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*.c)
FILES+=$(wildcard src/*/*/*/*.cpp) $(wildcard src/*/*/*/*.c)

OBJS=$(patsubst %,build/%.o,$(basename $(FILES:src/%=%)))
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
	@g++ $< $(CFLAGS) -MT $@ -MM -MF build/$*.d
build/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
	@g++ $< $(CFLAGS) -MT $@ -MM -MF build/$*.d
-include $(OBJS:.o=.d)
%.hpp %.h %.cpp %.c:
clean:
	@rm -rf *.o $(TARGET) $(TARGET).exe build/
	@echo "Cleaned."
