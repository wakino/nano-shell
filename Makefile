.PHONY: all
all: nanoShell.out

nanoShell.out: nanoShell.o howToUse.o
	gcc -o nanoShell.out nanoShell.o howToUse.o

nanoShell.o: nanoShell.c
	gcc -c nanoShell.c

howToUse.o: howToUse.c
	gcc -c howToUse.c


.PHONY: clean
clean:
	rm -rf *.o
