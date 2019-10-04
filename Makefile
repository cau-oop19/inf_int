all: inf_int
inf_int: kms.o gonapps.o skh.o main.o
	g++ kms.o gonapps.o skh.o main.o -o inf_int
kms.o: inf_int.h kms.cpp
	g++ -c kms.cpp -o kms.o
gonapps.o: inf_int.h gonapps.cpp
	g++ -c gonapps.cpp -o gonapps.o
skh.o: inf_int.h skh.cpp
	g++ -c skh.cpp -o skh.o
main.o: inf_int.h main.cpp
	g++ -c main.cpp -o main.o
clean: rm -rf *.o inf_int
