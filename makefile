# This is the makefile for the solution to the important message
# coding challenge by visual concepts

FILES = imp_mess_soln.c imp_mess_soln.h
CC = gcc
DEBUG = -g
CFLAGS = -Wall -Wshadow -ansi -pedantic $(DEBUG)

all:
	$(CC) $(CFLAGS) $(FILES) -o ImportantMessage

clean:
	rm ImportantMessage

tar:
	tar czvf imp_mess_soln.tar imp_mess_soln.*