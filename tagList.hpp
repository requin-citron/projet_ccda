#ifndef TAGLIST_HPP
#define TAGLIST_HPP

#include <list>
#include <string>
#include "tag.hpp"
//#include "interaction.hpp"

class Interaction;
class Tag;
//!class de tout les tags
/*!
  permet de stocker tout les tags existant dans le context
*/
class TagList {
private:
  //! list de pointeur de tag
  std::list<Tag*> tags_list;

public:
  //!constructeur
  TagList ();
  //!destructeur
  ~TagList();
  //! recupere un pointeur sur un tag
  /*!
    si le tag existe deja on renvois sont pointeur sinon on crée le nouveau tag et on renvois un pointeur sur ce nouveau tag
    \param name nom du tag
    \param inte pointeur sur l'interaction qui veux le tag
    \return pointeur sur Tag
  */
  Tag* getTag(std::string name, Interaction *inte);
  //!recupere la list de tout les tags existant
  /*!
    \return pointer sur une list de pointeur de tag
  */
  std::list<Tag*>* getTagList();
  //! récupére un tag dans la list
  /*!
    \param name nom du tag que l'on recherche
    \return pointeur sur tag si il existe NULL sinon
  */
  Tag* findTag(std::string name);
  //! suprime un tag
  /*!
    suprime le tag ainsi que toutes ses dependances
    \param name nom du tag
    \warning supprime toutes les interactions relie a ce tag
  */
  void eraseTag(std::string name);
};

#endif
