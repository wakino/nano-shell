.PHONY: all
all: nanoShell.out

objs = nanoShell.o howToUse.o

nanoShell.out: $(objs)
	gcc -o nanoShell.out $(objs)

nanoShell.o: nanoShell.c
	gcc -c nanoShell.c

howToUse.o: howToUse.c
	gcc -c howToUse.c


.PHONY: clean
clean:
	rm -rf *.o
