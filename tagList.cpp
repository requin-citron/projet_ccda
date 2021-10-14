#include "tagList.hpp"

TagList::TagList(){
  this->size = 0;
}
TagList::~TagList(){
std::list<Tag*>::iterator it = this->tags_list.begin();
std::list<Tag*>::iterator end = this->tags_list.end();
  while(it != end){
    delete (*it++);
  }
}

Tag *TagList::getTag(std::string name, Interaction *inte){
    for(auto &it:this->tags_list){
      if(it->getName() == name){
        it->addInteraction(inte);
        return it;
      }
    }
    Tag *tmp = new Tag(name, inte);
    this->tags_list.push_back(tmp);
    return tmp;
}
std::list<Tag*>* TagList::getTagList(){
  return &(this->tags_list);
}

Tag* TagList::findTag(std::string name){
  for(auto &it:this->tags_list){
    if(it->getName() == name){
      return it;
    }
  }
  return NULL;
}


void TagList::eraseTag(std::string name){
  for (auto &it:this->tags_list) {
    if(it->getName() == name){
      delete it;
      this->tags_list.remove(it);
      return;
    }
  }
}
