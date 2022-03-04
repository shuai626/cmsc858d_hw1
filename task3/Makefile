CC=g++
DEPS=sparse_array.h ../task2/select_support.h ../task1/rank_support.h

make: main.o sparse_array.o ../task2/select_support.o ../task1/rank_support.o
	$(CC) -o sparse_array.exe main.o sparse_array.o ../task2/select_support.o ../task1/rank_support.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

clean: 
	rm *.o sparse_array.exe