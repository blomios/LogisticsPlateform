all: main

main: main.o stock.o utils.o transporteur.o displayer.o reader.o semaphore.o portique.o
	gcc -o main main.o transporteur.o portique.o reader.o displayer.o semaphore.o stock.o utils.o -pthread -lm

main.o: Prg2.c main.h
	gcc -o main.o -c Prg2.c

portique.o: portique.c
	gcc -o portique.o -c portique.c

reader.o: reader.c
	gcc -o reader.o -c reader.c

transporteur.o: transporteur.c
	gcc -o transporteur.o -c transporteur.c

stock.o: stock.c
	gcc -o stock.o -c stock.c

utils.o: utils.c
	gcc -o utils.o -c utils.c

displayer.o: displayer.c
	gcc -o displayer.o -c displayer.c

semaphore.o: semaphore.c
	gcc -o semaphore.o -c semaphore.c