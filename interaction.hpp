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

//! class des interactions
/*!
  permet de stocker les interactions et les tags associés
*/
class Interaction {
private:
  //! variable privées
  std::string contenu;
  //! pointeur sur le contact qui a crée l'interaction
  Contact *target = NULL;
  //! liste de pointeur de Tag les tag ne sont pas gérés dans cet objet
  std::list<Tag*> tags_lst;
  //! pointeur sur la liste globale des tags
  TagList *tag_list = NULL;
  //! id local d'interaction
  /*!
    chaque interaction a un numéro qui commence a 0 et qui s'incremente chaque contact à un espace d'adressage différent donc l'id 0 est la première interaction de chaque contact
  */
  size_t id = 0;
  //! pointeur sur l'historique local
  HistLocal *local_hist = NULL;

  //! liste de tuple d'un chaine et d'une date (les todo)
  std::list<std::pair<std::string,Date*>*> todo_lst;
  //! fonction interne qui traite les lignes pour les mettre dans un tuple
  std::pair<std::string,Date*>* treat(std::string s);
  //! fonction interne qui appelle treat dès qu'une ligne contient todo
  void parser();
  //! supprime proprement le contenu de la todo liste
  void destroy_lst_todo();
  //! fonction d'affichage
  friend std::ostream& operator<<(std::ostream &os, Interaction &inte);

public:
  //! constructeur de la class
  /*!
    \param contenu string qui contient l'interaction
    \param attach_contact pointeur qui renvoie sur le contact qui a instancier l'interaction
    \param tag_lst permet de passer la liste de tags
    \warning il est nécessaire d'avoir une liste de tag pour pouvoir donner des tags à son interaction
  */
  Interaction(std::string contenu, Contact *attach_contact, TagList* tag_lst);
  //! constructeur de la class
  /*!
    \param id utilise quand on faire une importation par la db
    \param contenu string qui contient l'interaction
    \param attach_contact pointeur qui renvoie sur le contact qui a instancier l'interaction
    \param tag_lst permet de passer la liste de tags
    \warning il est nécessaire d'avoir une liste de tag pour pouvoir donner des tags à son interaction
  */
  Interaction(size_t id, std::string contenu, Contact *attach_contact, TagList* tag_lst);
  //! destructeur qui se détache des autres objets avant de se supprimer
  ~Interaction();

  //! fonction qui renvoie le contenu d'une interaction
  /*!
    \return contenue de l'interaction
  */
  std::string getContenu();
  //! fonction qui renvoie l'historique
  /*!
    \return pointeur sur l'historique
  */
  HistLocal *getHist();
  //! renvoie un pointeur sur les tags de l'interaction
  /*!
    \return pointeur sur les tags de l'interaction
  */
  std::list<Tag*>* getTags();
  //! renvoie l'id de l'interaction
  /*!
    \return id de l'interaction
  */
  size_t getId();
  //! renvoie le contact relié a l'interaction
  /*!
    \return pointeur sur le contact de l'interaction
  */
  Contact* getContact();
  //! renvoie un pointeur sur la liste des paires de todo
  /*!
    \return pointeur sur la list des paires de todo
  */
  std::list<std::pair<std::string,Date*>*>* getTodo();

  //! fonction de modification du contenu
  /*!
    \param magie chaine contenant la nouvelle interaction
  */
  void setContenu(std::string magie);
  //! fonction d'ajout de tag
  /*!
    \param tag nom du nouveau tag
  */
  void addTag(std::string tag);
  //! fonction d'ajout de tag non logee
  /*!
    \param tag nom du nouveau tag
  */
  void addTagUnLog(std::string tag);

  //! unlink all dependancies pointer
  //! supprime tous les pointeurs des autres objets pointant sur this
  void unlinkAll();
  //! unlink tag
  //! supprime un tag de l'interaction sans le supprimer
  /*!
    \param name nom du tag a unlink
  */
  void unlinkTag(std::string name);
};

#endif
