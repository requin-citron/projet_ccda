CC=g++
CXXFLAG=-Wall
LIBS=-lsqlite3
RM=rm



all: main
main:bdd_utils.cpp fiche_client.cpp main.cpp
		$(CC) $(CXXFLAG) $(LIBS) bdd_utils.cpp fiche_client.cpp  main.cpp -o main
clear:
		$(RM) main
