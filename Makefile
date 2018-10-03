EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
LIBRARY = per-pixel-graphics-view
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf -fPIC
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
	if [ -d $(OUTDIR) ]; then rm -rf $(OUTDIR); fi
	if [ -e $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi
	if [ -e lib$(LIBRARY).a ]; then rm lib$(LIBRARY).a; fi


run: exe-stat FreeMono.ttf
	./$(EXECUTABLE)

lib-stat: directories $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o
	ar rcs lib$(LIBRARY).a $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o

exe-stat: lib-stat $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o -l$(LIBRARY) -L. $(FLAGS) 
	rm $(OUTDIR)/main.o

lib-dynyamically: $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o
	$(GCC) -shared $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/View.o $(OUTDIR)/ViewBuffer.o -o $(OUTDIR)/lib$(LIBRARY).so

all-dynamically: directories lib-dynamically $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o -L$(OUTDIR) -l$(LIBRARY) $(FLAGS) 

install-dynamically: directories lib-dynamically
	sudo mv $(OUTDIR)/lib$(LIBRARY).so /usr/lib
	sudo chmod 755 /usr/lib/lib$(LIBRARY).so

