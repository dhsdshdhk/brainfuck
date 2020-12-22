all: bfi

bfi: bfi.c
	gcc -o bfi bfi.c -Wall -O3

clean: bfi.c
	rm bfi