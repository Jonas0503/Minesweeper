all: minesweeper

minesweeper: minesweeper.c
	gcc -g minesweeper.c -o minesweeper

clean:
	rm -f minesweeper
