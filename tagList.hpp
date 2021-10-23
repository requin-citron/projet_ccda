#ifndef TAGLIST_HPP
#define TAGLIST_HPP

#include <list>
#include <string>
#include "tag.hpp"
//#include "interaction.hpp"

class Interaction;
class Tag;
//! class de tous les tags
/*!
  permet de stocker tous les tags existant dans le contexte
*/
class TagList {
private:
  //! liste de pointeurs de tag
  std::list<Tag*> tags_list;

public:
  //! constructeur
  TagList ();
  //! destructeur
  ~TagList();
  //! récupère un pointeur sur un tag
  /*!
    si le tag existe déjà on renvoie son pointeur sinon on crée le nouveau tag et on renvoie un pointeur sur ce nouveau tag
    \param name nom du tag
    \param inte pointeur sur l'interaction qui veut le tag
    \return pointeur sur Tag
  */
  Tag* getTag(std::string name, Interaction *inte);
  //! récupère la liste de tous les tags existant
  /*!
    \return pointeur sur une liste de pointeur de tag
  */
  std::list<Tag*>* getTagList();
  //! récupére un tag dans la liste
  /*!
    \param name nom du tag que l'on recherche
    \return pointeur sur tag s'il existe, NULL sinon
  */
  Tag* findTag(std::string name);
  //! supprime un tag
  /*!
    supprime le tag ainsi que toutes ses dépendances
    \param name nom du tag
    \warning supprime toutes les interactions reliées à ce tag
  */
  void eraseTag(std::string name);
};

#endif
