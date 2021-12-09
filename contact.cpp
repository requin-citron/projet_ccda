#include "contact.hpp"

size_t Contact::id_c = 0;

Contact::Contact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture,TagList *lst): firstName(firstName), lastName(lastName), enterprise(enterprise), mail(mail), phone(phone), pathPicture(pathPicture), tags_lst(lst){
  this->local_hist = new HistLocal();
  this->id = this->id_c;
  this->id_c ++;
}

Contact::Contact(size_t id,std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture,TagList *lst): id(id), firstName(firstName), lastName(lastName), enterprise(enterprise), mail(mail), phone(phone), pathPicture(pathPicture), tags_lst(lst){
  this->local_hist = new HistLocal();
    this->id_c = id+1;
}

Contact::~Contact(){
  delete this->local_hist;
  std::list<Interaction*>::iterator it = this->interaction_lst.begin();
  std::list<Interaction*>::iterator end = this->interaction_lst.end();
  while (it != end) {
    delete (*it++);
  }
}

void Contact::print_debug(){
  std::cerr << "firstName :" << this->firstName << std::endl;
  std::cerr << "lastName :" << this->lastName << std::endl;
  std::cerr << "enterprise :" << this->enterprise << std::endl;
  std::cerr << "mail :" << this->mail << std::endl;
  std::cerr << "phone :" << this->phone << std::endl;
  std::cerr << "pathPicture :" << this->pathPicture << std::endl;
}

void Contact::setFirstName(std::string fn){
  this->firstName = fn;
  this->local_hist->insertHist(this, CHANGE_FIRST_NAME);
}

void Contact::setLastName(std::string ln){
  this->lastName = ln;
  this->local_hist->insertHist(this, CHANGE_LAST_NAME);
}

void Contact::setEnterprise(std::string et){
  this->enterprise = et;
  this->local_hist->insertHist(this, CHANGE_ENTREPRISE_NAME);
}

void Contact::setMail(std::string ml){
  this->mail = ml;
  this->local_hist->insertHist(this, CHANGE_MAIL);
}

void Contact::setPhone(std::string ph){
  this->phone = ph;
  this->local_hist->insertHist(this, CHANGE_PHONE);
}

void Contact::setPathPicture(std::string path){
  this->pathPicture = path;
  this->local_hist->insertHist(this, CHANGE_PATH_PICTURE);
}

void Contact::addInteraction(std::string contenue){
  Interaction *inte = new Interaction(contenue, this, this->tags_lst);
  this->interaction_lst.push_back(inte);
  this->local_hist->insertHist(this, ADD_INTERACTION);
}

void Contact::setInteractionId(size_t id){
    this->interaction_id = id;
}

Interaction* Contact::addInteraction(std::string contenue, std::string tag){
  Interaction *inte = new Interaction(contenue, this, this->tags_lst);
  inte->addTag(tag);
  this->interaction_lst.push_back(inte);
  this->local_hist->insertHist(this, ADD_INTERACTION);
  return inte;
}


void Contact::addInteraction(size_t id, std::string contenue){
  Interaction *inte = new Interaction(id, contenue, this, this->tags_lst);
  this->interaction_lst.push_back(inte);
}

size_t Contact::getId(){
  return this->id;
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

HistLocal *Contact::getHist(){
  return this->local_hist;
}

size_t Contact::getInteractionId(){
  size_t ret = this->interaction_id;
  this->interaction_id++;
  return ret;
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

bool operator==(Contact const& a, Contact const& b) {
    if (a.id==b.id) return true;
    else return false;
}

void Contact::eraseInteraction(Interaction *inte){
  delete inte;
  this->local_hist->insertHist(this,DELETE_INTERACTION);
}

void Contact::unlinkInteraction(Interaction *inte){
  this->interaction_lst.remove(inte);
}
