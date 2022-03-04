CC=g++
DEPS=select_support.h rank_support.h

make: main.o select_support.o rank_support.o
	$(CC) -o select.exe main.o select_support.o rank_support.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

clean: 
	rm *.o select.exe