CC=g++
CXXFLAG=-Wall
LIBS=
RM=rm



all: main
main: interaction.cpp contact.cpp tag.cpp 
		$(CC) $(CXXFLAG) $(LIBS) interaction.cpp contact.cpp tagList.cpp tag.cpp -o main
clear:
		$(RM) main
