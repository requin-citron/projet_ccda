#include "contactCatalog.hpp"

ContactCatalog::ContactCatalog(){
  this->local_hist = new HistLocal();
}

ContactCatalog::~ContactCatalog(){
  delete this->local_hist;
  for(auto &it: this->contact_lst){
    delete it;
  }
}

void ContactCatalog::addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture){
  Contact *c = new Contact(firstName, lastName, enterprise, mail, phone, pathPicture, &(this->tag_lst));
  this->local_hist->insertHist(c,CREATE_CONTACT);
  this->contact_lst.push_back(c);
}

std::list<Contact*>* ContactCatalog::getContactLst(){
  return &(this->contact_lst);
}

HistLocal *ContactCatalog::getHist(){
  return this->local_hist;
}

void ContactCatalog::eraseContact(Contact *c){
  this->local_hist->insertHist(c,DELETE_CONTACT);
  delete c;
  this->contact_lst.remove(c);
}
