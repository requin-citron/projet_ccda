#ifndef FICHE_CLIENT_H
#define FICHE_CLIENT_H
#include <iostream>
#include <cstdlib>
#include <sqlite3.h>
typedef struct{
  std::string nom;
  std::string prenom;
  std::string entreprise;
  std::string mail;
  std::string telephone;
  std::string photo; //inchala on fait quoi un flux d'octet ?
  std::string date_creation;
} fiche;
void print_fiche(fiche *);
fiche create_fiche(std::string, std::string, std::string, std::string, std::string,std::string, std::string);
#endif
