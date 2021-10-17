#include "interaction.hpp"



void Interaction::initDate(){
  this->contenu = "";
  time_t tn = time(NULL);
  *(this->date) = tm(*localtime(&tn));
}

Interaction::Interaction(std::string contenu,Contact *attach_contact, TagList *tag_lst){
  this->local_hist = new HistLocal();
  if(this->tag_list == NULL){
    this->tag_list = tag_lst;
  }
  this->initDate();
  this->target = attach_contact;
  this->contenu = contenu;
  this->id = this->target->getInteractionId();
  this->local_hist->insertHist(this->target, this, ADD_INTERACTION);
}

Interaction::~Interaction(){
  delete this->local_hist;
  delete this->date;
  this->unlinkAll();
}

void Interaction::unlinkAll(){
  this->target->unlinkInteraction(this);
  //this->tags_lst.erase(this->tags_lst.begin(), this->tags_lst.end());
  std::list<Tag*>::iterator it = this->tags_lst.begin();
  std::list<Tag*>::iterator end = this->tags_lst.end();
  while(it != end){
    (*it++)->unlinkInteraction(this);
  }
}


void Interaction::setContenu(std::string magie){
  this->contenu = magie;
  this->local_hist->insertHist(this->target,this, CHANGE_CONTENUE);
}

void Interaction::setDate(struct tm &dt){
  *(this->date) = dt;
}

void Interaction::addTag(std::string tag){
  if(this->tag_list == NULL){
    std::cerr << "you need ton link tag list to use addTag" << std::endl;
    exit(2);
  }
  Tag *tmp = this->tag_list->getTag(tag, this);
  this->tags_lst.push_back(tmp);
  this->local_hist->insertHist(this->target,this, ADD_TAG);
}

HistLocal *Interaction::getHist(){
  return this->local_hist;
}

size_t Interaction::getId(){
  return this->id;
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

//peut etre rajouter un flag en cas d'erreur
void Interaction::unlinkTag(std::string name){
  std::list<Tag*>::iterator it = this->tags_lst.begin();
  std::list<Tag*>::iterator end = this->tags_lst.end();
  while(it != end){
    if((*it)->getName() == name){
      break;
    }
    it++;
  }
  if(it != end){
    (*it)->unlinkInteraction(this);
    this->tags_lst.erase(it);
  }
  this->local_hist->insertHist(this->target,this, DELETE_TAG);
}
