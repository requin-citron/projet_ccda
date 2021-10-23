#ifndef TAG_HPP
#define TAG_HPP
#include <list>
#include <string>
#include "interaction.hpp"

class Interaction;

//! class des tags
/*!
  permet de stocker un tag ainsi que toutes les interactions reliées à ce tag
*/
class Tag {
private:
  //! nom du tag
  std::string name;
  //! liste de pointeur d'interaction appartenant aux tags
  std::list<Interaction*> interaction_lst;
public:
  //! constructeur
  /*!
    le constructeur à besoin d'un nom et d'un pointeur sur une interaction
    \param name nom du tag
    \param interac pointeur sur l'interaction qui utilise le tag
  */
  Tag (std::string name,Interaction* interac);
  //! destructeur
  ~Tag();
  //! ajout d'une interaction aux tags déjà existant
  /*!
    \param pointeur sur l'interaction qui veut s'ajouter aux tags
  */
  void addInteraction(Interaction* inte);
  //! récupére le nom du tag
  /*!
    \return nom du tag
  */
  std::string getName();
  //! revoie un pointeur sur la liste des interactions qui ont ce tag
  /*!
    \return pointeur d'une liste de pointeurs sur des interactions
  */
  std::list<Interaction*>* getInteraction();
  //! permet de supprimer un pointeur sur une interaction
  /*!
    \param inte pointeur de l'interaction à enlever de la liste d'interaction
  */
  void unlinkInteraction(Interaction * inte);
};


#endif
