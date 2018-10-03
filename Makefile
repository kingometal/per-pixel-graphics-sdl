EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf
GCC = g++


all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/View.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/FillJob.o $(OUTDIR)/DrawJob.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp View.h
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/View.o: View.cpp View.h ViewBuffer.h filljob.h drawjob.h
	$(GCC) $(FLAGS) -c View.cpp -o $(OUTDIR)/View.o

$(OUTDIR)/ViewBuffer.o: ViewBuffer.cpp ViewBuffer.h ifillbuffer.h idrawbuffer.h  bufferstate.h
	$(GCC) $(FLAGS) -c ViewBuffer.cpp -o $(OUTDIR)/ViewBuffer.o

$(OUTDIR)/FillJob.o: filljob.cpp filljob.h ifillbuffer.h bufferstate.h
	$(GCC) $(FLAGS) -c filljob.cpp -o $(OUTDIR)/FillJob.o

$(OUTDIR)/DrawJob.o: drawjob.cpp drawjob.h idrawbuffer.h bufferstate.h
	$(GCC) $(FLAGS) -c drawjob.cpp -o $(OUTDIR)/DrawJob.o

directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)



run: all
	./$(EXECUTABLE)
