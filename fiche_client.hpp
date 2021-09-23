#ifndef FICHE_CLIENT_H
#define FICHE_CLIENT_H
typedef struct{
  std::string nom;
  std::string prenom;
  std::string entreprise;
  std::string mail;
  std::string telephone;
  //strings photo; //inchala on fait quoi un flux d'octet ?
  std::string date_creation;
} fiche;

void print_fiche(fiche *);
fiche create_fiche(std::string, std::string, std::string, std::string, std::string, std::string);
#endif
