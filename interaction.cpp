#include "interaction.hpp"


Interaction::Interaction(std::string contenu,Contact *attach_contact, TagList *tag_lst){
  this->local_hist = new HistLocal();
  if(this->tag_list == NULL){
    this->tag_list = tag_lst;
  }
  this->target = attach_contact;
  this->contenu = contenu;
  this->parser();
  this->id = this->target->getInteractionId();
  this->local_hist->insertHist(this->target, this, ADD_INTERACTION);
}

Interaction::Interaction(size_t id, std::string contenu,Contact *attach_contact, TagList *tag_lst){
  this->local_hist = new HistLocal();
  if(this->tag_list == NULL){
    this->tag_list = tag_lst;
  }
  this->target = attach_contact;
  this->contenu = contenu;
  this->parser();
  this->id = id;
  this->target->setInteractionId(id+1);
}

Interaction::~Interaction(){
  delete this->local_hist;
  this->unlinkAll();
  //destroy todo_lst;
  this->destroy_lst_todo();
}

void Interaction::unlinkAll(){
  this->target->unlinkInteraction(this);
  //this->tags_lst.erase(this->tags_lst.begin(), this->tags_lst.end());
  std::list<Tag*>::iterator it = this->tags_lst.begin();
  std::list<Tag*>::iterator end = this->tags_lst.end();
  Tag * curr;
  while(it != end){
    curr = *it++;
    curr->unlinkInteraction(this);
  }
}

void Interaction::setContenu(std::string magie, bool hist){
  this->contenu = magie;
  this->parser();
  if(hist)this->local_hist->insertHist(this->target,this, CHANGE_CONTENUE);
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

void Interaction::addTagUnLog(std::string tag){
  if(this->tag_list == NULL){
    std::cerr << "you need ton link tag list to use addTag" << std::endl;
    exit(2);
  }
  Tag *tmp = this->tag_list->getTag(tag, this);
  this->tags_lst.push_back(tmp);
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
  return os;
}

std::list<Tag*>* Interaction::getTags(){
  return &(this->tags_lst);
}


Contact* Interaction::getContact(){
  return this->target;
}

std::string Interaction::getFormat(){
    std::string ret=this->contenu;
    for(size_t i=0;i<this->contenu.length();i++){
        if(this->contenu[i] == '\n') ret[i]='-';
    }
    if(ret.length()>=30){
        ret = ret.substr(0,30) + "...";
    }
    ret = "\tInter ("+std::to_string(this->id)+")\n"+ret;
    return ret;
}

//peut etre rajouter un flag en cas d'erreur
void Interaction::unlinkTag(std::string name){
  std::list<Tag*>::iterator it = this->tags_lst.begin();
  std::list<Tag*>::iterator end = this->tags_lst.end();
  Tag *curr;
  while(it != end){
    curr = *it;
    if(curr->getName() == name){
      break;
    }
    it++;
  }
  if(it != end){
    curr = *it;
    curr->unlinkInteraction(this);
    this->tags_lst.erase(it);
  }
  this->local_hist->insertHist(this->target,this, DELETE_TAG);
}

std::pair<std::string,Date*>* Interaction::treat(std::string s){
  std::pair<std::string,Date*>* r = new std::pair<std::string,Date*>;
  ///////////////////////////////////////
  std::string magie = "";
  for(size_t t=0; t<s.length(); t++){
    if(s[t] == '\0' || s[t] == '\r' || s[t] == '@' || s[t] == '\n'){
        break;
    }
    magie+=s[t];
  }
  /////////////////////////////////////////
  r->first = magie;
  size_t date = s.find("@date");
  if (date!=std::string::npos && s.size()>=date+16){
      r->second = new Date(s.substr(date+6));
  }
  else{
      r->second = NULL;
  }
  return r;
}

void Interaction::parser(){
  this->destroy_lst_todo();
  std::stringstream ss( this->contenu );
  std::string tmp;
  while (getline(ss,tmp,'\n'))
      if (tmp.length()>6 && tmp.substr(0,6)=="@todo ")
          this->todo_lst.push_back(treat(tmp.substr(6)));
}

void Interaction::destroy_lst_todo(){
  //destroy todo_lst
  //todo_lst.clear();
  auto it = this->todo_lst.begin();
  auto end  = this->todo_lst.end();
  while(it != end){
     if((*it)->second != NULL)delete (*it)->second;
     delete (*it++);
  }
  this->todo_lst.clear();
}

std::list<std::pair<std::string,Date*>*>* Interaction::getTodo(){
  return &(this->todo_lst);
}

void Interaction::mergeTag(std::list<std::string> *lst){
    bool flag;
    auto it = this->tags_lst.begin();
    auto end = this->tags_lst.end();
    std::list<std::string>::iterator it1;
    std::list<std::string>::iterator end1;

    while(it != end){
        flag=false;
        it1=lst->begin();
        end1=lst->end();
        while(it1!=end1){
            if((*it)->getName() == *it1){
                flag=true;
            }
            it1++;
        }
        if(flag == false){
            this->unlinkTag((*it++)->getName());
        }
        it++;
    }

    it1=lst->begin();
    end1=lst->end();
    while(it1 != end1){
        it = this->tags_lst.begin();
        end = this->tags_lst.end();
        flag = true;
        while(it!=end){
            if((*it)->getName() == *it1) flag=false;
            it++;
        }
        if(flag == true){
            this->addTag(*it1);
        }
        it1++;
    }

}
