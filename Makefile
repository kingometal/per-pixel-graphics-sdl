EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
LIBRARY = per-pixel-graphics-view
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf -fPIC
GCC = g++

SOURCEDIR=source
INTERFACEFOLDER=Interfaces
INTERFACEFILES=$(INTERFACEFOLDER)/IPresenter.h
DATAFOLDER=Data
DATAFILES=$(DATAFOLDER)/RGBData.h


all: directories $(EXECUTABLE)

$(EXECUTABLE): $(OUTDIR)/main.o $(OUTDIR)/DemoModel.o $(OUTDIR)/RGBData.o $(OUTDIR)/DemoPresenter.o $(OUTDIR)/UserInput.o $(OUTDIR)/RandomWalkModel.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/DemoModel.o $(OUTDIR)/RGBData.o $(OUTDIR)/DemoPresenter.o $(OUTDIR)/UserInput.o $(OUTDIR)/RandomWalkModel.o $(FLAGS)

$(OUTDIR)/main.o: $(SOURCEDIR)/main.cpp $(SOURCEDIR)/DemoModel.h $(SOURCEDIR)/DemoPresenter.h $(SOURCEDIR)/UserInput.h $(SOURCEDIR)/RandomWalkModel.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) $(FLAGS) -c $(SOURCEDIR)/main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/RandomWalkModel.o: $(SOURCEDIR)/RandomWalkModel.cpp $(SOURCEDIR)/RandomWalkModel.h $(SOURCEDIR)/$(INTERFACEFILES) $(SOURCEDIR)/$(DATAFILES)
	$(GCC) $(FLAGS) -c $(SOURCEDIR)/RandomWalkModel.cpp -o $(OUTDIR)/RandomWalkModel.o

$(OUTDIR)/DemoModel.o: $(SOURCEDIR)/DemoModel.cpp $(SOURCEDIR)/DemoModel.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) $(FLAGS) -c $(SOURCEDIR)/DemoModel.cpp -o $(OUTDIR)/DemoModel.o

$(OUTDIR)/RGBData.o: $(SOURCEDIR)/$(DATAFOLDER)/RGBData.h $(SOURCEDIR)/$(DATAFOLDER)/RGBData.cpp
	$(GCC) $(FLAGS) -c $(SOURCEDIR)/$(DATAFOLDER)/RGBData.cpp -o $(OUTDIR)/RGBData.o

$(OUTDIR)/DemoPresenter.o: $(SOURCEDIR)/DemoPresenter.cpp $(SOURCEDIR)/DemoPresenter.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) $(FLAGS) -c $(SOURCEDIR)/DemoPresenter.cpp -o $(OUTDIR)/DemoPresenter.o

$(OUTDIR)/UserInput.o: $(SOURCEDIR)/UserInput.h $(SOURCEDIR)/UserInput.cpp
	$(GCC) $(FLAGS) -c $(SOURCEDIR)/UserInput.cpp -o $(OUTDIR)/UserInput.o


directories: $(SOURCEDIR) $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)



clean: 
	if [ -d $(OUTDIR) ]; then rm -rf $(OUTDIR); fi
	if [ -e $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi
	if [ -e lib$(LIBRARY).a ]; then rm lib$(LIBRARY).a; fi

rebuild: clean all


run: all FreeMono.ttf
	./$(EXECUTABLE)

