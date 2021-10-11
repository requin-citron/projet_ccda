#include "interaction.hpp"


void Interaction::initDate(){
  this->contenu = "";
  time_t tn = time(NULL);
  *(this->date) = tm(*localtime(&tn));
}
Interaction::Interaction(std::string con):contenu(con){
  this->initDate();
}

Interaction::Interaction(){
    this->initDate();
}


std::string Interaction::getContenu(){
  return this->contenu;
}

void Interaction::setDate(struct tm &dt){
  *(this->date) = dt;
}

std::ostream& operator<<(std::ostream &os, Interaction &inte){
  os << "contenu: " << inte.getContenu() << std::endl;
  struct tm curr = inte.getDate();
  os << "year: " << (curr.tm_year + 1900) << std::endl;
  os << "month: " << curr.tm_mon << std::endl;
  os << "day: " << (curr.tm_mday ) << std::endl;
  return os;
}

struct tm Interaction::getDate(){
  return *(this->date);
}
