EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
LIBRARY = per-pixel-graphics-view
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf -fPIC
GCC = g++
INTERFACEFOLDER=Interfaces
INTERFACEFILES=$(INTERFACEFOLDER)/IModel.h $(INTERFACEFOLDER)/KeyCodes.h $(INTERFACEFOLDER)/RGBData.h


all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/DrawJob.o $(OUTDIR)/DemoModel.o $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/DrawJob.o $(OUTDIR)/DemoModel.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp $(OUTDIR)/DrawJob.o $(OUTDIR)/DemoModel.o
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/DemoModel.o: DemoModel.cpp DemoModel.h $(INTERFACEFILES)
	$(GCC) $(FLAGS) -c DemoModel.cpp -o $(OUTDIR)/DemoModel.o

$(OUTDIR)/DrawJob.o: DrawJob.cpp DrawJob.h $(INTERFACEFILES)
	$(GCC) $(FLAGS) -c DrawJob.cpp -o $(OUTDIR)/DrawJob.o

directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)



clean: 
	if [ -d $(OUTDIR) ]; then rm -rf $(OUTDIR); fi
	if [ -e $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi
	if [ -e lib$(LIBRARY).a ]; then rm lib$(LIBRARY).a; fi


run: $(EXECUTABLE) FreeMono.ttf
	./$(EXECUTABLE)

