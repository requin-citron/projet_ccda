#include "tag.hpp"

Tag::Tag(std::string name,Interaction *interac){
  this->interaction_lst.push_back(interac);
  this->name = name;
}
Tag::~Tag(){
  std::list<Interaction*>::iterator it = this->interaction_lst.begin();
  std::list<Interaction*>::iterator end = this->interaction_lst.end();
  while(it != end){
    (*it)->unlinkAll();
    delete (*it++);
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

void Tag::eraseInteraction(Interaction *inte){
  this->interaction_lst.remove(inte);
}
