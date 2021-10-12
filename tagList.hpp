#ifndef TAGLIST_HPP
#define TAGLIST_HPP

#include <list>
#include <string>
#include "tag.hpp"
//#include "interaction.hpp"

class Interaction;
class Tag;
class TagList {
private:
  std::list<Tag*> tags_list;
  size_t size;

public:
  TagList ();
  ~TagList();
  Tag* getTag(std::string name, Interaction *inte);
  std::list<Tag*>* getTagList();
  Tag* findTag(std::string name);
  void eraseTag(std::string name);
};

#endif
