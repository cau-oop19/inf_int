CFLAGS := -g
#CFLAGS += -fsanitize=address
all: inf_int
inf_int: kms.o gonapps.o skh.o main.o
	g++ $(CFLAGS) kms.o gonapps.o skh.o main.o -o inf_int
kms.o: inf_int.h kms.cpp
	g++ $(CFLAGS) -c kms.cpp -o kms.o
gonapps.o: inf_int.h gonapps.cpp
	g++ $(CFLAGS) -c gonapps.cpp -o gonapps.o
skh.o: inf_int.h skh.cpp
	g++ $(CFLAGS) -c skh.cpp -o skh.o
main.o: inf_int.h main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o
clean:
	rm -rf *.o inf_int
