#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include<string>
#include<iostream>
#include<list>
#include "contact.hpp"
#include "tag.hpp"
#include "tagList.hpp"
#include "histlocal.hpp"
#include "date.hpp"

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
  //!pointeur sur le contact qui a crée l'interaction
  Contact *target = NULL;
  //!list de pointeur de Tag les tag ne sont pas géré dans cet objet
  std::list<Tag*> tags_lst;
  //!pointeur sur la list global des tags
  TagList *tag_list = NULL;
  //!id local de interaction
  /*
    chaque interaction a un numéro qui commence a 0
    et qui s'incremente chaque contact a un espace d'addressage different donc l'id 0 est la première interaction de chaque contact
  */
  size_t id = 0;
  //! pointeur sur l'historique local
  HistLocal *local_hist = NULL;

  //!list de tuple d'un chaine et d'une date (les todo)
  std::list<std::pair<std::string,Date*>*> todo_lst;
  //! fonction interne qui traite les ligne pour les mettre dans un tuple
  std::pair<std::string,Date*>* treat(std::string s);
  //! fonction interne qui appelle treat des qu'une ligne contient todo
  void parser();
  //! supprime proprement le contenue de la todo list
  void destroy_lst_todo();
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
  //!destructeur qui ce détache des autres objet avant de ce supprimer
  ~Interaction();

  //! fonction qui renvoie le contenu d'une interaction
  std::string getContenu();
  //! fonction qui renvoie l'historique
  HistLocal *getHist();
  //! renvois un pointeur sur les tags de l'interaction
  std::list<Tag*>* getTags();
  //! renvois l'id de l'interaction
  size_t getId();
  //! renvois le contact relié a l'interaction
  Contact* getContact();
  //! renvois un pointeur sur la list de tuple de todo
  std::list<std::pair<std::string,Date*>*>* getTodo();

  //! fonction de modification du contenue
  void setContenu(std::string magie);
  //! fonction d'ajout de tag
  void addTag(std::string tag);

  //unlink all dependancies pointer
  //! supprime tout les pointeur des autres objet pointant sur this
  void unlinkAll();
  //unlink tag
  //! supprime un tag de l'interaction dans le supprimer
  void unlinkTag(std::string name);
};

#endif
