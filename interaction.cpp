#include "interaction.hpp"



void Interaction::initDate(){
  this->contenu = "";
  time_t tn = time(NULL);
  *(this->date) = tm(*localtime(&tn));
}
Interaction::Interaction(std::string contenu,Contact *attach_contact){
  this->initDate();
  this->target = attach_contact;
  this->contenu = contenu;
}
Interaction::~Interaction(){
  delete this->date;
  for(auto &it:this->tags_lst){
    delete it;
  }
}

Interaction::Interaction(){
    this->initDate();
}



void Interaction::setDate(struct tm &dt){
  *(this->date) = dt;
}
void Interaction::addTag(std::string tag){
  Tag *tmp = new Tag(tag, this);
  this->tags_lst.push_back(tmp);
}

std::string Interaction::getContenu(){
  return this->contenu;
}

std::ostream& operator<<(std::ostream &os, Interaction &inte){
  os << "contenu: " << inte.getContenu() << std::endl;
  struct tm curr = inte.getDate();
  os << "year: " << (curr.tm_year + 1900) << std::endl;
  os << "month: " << curr.tm_mon << std::endl;
  os << "day: " << (curr.tm_mday ) << std::endl;
  return os;
}

std::list<Tag*>* Interaction::getTags(){
  return &(this->tags_lst);
}
struct tm Interaction::getDate(){
  return *(this->date);
}

Contact* Interaction::getContact(){
  return this->target;
}
