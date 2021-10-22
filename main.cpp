#include "date.hpp"
#include "tagList.hpp"
#include "contact.hpp"
#include "contactCatalog.hpp"
#include <unistd.h>

using namespace std;


std::pair<std::string,Date*> treat(std::string s) {
    std::pair<std::string,Date*> r;
    r.first = s;
    size_t date = s.find("@date");
    if (date!=std::string::npos && s.size()>=date+16)
        r.second = new Date(s.substr(date+6,10));
    else
        r.second = NULL;
    return r;
}
std::list<std::pair<std::string,Date*>> parser(std::string s) {
    std::list<std::pair<std::string,Date*>> r;
    std::stringstream ss(s);
    std::string tmp;
    while (getline(ss,tmp,'\n'))
        if (tmp.substr(0,6)=="@todo ")
            r.push_back(treat(tmp.substr(6)));
    return r;
}
void destroy(std::list<std::pair<std::string,Date*>> lp) {
    for (auto& i : lp)
        if (i.second!=NULL)
            delete i.second;
}

void showHist(ContactCatalog *cata){
  for(auto &it: *(cata->getHist()->getLst())){
    cout <<"Hist:"<< it->first << endl;
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
  cout << "date: " << magie->second->print() << endl;
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

void testParser() {
    cout << "testParser-------------------------------------------" << endl;
    std::string s = "rdv aujourd’hui par tél., RAS.\n"
               "@todo Rappeler @date 19/10/2010\n"
               "@todo confirmer commande n°xyz\n";
    std::cout << s << std::endl;
    std::list<std::pair<std::string,Date*>> lp = parser(s);
    for (auto& i : lp)
        std::cout << i.first << "\n-> " << (i.second!=NULL?i.second->print():"NO DATE") << std::endl;
    destroy(lp);
    cout << "testParser------------------------------------------END" << endl;
}

void testTodo(){
  cout << "testTodo -----------------------------"<<endl;

  TagList tags_lst;
  Contact *chevalo = new Contact("kleman", "l3", "sans23.re", "commit.leaks@gmail.com","0605040302", "/tmp/kamtar", &tags_lst);
  chevalo->addInteraction("@todo kamion @date 12/12/2001","pwn");
  showHist(chevalo);
  for(auto &it:*(chevalo->getInteractionLst())){
    for(auto &od: *(it->getTodo())){
        showTodo(od);
    }
  }
  delete chevalo;
  cout << "testTodo -----------------------------END"<<endl;
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
  testDate();
  testParser();
  testTodo();
  return 0;
}
