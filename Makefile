CC = gcc
CFLAGS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf `sdl-config -libs`
LDFLAGS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf `sdl-config -libs`
EXEC = Soko-Pacman
INC = ./include/
SRC = ./src/

all: Soko-Pacman clean

Soko-Pacman: editeur.o fichiers.o jeu.o main.o
	$(CC) -Wall -o Soko-Pacman editeur.o fichiers.o jeu.o main.o $(LDFLAGS)

editeur.o: $(SRC)editeur.c $(INC)editeur.h $(INC)fichiers.h $(INC)constantes.h
	$(CC) -Wall -o editeur.o -c $(SRC)editeur.c $(CFLAGS)
   
fichiers.o: $(SRC)fichiers.c $(INC)fichiers.h $(INC)constantes.h
	$(CC) -Wall -o fichiers.o -c $(SRC)fichiers.c $(CFLAGS)

jeu.o: $(SRC)jeu.c $(INC)jeu.h $(INC)constantes.h #$(INC)constantes.h
	$(CC) -Wall -o jeu.o -c $(SRC)jeu.c $(CFLAGS)

main.o: main.c $(INC)constantes.h $(INC)jeu.h $(INC)editeur.h $(INC)fichiers.h
	$(CC) -Wall -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

