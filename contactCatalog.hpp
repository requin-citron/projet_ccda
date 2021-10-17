#ifndef CONTACTCATALOG_HPP
#define CONTACTCATALOG_HPP

#include <string>
#include <list>
#include "contact.hpp"
#include "tagList.hpp"

class ContactCatalog {
private:
  std::list<Contact*> contact_lst;
  TagList tag_lst;

public:
  ContactCatalog();
  ~ContactCatalog();
  void addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture);
  std::list<Contact*>* getContactLst();
};

#endif
