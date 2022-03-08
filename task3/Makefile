CC=g++
DEPS=sparse_array.h ../task2/select_support.h ../task1/rank_support.h
CFLAGS=-std=c++20 -stdlib=libc++ -I ~/include 
LIB=-L ~/lib -lsdsl -ldivsufsort -ldivsufsort64

make: main.o sparse_array.o ../task2/select_support.o ../task1/rank_support.o
	$(CC) -o sparse_array.exe main.o sparse_array.o ../task2/select_support.o ../task1/rank_support.o $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean: 
	rm *.o sparse_array.exe