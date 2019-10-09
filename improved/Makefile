all: inf_int
inf_int: kms.o gonapps.o skh.o main.o
	g++ -g kms.o gonapps.o skh.o main.o -lpthread -o inf_int
kms.o: inf_int.h kms.cpp
	g++ -g -c kms.cpp -o kms.o
gonapps.o: inf_int.h gonapps.cpp
	g++ -g -c gonapps.cpp -o gonapps.o
skh.o: inf_int.h skh.cpp
	g++ -g -c skh.cpp -o skh.o
main.o: inf_int.h main.cpp
	g++ -g -c main.cpp -o main.o
clean:
	rm -rf *.o inf_int
