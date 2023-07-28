all: run

run: main.cxx ShiftFitMaker.cxx ShiftHistMaker.cxx
	g++ $^ -o $@ $$(root-config --libs --cflags) -std=c++17 -O3