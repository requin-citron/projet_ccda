#include <iostream>
#include <cstdlib>
#include "fiche_client.hpp"
using namespace std;



void print_fiche(fiche *in){
  cout << in->nom <<" "<< in->prenom << " "<< in->entreprise << " " <<\
  in->mail << " "<< in->telephone<< " " << in->date_creation << endl;
}
fiche create_fiche(string nom, string prenom, string entreprise, string mail, string telephone, string date_creation){
  fiche ret;
  ret.nom = nom;
  ret.prenom = prenom;
  ret.entreprise = entreprise;
  ret.mail = mail;
  ret.telephone = telephone;
  ret.date_creation = date_creation;
  return ret;
}


int main(int argc, char const *argv[]) {
  fiche client = create_fiche("kleman","chevalo", "la fac", "test@example.com", "0605040302", "01-01-1971");
  print_fiche(&client);
  return 0;
}
