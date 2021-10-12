#include "tag.hpp"

Tag::Tag(std::string name,Interaction *interac){
  this->interaction_lst.push_back(interac);
  this->name = name;
}
Tag::~Tag(){
  for(auto &it:this->interaction_lst){
    it->unlinkTarget();
    delete it;
  }
}

std::string Tag::getName(){
  return this->name;
}

void Tag::addInteraction(Interaction* inte){
  this->interaction_lst.push_back(inte);
}

std::list<Interaction*>* Tag::getInteraction(){
  return &(this->interaction_lst);
}
