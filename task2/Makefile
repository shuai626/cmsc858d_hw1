CC=g++
DEPS=select_support.h ../task1/rank_support.h
CFLAGS=-std=c++20 -stdlib=libc++ -I ~/include 
LIB=-L ~/lib -lsdsl -ldivsufsort -ldivsufsort64

make: main.o select_support.o ../task1/rank_support.o
	$(CC) -o select.exe main.o select_support.o ../task1/rank_support.o $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean: 
	rm *.o select.exe