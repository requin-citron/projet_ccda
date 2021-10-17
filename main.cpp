#include "tagList.hpp"
#include "contact.hpp"
#include "contactCatalog.hpp"

using namespace std;

void showHist(Contact *conta){
  for(auto &it: *(conta->getHist()->getLst())){
    cout <<"Hist:"<< it.first << endl;
  }
}

void showHist(Interaction *inte){
  for(auto &it: *(inte->getHist()->getLst())){
    cout <<"Hist1:"<< it.first << endl;
  }
}

void contactShowInteraction(Contact *conta){
  int c = 0;
  for(auto &it: *conta->getInteractionLst()){
    cout << conta->getFirstName() << " Interaction n°" << c << " "<<it->getContenu() << " "<< it->getId() << endl;
    showHist(conta);
    c++;
  }
}

void contactInteractionTestCase(TagList *tags_lst){
  cout << "contactInteractionTestCase ---------------------------"<<endl;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", tags_lst);
  cout << *chevalo << endl;
  chevalo->addInteraction("Interaction1","todo");
  chevalo->addInteraction("Interaction2","todo");
  chevalo->addInteraction("Interaction3","fini");
  chevalo->addInteraction("Interaction4","fini");

  contactShowInteraction(chevalo);

  //on suppr la premiere interaction
  list<Interaction*>::iterator it = chevalo->getInteractionLst()->begin();
  chevalo->eraseInteraction(*it);

  //on suprr la dernière
  it = chevalo->getInteractionLst()->end();
  it--;

  chevalo->eraseInteraction(*it);
  cout << "---------------------" << endl;
  contactShowInteraction(chevalo);
  showHist(chevalo);
  delete chevalo;
  cout << "contactInteractionTestCase END -----------------------"<<endl;
}

void InteractionEraseTag(){
  cout << "InteractionEraseTag ---------------------------"<<endl;
  TagList tags_lst;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", &tags_lst);
  cout << *chevalo << endl;
  chevalo->addInteraction("Interaction1","todo");
  chevalo->addInteraction("Interaction2","todo");
  for(auto &it : *chevalo->getInteractionLst()){
    it->addTag("aze");
    it->addTag("kamion");
    showHist(it);
  }
  //on regarde les tags
  for (auto &it : *chevalo->getInteractionLst()) {
    cout << it->getContenu() << " tag : ";
    for(auto &it1 : *(it->getTags()) ){
      cout << it1->getName() << " ";
    }
    cout << endl;
  }
  list<Interaction*>::iterator it = chevalo->getInteractionLst()->begin();
  (*it)->unlinkTag("aze");
  (*it)->unlinkTag("todo");
  (*it)->unlinkTag("kamion");

  cout << "--------------------------------" << endl;
  //on regarde les tags
  for (auto &it : *chevalo->getInteractionLst()) {
    cout << it->getContenu() << " tag : ";
    for(auto &it1 : *(it->getTags()) ){
      cout << it1->getName() << " ";
    }
    cout << endl;
  }
  showHist(chevalo);
  delete chevalo;
  cout << "InteractionEraseTag END -----------------------"<<endl;
}

void tagListTestCase(){
  cout << "tagListTestCase -----------------------" << endl;
  TagList t;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", &t);
  Contact *chevalo1 = new Contact("kleman-667", "l3-667", "sans23.re", "667@gmail.com","0605040302", "/tmp/kamtar", &t);
  chevalo->addInteraction("Interaction1" , "todo" );
  chevalo->addInteraction("Interaction2" , "fini" );
  chevalo->addInteraction("Interaction3" , "fini" );

  chevalo1->addInteraction("Interaction4" , "todo" );
  chevalo1->addInteraction("Interaction5" , "fini" );
  chevalo1->addInteraction("Interaction6" , "fini" );
  contactShowInteraction(chevalo);
  contactShowInteraction(chevalo1);
  cout << "erase" << endl;
  t.eraseTag("fini");

  contactShowInteraction(chevalo);
  contactShowInteraction(chevalo1);

  showHist(chevalo);
  showHist(chevalo1);
  delete chevalo;
  delete chevalo1;
  cout << "tagListTestCase ----------------------- END" << endl;
}

void tagListEraseAllTagsTestCase(){
  cout << "tagListEraseAllTagsTestCase -----------------------" << endl;
  TagList t;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", &t);
  Contact *chevalo1 = new Contact("kleman-667", "l3-667", "sans23.re", "667@gmail.com","0605040302", "/tmp/kamtar", &t);
  chevalo->addInteraction("Interaction1" , "todo" );
  chevalo->addInteraction("Interaction2" , "fini" );
  chevalo->addInteraction("Interaction3" , "fini" );

  chevalo1->addInteraction("Interaction4" , "todo" );
  chevalo1->addInteraction("Interaction5" , "fini" );
  chevalo1->addInteraction("Interaction6" , "fini" );
  contactShowInteraction(chevalo);
  contactShowInteraction(chevalo1);
  cout << "erase" << endl;
  t.eraseTag("fini");
  t.eraseTag("todo");

  contactShowInteraction(chevalo);
  contactShowInteraction(chevalo1);

  showHist(chevalo);
  showHist(chevalo1);
  delete chevalo;
  delete chevalo1;
  cout << "tagListEraseAllTagsTestCase ----------------------- END" << endl;
}

void testHistLocal(){
  cout << "testHistLocal -----------------------" << endl;
  TagList t;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", &t);
  chevalo->setLastName("Kamion");
  showHist(chevalo);
  delete chevalo;
  cout << "testHistLocal ----------------------- END" << endl;
}

void testCatalog(){
  ContactCatalog cata;
  cata.addContact("kleman","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
}
//tests cases
int main(int argc, char const *argv[]) {
  TagList t;
  contactInteractionTestCase(&t);
  tagListTestCase();
  tagListEraseAllTagsTestCase();
  InteractionEraseTag();
  testHistLocal();
  testCatalog();
  return 0;
}
