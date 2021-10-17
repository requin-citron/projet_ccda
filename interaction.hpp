#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include<string>
#include<iostream>
#include<list>
#include "contact.hpp"
#include "tag.hpp"
#include "tagList.hpp"
#include "histlocal.hpp"

class Contact;
class Tag;
class TagList;
class HistLocal;

//!class des intéractions
/*!
  permet de stocker les interaction et les tags
  associer
*/
class Interaction {
private:
  //!variable privées
  std::string contenu;
  struct tm *date = new tm;
  Contact *target = NULL;
  std::list<Tag*> tags_lst;
  TagList *tag_list = NULL;
  size_t id = 0;
  HistLocal *local_hist = NULL;
  //! initialise le membre date de l'objet avec la date actuelle
  /*!
  la fonction est privé elle est appellé que par le constructeur
  */
  void initDate();
  //! fonction d'affichage
  friend std::ostream& operator<<(std::ostream &os, Interaction &inte);

public:
  //! constructeur de la class
  /*!
    \param contenu string qui contient  l'interaction
    \param attach_contact pointeur qui renvoie sur le contact qui a instancier l'interaction
    \param tag_lst permé de passer la list de tag
    \warning il est une list de tag pour pouvoir donner des tag a sont interaction
  */
  Interaction(std::string contenu, Contact *attach_contact, TagList* tag_lst);
  ~Interaction();
  std::string getContenu();
  void setDate(struct tm &dt);
  void setContenu(std::string magie);
  void addTag(std::string tag);
  //! fonction qui renvoie l'historique
  HistLocal *getHist();
  std::list<Tag*>* getTags();
  size_t getId();
  struct tm getDate();
  Contact* getContact();

  //unlink all dependancies pointer
  void unlinkAll();
  //unlink tag
  void unlinkTag(std::string name);

};

#endif
