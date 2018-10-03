EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf
GCC = g++


all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/View.o $(OUTDIR)/ViewBuffer.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp  $(OUTDIR)/View.o View.h bufferstate.h
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/View.o: View.cpp View.h  $(OUTDIR)/ViewBuffer.o 
	$(GCC) $(FLAGS) -c View.cpp -o $(OUTDIR)/View.o

$(OUTDIR)/ViewBuffer.o: ViewBuffer.cpp ViewBuffer.h bufferstate.h
	$(GCC) $(FLAGS) -c ViewBuffer.cpp -o $(OUTDIR)/ViewBuffer.o

directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)



run: all
	./$(EXECUTABLE)
