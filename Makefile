EXECUTABLE=per-pixel-graphics.x
OUTDIR = build
LIBRARY = per-pixel-graphics-view
LIBDIR = libs
FLAGS = -std=c++11 -lSDL2 -lSDL2_ttf
FLAGS_COMPILE = -fPIC
GCC = g++

SOURCEDIR=source
INTERFACEFOLDER=Interfaces
INTERFACEFILES=$(INTERFACEFOLDER)/IPresenter.h
DATAFOLDER=Data
DATAFILES=$(DATAFOLDER)/RGBData.h


MODELS=$(OUTDIR)/DemoModel.o $(OUTDIR)/RandomWalkModel.o $(OUTDIR)/BallModel.o

all: directories $(EXECUTABLE)

$(EXECUTABLE): $(OUTDIR)/main.o $(OUTDIR)/RGBData.o $(OUTDIR)/DemoPresenter.o $(OUTDIR)/UserInput.o $(MODELS)
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/RGBData.o $(OUTDIR)/DemoPresenter.o $(OUTDIR)/UserInput.o $(MODELS) $(FLAGS)

$(OUTDIR)/main.o: $(SOURCEDIR)/main.cpp $(SOURCEDIR)/DemoModel.h $(SOURCEDIR)/DemoPresenter.h $(SOURCEDIR)/UserInput.h $(SOURCEDIR)/RandomWalkModel.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) -c $(SOURCEDIR)/main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/RandomWalkModel.o: $(SOURCEDIR)/RandomWalkModel.cpp $(SOURCEDIR)/RandomWalkModel.h $(SOURCEDIR)/$(INTERFACEFILES) $(SOURCEDIR)/$(DATAFILES)
	$(GCC) -c $(SOURCEDIR)/RandomWalkModel.cpp -o $(OUTDIR)/RandomWalkModel.o

$(OUTDIR)/DemoModel.o: $(SOURCEDIR)/DemoModel.cpp $(SOURCEDIR)/DemoModel.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) -c $(SOURCEDIR)/DemoModel.cpp -o $(OUTDIR)/DemoModel.o

$(OUTDIR)/BallModel.o: $(SOURCEDIR)/BallModel.cpp $(SOURCEDIR)/BallModel.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) -c $(SOURCEDIR)/BallModel.cpp -o $(OUTDIR)/BallModel.o

$(OUTDIR)/RGBData.o: $(SOURCEDIR)/$(DATAFOLDER)/RGBData.h $(SOURCEDIR)/$(DATAFOLDER)/RGBData.cpp
	$(GCC) -c $(SOURCEDIR)/$(DATAFOLDER)/RGBData.cpp -o $(OUTDIR)/RGBData.o

$(OUTDIR)/DemoPresenter.o: $(SOURCEDIR)/DemoPresenter.cpp $(SOURCEDIR)/DemoPresenter.h $(SOURCEDIR)/$(INTERFACEFILES)
	$(GCC) -c $(SOURCEDIR)/DemoPresenter.cpp -o $(OUTDIR)/DemoPresenter.o $(FLAGS_COMPILE)

$(OUTDIR)/UserInput.o: $(SOURCEDIR)/UserInput.h $(SOURCEDIR)/UserInput.cpp
	$(GCC) -c $(SOURCEDIR)/UserInput.cpp -o $(OUTDIR)/UserInput.o $(FLAGS_COMPILE)


directories: $(SOURCEDIR) $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)


clean: 
	if [ -d $(OUTDIR) ]; then rm -rf $(OUTDIR); fi
	if [ -e $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi
	if [ -e lib$(LIBRARY).a ]; then rm lib$(LIBRARY).a; fi
	if [ -d $(LIBDIR) ]; then rm -rf $(LIBDIR); fi

rebuild: clean all


run: all FreeMono.ttf
	./$(EXECUTABLE) $(filter-out $@, $(MAKECMDGOALS))



lib-stat: directories $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o
	ar rcs lib$(LIBRARY).a $(OUTDIR)/DrawJob.o $(OUTDIR)/FillJob.o $(OUTDIR)/ViewBuffer.o $(OUTDIR)/View.o

exe-stat: lib-stat $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o -l$(LIBRARY) -L. $(FLAGS) 
	rm $(OUTDIR)/main.o

$(LIBDIR)/libPresenter.so: $(LIBDIR) $(OUTDIR)/DemoPresenter.o $(OUTDIR)/UserInput.o
	$(GCC) -shared $(OUTDIR)/DemoPresenter.o $(OUTDIR)/UserInput.o -o $(LIBDIR)/libPresenter.so

$(LIBDIR)/libDataTypes.so: $(LIBDIR) $(OUTDIR)/RGBData.o
	$(GCC) -shared $(OUTDIR)/RGBData.o -o $(LIBDIR)/libDataTypes.so

all-dynamic: directories $(LIBDIR)/libPresenter.so $(OUTDIR)/main.o $(MODELS) $(LIBDIR)/libDataTypes.so $(MODELS)
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(MODELS) -L$(LIBDIR) -lPresenter -lDataTypes $(FLAGS) 

run-dynamic: all-dynamic FreeMono.ttf
	LD_LIBRARY_PATH=./${LIBDIR}:${LD_LIBRARY_PATH} ./$(EXECUTABLE) $(filter-out $@, $(MAKECMDGOALS))

install-dynamic: directories $(LIBDIR)/libDataTypes.so $(LIBDIR)/libPresenter.so
	cp ./${LIBDIR}/* ~/lib
