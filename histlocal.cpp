#include "histlocal.hpp"


HistLocal::HistLocal(){};

void HistLocal::insertHist(Contact *conta, char flag){
  std::string tmp = "Contact N "+std::to_string(conta->getId()) + " ";
  switch (flag) {
    case CHANGE_LAST_NAME:
      tmp += "Change name to "+conta->getLastName();
  }
  std::pair<std::string, struct tm> p;
  p.first = tmp;
  struct tm aze;
  p.second =aze;
  this->hist_lst.push_back(p);
}



void HistLocal::insertHist(Contact *conta, Interaction *inte, char flag){
  std::string tmp = "Contact N "+std::to_string(conta->getId()) + " ";
  tmp += "interaction N "+ std::to_string(inte->getId()) + " ";
  switch (flag) {
    case CHANGE_LAST_NAME:
      tmp += "Change name to "+conta->getLastName();
  }
  std::pair<std::string, struct tm> p;
  p.first = tmp;
  struct tm aze;
  p.second =aze;
  this->hist_lst.push_back(p);
}

std::list<std::pair<std::string, struct tm>>* HistLocal::getLst(){
  return &(this->hist_lst);
}
