all: main.c
	g++ main.c -o wotexp -Wall

test:
	./wotexp 3 40 3 49
	./wotexp 0 100

clean:
	rm *.o wotexp
