#include "contactCatalog.hpp"

ContactCatalog::ContactCatalog(){}

ContactCatalog::~ContactCatalog(){
  for(auto &it: this->contact_lst){
    delete it;
  }
}

void ContactCatalog::addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture){
  Contact *c = new Contact(firstName, lastName, enterprise, mail, phone, pathPicture, &(this->tag_lst));
  this->contact_lst.push_back(c);
}

std::list<Contact*>* ContactCatalog::getContactLst(){
  return &(this->contact_lst);
}
