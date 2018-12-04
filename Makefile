EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
LIBRARY = per-pixel-graphics-view
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf -fPIC
GCC = g++
INTERFACEFOLDER=Interfaces
INTERFACEFILES=$(INTERFACEFOLDER)/IPresenter.h
DATAFOLDER=Data
DATAFILES=$(DATAFOLDER)/KeyCodes.h


all: directories $(EXECUTABLE)

$(EXECUTABLE): $(OUTDIR)/main.o $(OUTDIR)/DemoModel.o $(OUTDIR)/RGBData.o $(OUTDIR)/DemoPresenter.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/DemoModel.o $(OUTDIR)/RGBData.o $(OUTDIR)/DemoPresenter.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp DemoModel.h DemoPresenter.h $(INTERFACEFILES)
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/DemoModel.o: DemoModel.cpp DemoModel.h $(INTERFACEFILES)
	$(GCC) $(FLAGS) -c DemoModel.cpp -o $(OUTDIR)/DemoModel.o

$(OUTDIR)/RGBData.o: $(DATAFOLDER)/RGBData.h $(DATAFOLDER)/RGBData.cpp
	$(GCC) $(FLAGS) -c $(DATAFOLDER)/RGBData.cpp -o $(OUTDIR)/RGBData.o

$(OUTDIR)/DemoPresenter.o: DemoPresenter.cpp DemoPresenter.h $(INTERFACEFILES)
	$(GCC) $(FLAGS) -c DemoPresenter.cpp -o $(OUTDIR)/DemoPresenter.o


directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)



clean: 
	if [ -d $(OUTDIR) ]; then rm -rf $(OUTDIR); fi
	if [ -e $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi
	if [ -e lib$(LIBRARY).a ]; then rm lib$(LIBRARY).a; fi

rebuild: clean all


run: all FreeMono.ttf
	./$(EXECUTABLE)

