all: main.c
	g++ main.c -o wotexp -Wall

test:
	./wotexp 3 50 3 55
	./wotexp 0 100

clean:
	rm *.o wotexp *~
