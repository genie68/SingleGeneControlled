#SingleGeneControlled project
CPP=g++
CFLAGS=
LFLAGS=

all: stochart


stochart: mendel.h summation.h stochart.cpp herd.h herd.cpp SimpleRNG.h SimpleRNG.cpp
	$(CPP) $(CFLAGS) $(LFLAGS) stochart.cpp herd.cpp SimpleRNG.cpp -o $@

clean:
	rm -f *~ *.o stochart
