#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include<string>
#include<iostream>
#include<list>
#include "contact.hpp"
#include "tag.hpp"
#include "tagList.hpp"

class Contact;
class Tag;
class TagList;
class Interaction {
private:
  std::string contenu;
  struct tm *date = new tm;
  Contact *target = NULL;
  std::list<Tag*> tags_lst;
  TagList *tag_list = NULL;


  void initDate();
  friend std::ostream& operator<<(std::ostream &os, Interaction &inte);

public:
  Interaction(std::string contenu, Contact *attach_contact, TagList* tag_lst=NULL);
  Interaction();
  ~Interaction();
  std::string getContenu();
  void setDate(struct tm &dt);
  void addTag(std::string tag);
  std::list<Tag*>* getTags();
  struct tm getDate();
  Contact* getContact();

  void unlinkAll();

};

#endif
