#ifndef TAGLIST_HPP
#define TAGLIST_HPP

#include <list>
#include "tag.hpp"

class TagList {
private:
  std::list<Tag> tags_list;

public:
  TagList ();
};

#endif
