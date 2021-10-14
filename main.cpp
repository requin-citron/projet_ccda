#include "tagList.hpp"
#include "contact.hpp"

using namespace std;

void contactShowInteraction(Contact *conta){
  int c = 0;
  for(auto &it: *conta->getInteractionLst()){
    cout << conta->getFirstName() << " Interaction n°" << c << " "<<it->getContenu() << endl;
    c++;
  }
}

void contactInteractionTestCase(TagList *tags_lst){
  cout << "contactInteractionTestCase ---------------------------"<<endl;
  Tag *t;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar");
  cout << *chevalo << endl;
  chevalo->addInteraction("Interaction1","todo", tags_lst);
  chevalo->addInteraction("Interaction2","todo", tags_lst);
  chevalo->addInteraction("Interaction3","fini", tags_lst);
  chevalo->addInteraction("Interaction4","fini", tags_lst);
  list<Interaction*>::iterator it = chevalo->getInteractionLst()->begin();

  chevalo->eraseInteraction(*it);

  contactShowInteraction(chevalo);
  delete chevalo;
  cout << "contactInteractionTestCase END -----------------------"<<endl;
}


int main(int argc, char const *argv[]) {
  Contact *chevalo = new Contact("eva", "rodrigues", "pornhub", "chevalo@chevalo.com", "01020304", "blabla");
  Contact *chevalo1 = new Contact("klemou", "aze", "pornhub", "chevalo@chevalo.com", "01020304", "blabla");
  chevalo->print_debug();
  cout << "==========================="<<endl;
  cout << *chevalo;
  cout << "==========================="<<endl;
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
    cout <<"Interactions: " << it->getContenu() << " from "<< it->getContact()->getFirstName() <<endl;
  }
  delete chevalo;
  delete chevalo1;
  return 0;
}
