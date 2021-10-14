#ifndef TAG_HPP
#define TAG_HPP
#include <list>
#include <string>
#include "interaction.hpp"




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
  void unlinkInteraction(Interaction * inte);
};


#endif
