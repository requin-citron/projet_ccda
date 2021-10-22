#include "histlocal.hpp"


HistLocal::HistLocal(){
};

HistLocal::~HistLocal(){
  for (auto &it: this->hist_lst) {
    delete it;
  }
};

void HistLocal::insertHist(Contact *conta, char flag){
  std::string tmp = "Contact N "+std::to_string(conta->getId()) + " ";
  switch (flag) {
    case CHANGE_LAST_NAME:
      tmp += "Change last name to "+conta->getLastName();
      break;
    case CHANGE_FIRST_NAME:
      tmp += "Change first name to "+conta->getFirstName();
      break;
    case CHANGE_ENTREPRISE_NAME:
      tmp += "Change entreprise name  to "+conta->getEnterprise();
      break;
    case CHANGE_MAIL:
      tmp += "Change mail to "+conta->getMail();
      break;
    case CHANGE_PHONE:
      tmp += "Change phone to "+conta->getPhone();
      break;
    case CHANGE_PATH_PICTURE:
      tmp += "Change picture path to "+conta->getPathPicture();
      break;
    case ADD_INTERACTION:
      tmp += "Add Interaction";
      break;
    case DELETE_INTERACTION:
      tmp += "Delete Interaction";
      break;
    case CREATE_CONTACT:
      tmp += "Creation";
      break;
    case DELETE_CONTACT:
      tmp += "Delete";
      break;
    default:
      tmp += "invalid flag " + std::to_string(flag);
  }
  std::pair<std::string, Date> *p = new std::pair<std::string, Date>;
  p->first = tmp;
  this->hist_lst.push_back(p);
}

void HistLocal::insertHist(Contact *conta, Interaction *inte, char flag){
  std::string tmp = "Contact N "+std::to_string(conta->getId()) + " ";
  tmp += "interaction N "+ std::to_string(inte->getId()) + " ";
  switch (flag) {
    case ADD_INTERACTION:
      tmp += "Creation";
      break;
    case CHANGE_CONTENUE:
      tmp += "Change Contenue";
      break;
    case DELETE_TAG:
      tmp += "Delete tag";
      break;
    case ADD_TAG:
      Tag *t = *(--inte->getTags()->end());
      tmp += "Add tag: " + t->getName();
  }
  std::pair<std::string, Date> *p = new std::pair<std::string, Date>;
  p->first = tmp;
  this->hist_lst.push_back(p);
}

std::list<std::pair<std::string, Date>*>* HistLocal::getLst(){
  return &(this->hist_lst);
}
