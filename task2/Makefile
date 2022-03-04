CC=g++
DEPS=select_support.h ../task1/rank_support.h

make: main.o select_support.o ../task1/rank_support.o
	$(CC) -o select.exe main.o select_support.o ../task1/rank_support.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

clean: 
	rm *.o select.exe