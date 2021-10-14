#include "contact.hpp"


Contact::Contact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture): firstName(firstName), lastName(lastName), enterprise(enterprise), mail(mail), phone(phone), pathPicture(pathPicture){}
Contact::~Contact(){
  for(auto &it: this->interaction_lst){
    delete it;
  }
}

void Contact::print_debug(){
  std::cerr << "firstName :" << this->firstName << std::endl;
  std::cerr << "lastName :" << this->lastName << std::endl;
  std::cerr << "enterprise :" << this->enterprise << std::endl;
  std::cerr << "mail :" << this->mail << std::endl;
  std::cerr << "phone :" << this->phone << std::endl;
  std::cerr << "pathPicture :" << this->pathPicture << std::endl;
  //std::cerr << "date :" << this->date << std::endl;
}

void Contact::setFirstName(std::string fn){
  this->firstName = fn;
}
void Contact::setLastName(std::string ln){
  this->lastName = ln;
}
void Contact::setEnterprise(std::string et){
  this->enterprise = et;
}
void Contact::setMail(std::string ml){
  this->mail = ml;
}
void Contact::setPhone(std::string ph){
  this->phone = ph;
}
void Contact::setPathPicture(std::string path){
  this->pathPicture = path;
}
void Contact::setDate(struct tm &da){
  this->date=da;
}
void Contact::addInteraction(std::string contenue){
  Interaction *inte = new Interaction(contenue, this, NULL);
  this->interaction_lst.push_back(inte);
}
void Contact::addInteraction(std::string contenue, std::string tag, TagList *tag_lst){
  Interaction *inte = new Interaction(contenue, this, tag_lst);
  inte->addTag(tag);
  this->interaction_lst.push_back(inte);
}

std::list<Interaction*>* Contact::getInteractionLst(){
  return &(this->interaction_lst);
}
std::string Contact::getFirstName(){
  return this->firstName;
}
std::string Contact::getLastName(){
  return this->lastName;
}
std::string Contact::getEnterprise(){
  return this->enterprise;
}
std::string Contact::getMail(){
  return this->mail;
}
std::string Contact::getPhone(){
  return this->phone;
}
std::string Contact::getPathPicture(){
  return this->pathPicture;
}
struct tm Contact::getDate(){
  return this->date;
}

std::ostream& operator<<(std::ostream &os, Contact &curr){
  os << "firstName :" << curr.getFirstName() << std::endl;
  os << "lastName :" << curr.getLastName() << std::endl;
  os << "enterprise :" << curr.getEnterprise() << std::endl;
  os << "mail :" << curr.getMail() << std::endl;
  os << "phone :" << curr.getPhone() << std::endl;
  os << "pathPicture :" << curr.getPathPicture() << std::endl;
  return os;
}

void Contact::eraseInteraction(Interaction *inte){
  this->interaction_lst.remove(inte);
}
