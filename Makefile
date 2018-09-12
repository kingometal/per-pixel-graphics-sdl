EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf
GCC = g++


all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)



run: all
	./$(EXECUTABLE)
