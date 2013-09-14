all: main.c
	g++ main.c -o wotexp

test:
	./wotexp 3 40

clean:
	rm *.o wotexp
