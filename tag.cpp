#include "tag.hpp"

Tag::Tag(std::string name,Interaction *interac){
  this->interaction_lst.push_back(interac);
  this->name = name;
}

std::string Tag::getName(){
  return this->name;
}
