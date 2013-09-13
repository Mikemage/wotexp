all: main.c
	g++ main.c -o wotexp

test:
	./wotexp 3 40 -p

clean:
	rm *.o wotexp
