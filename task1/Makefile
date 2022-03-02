CC=g++
DEPS=rank_support.h

make: main.o rank_support.o
	$(CC) -o rank.exe main.o rank_support.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

clean: 
	rm *.o rank.exe