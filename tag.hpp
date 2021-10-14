#ifndef TAG_HPP
#define TAG_HPP
#include <list>
#include <string>
#include "interaction.hpp"

/*
  Il n'y a pas de possibilité encore pour faire
  une recherche par tag il aurait était possible de faire un objet
  list tag qui permet de faire des pointeur pour faire récupérer tout
  les intéractions et donc les contact relier mais dans le futur
  nous utiliseron la BDD pour faire. Donc l'implementation attendera la BDD
*/





class Interaction;
class Tag {
private:
  std::string name;
  std::list<Interaction*> interaction_lst;


public:
  Tag (std::string name,Interaction* interac);
  ~Tag();
  void add(std::string);
  void addInteraction(Interaction* inte);
  std::string getName();
  std::list<Interaction*>* getInteraction();
  void eraseInteraction(Interaction * inte);
};


#endif
