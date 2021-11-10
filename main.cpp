#include "date.hpp"
#include "tagList.hpp"
#include "contact.hpp"
#include "contactCatalog.hpp"
#include "mainwindow.h"

#include <unistd.h>
#include <QApplication>

using namespace std;

void showHist(ContactCatalog *cata){
  for(auto &it: *(cata->getHist()->getLst())){
    cout <<"Hist:"<< it->first <<" "<< it->second.printAll()<< endl;
  }
}

void showHist(Contact *conta){
  for(auto &it: *(conta->getHist()->getLst())){
    cout <<"Hist:"<< it->first << endl;
  }
}

void showHist(Interaction *inte){
  for(auto &it: *(inte->getHist()->getLst())){
    cout <<"Hist1:"<< it->first << endl;
  }
}

void showTodo(std::pair<std::string,Date*>* magie){
  cout << "todo: " << magie->first << endl;
  if(magie->second != NULL)cout << "date: " << magie->second->print() << endl;
}

void showAll(std::list<Contact*>* magie){
    for(auto &it: *magie){
        cout << "Contact " << it->getId()<<" " << it->getFirstName() <<" "<< it->getLastName() <<" "<< it->getMail() << endl;
        cout << "contact hist ==========" << endl;
        showHist(it);
        cout << "contact hist ==========end" << endl;
        for(auto &it1 : *it->getInteractionLst()){
            cout << it->getFirstName() <<"|"<< it1->getContenu() <<endl;
            cout << "interaction hist ===========" << endl;
            showHist(it1);
            cout << "interaction hist ===========end" << endl;
            for(auto &it2: *it1->getTags()){
                cout << "ID " << it1->getId() << " TAGS: " << it2->getName() << endl;
            }
        }
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
  cout << "azeazeazezaezae" << endl;
  chevalo->eraseInteraction(*it);
  cout << "azeazeazezaezae" << endl;

  //on suprr la dernière
  it = chevalo->getInteractionLst()->end();
  it--;
  cout << "azeazeazezaezae" << endl;
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
  cout << "testCatalog--------------------------------------------" << endl;
  ContactCatalog cata;
  cata.addContact("kleman","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
  cata.addContact("kleman1","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
  cata.addContact("kleman2","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
  auto it = cata.getContactLst()->begin();
  auto end = cata.getContactLst()->end();
  while(it!=end){
    cata.eraseContact(*it++);
  }
  showHist(&cata);
  cout << "testCatalog----------------------------------------------END" << endl;
}

void testDate() {
    cout << "testDate-----------------------------------------" << endl;
    Date *d1, *d2;

    d1 = new Date();
    d2 = new Date();
    std::cout <<d1->day()<<"-"<<d1->mon()<<"-"<<d1->year()<<"-"<<d1->hour()<<"-"<<d1->min()<<"-"<<d1->sec()<< std::endl;
    std::cout << *d1 <<" "<< *d2 <<" "<<
        (*d1==*d2) <<" "<< (*d1!=*d2) <<" "<< (*d1>=*d1) <<" "<< (*d1<=*d1) << std::endl;
    delete d1;
    delete d2;

    d1 = new Date();
    sleep(3);
    d2 = new Date();
    std::cout << *d1 <<" < "<< *d2 <<" = "<< ((*d1<*d2)?"vrai":"faux") << std::endl;
    std::cout << *d1 <<" > "<< *d2 <<" = "<< ((*d1>*d2)?"vrai":"faux") << std::endl;
    std::cout << *d1 <<" <= "<< *d2 <<" = "<< ((*d1<=*d2)?"vrai":"faux") << std::endl;
    std::cout << *d1 <<" >= "<< *d2 <<" = "<< ((*d1>=*d2)?"vrai":"faux") << std::endl;
    delete d1;
    delete d2;
    cout << "testDate--------------------------------------END" << endl;
}

void testTodo(){
  cout << "testTodo -----------------------------"<<endl;

  TagList tags_lst;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", &tags_lst);
  chevalo->addInteraction("@todo kamion @date 12/12/2001\n@todo magie","pwn");
  showHist(chevalo);
  for(auto &it:*(chevalo->getInteractionLst())){
    for(auto &od: *(it->getTodo())){
        showTodo(od);
    }
  }
  delete chevalo;
  cout << "testTodo -----------------------------END"<<endl;
}

void testDBSave(){
    cout << "testDBSave ------------------------------------------------" << endl;
    ContactCatalog cata;
    cata.addContact("kleman","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
    cata.addContact("kleman1","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
    cata.addContact("kleman2","chevalo", "aze", "aze@gmail.com", "0605040302", "/tmp/aze");
    Contact *c = *(cata.getContactLst()->begin());
    c->addInteraction("cinema ", "relou");
    c->addInteraction("manger\n@todo kamion et un autre @date 12/12/2001\n@todo magie", "Gigarelou");
    c->addInteraction("@todo test @date 12/00/2002\n@todo kamion123", "relou");
    c = *(++cata.getContactLst()->begin());
    c->addInteraction("eza", "hh");
    c->addInteraction("ggg", "hh");
    c->addInteraction("aze", "relou");
    cata.saveDataBase();
    cout << "testDBSave --------------------------------------------END" << endl;
}

void testDBImport(){
    cout << "testDBImport ------------------------------------------------" << endl;
    ContactCatalog cata;
    cata.loadDataBase();

    cout << "global hist ============" << endl;
    showHist(&cata);
    cout << "global hist ============end" << endl;
    showAll(cata.getContactLst());
    cout << "testDBImport --------------------------------------------END" << endl;
}

//tests cases
int main(int argc, char *argv[]) {
  TagList t;
  contactInteractionTestCase(&t);
  tagListTestCase();
  tagListEraseAllTagsTestCase();
  InteractionEraseTag();
  testHistLocal();
  testCatalog();
  testDate();
  testTodo();
  testDBSave();
  testDBImport();
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  //return a.exec();
  return 0;
}
