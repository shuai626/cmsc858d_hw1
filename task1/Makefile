CC=g++
CFLAGS=  -std=c++20
DEPS=rank_support.h

make: main.o rank_support.o
	$(CC) -o rank.exe main.o rank_support.o $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm *.o rank.exe