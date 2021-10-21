CC=g++
CXXFLAG=-Wall
LIBS=
RM=rm



all: main
main: tagList.o tag.o interaction.o histlocal.o date.o contactCatalog.o contact.o main.o
		$(CC) $(CXXFLAG) $(LIBS) $^ -o main
main.o:main.cpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
tagList.o:tagList.cpp tagList.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
tag.o:tag.cpp tag.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
interaction.o:interaction.cpp interaction.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
histlocal.o:histlocal.cpp histlocal.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
date.o:date.cpp date.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
contactCatalog.o:contactCatalog.cpp contactCatalog.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
contact.o:contact.cpp contact.hpp
		$(CC) $(CXXFLAG) $(LIBS) -c $<
clean: clean_objet
		$(RM) main
clean_objet:
		$(RM) *.o
doc:
	doxygen
