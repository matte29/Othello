
# don't echo the commands
MAKEFLAGS += --silent
#Variables
CFLAGS = -Wall -std=c++11
CC = g++

a.out: game.o othello.o othelloMain.o
		$(CC) $(CFLAGS) game.o othello.o othelloMain.o -o a.out

othelloMain.o: othelloMain.cc othello.h game.h
		$(CC) -c $(CFLAGS) othelloMain.cc -o othelloMain.o

othello.o: othello.cc othello.h piece.h colors.h game.h
		$(CC) -c $(CFLAGS) othello.cc -o othello.o

game.o: game.cc game.h
		$(CC) -c $(CFLAGS) game.cc -o game.o

piece.o: piece.cc piece.h
		$(CC) -c $(CFLAGS) piece.cc

clean: rm -rf *.o a.out 