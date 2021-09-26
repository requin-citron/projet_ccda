CC=g++
CXXFLAG=-Wall
LIBS=-lsqlite3
RM=rm



all: bdd_utils fiche_client
bdd_utils:bdd_utils.cpp
		$(CC) $(CXXFLAG) $(LIBS) bdd_utils.cpp -o bdd_utils
fiche_client:fiche_client.cpp
				$(CC) $(CXXFLAG) $(LIBS) fiche_client.cpp -o fiche_client
clear:
		$(RM) bdd_utils fiche_client
