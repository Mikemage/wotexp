all: main.c
	g++ main.c -o wotexp -Wall

test:
	./wotexp 3 53 3 55

clean:
	rm *.o wotexp *~
