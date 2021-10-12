#include "contact.hpp"
#include "tagList.hpp"


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
  os << "lastName :" << curr.getFirstName() << std::endl;
  os << "enterprise :" << curr.getEnterprise() << std::endl;
  os << "mail :" << curr.getMail() << std::endl;
  os << "phone :" << curr.getPhone() << std::endl;
  os << "pathPicture :" << curr.getPathPicture() << std::endl;
  return os;
}

void Contact::eraseInteraction(Interaction *inte){
  this->interaction_lst.remove(inte);
}


int main(int argc, char const *argv[]) {
  Contact *chevalo = new Contact("eva", "rodrigues", "pornhub", "chevalo@chevalo.com", "01020304", "blabla");
  Contact *chevalo1 = new Contact("klemou", "aze", "pornhub", "chevalo@chevalo.com", "01020304", "blabla");
  chevalo->print_debug();
  std::cout << "==========================="<<std::endl;
  std::cout << *chevalo ;
  std::cout << "==========================="<<std::endl;
  TagList tag_lst;
  chevalo->addInteraction("TestTest","pwn",&tag_lst);
  chevalo->addInteraction("Test1","reverse",&tag_lst);
  chevalo->addInteraction("Test2","pwn",&tag_lst);
  chevalo->addInteraction("Test3","cheval",&tag_lst);
  chevalo1->addInteraction("kamion","pwn",&tag_lst);
  chevalo1->addInteraction("aze","reverse",&tag_lst);
  chevalo1->addInteraction("eza","pwn",&tag_lst);
  chevalo1->addInteraction("asd","cheval",&tag_lst);
  for (auto &it: *chevalo->getInteractionLst()) {
    std::cout <<"Interactions: " << it->getContenu() << " from "<< it->getContact()->getFirstName() <<std::endl;
    for (auto &it1: *it->getTags()){
      std::cout << "Tags: " << it1->getName() << std::endl;
    }
  }
  for (auto &it:*tag_lst.getTagList()) {
    std::cout << "il exite le tag: " << it->getName() << std::endl;
  }
  std::cout << "on cherche tout les interaction et contact de pwn" << std::endl;
  tag_lst.eraseTag("pwn");
  std::cout << "erase" << std::endl;
  for (auto &it:*tag_lst.getTagList()) {
    std::cout << "il exite le tag: " << it->getName() << std::endl;
  }
  Tag* pwn_tag = tag_lst.findTag("pwn");
  if(pwn_tag == NULL){
    std::cout << "le tag n'existe pas" << std::endl;
  }else{
    for(auto &it:*pwn_tag->getInteraction()){
        std::cout << "contenue: " << it->getContenu() << " ";
        std::cout << "Contact: " << it->getContact()->getLastName() << std::endl;
    }
  }
  delete chevalo1;
  delete chevalo;
  return 0;
}
