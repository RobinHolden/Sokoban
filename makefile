CFLAGS=-g -Wall -fsanitize=address
LDFLAGS=-lm
CC=gcc

sokoban: main.o lectureTableau.o affichageTableau.o util.o deplacement.o io.o retourArriere.o positionObjectifs.o sauvegarde.o
	${CC} -o $@ ${CFLAGS} $^ ${LDFLAGS}
.c.o:
	${CC} ${CFLAGS} -c $<
clean:
	rm -f sokoban
	rm -f *.o
