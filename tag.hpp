#ifndef TAG_HPP
#define TAG_HPP
#include <list>
#include <string>
#include "interaction.hpp"




class Interaction;

//! Class des tags
/*!
  Permet de stocker un tag ainsi que toutes les interaction relié a ce tag
*/
class Tag {
private:
  //! nom du tag
  std::string name;
  //! list de pointeur d'interaction apartenant aux tag
  std::list<Interaction*> interaction_lst;
public:
  //! constructeur
  /*!
    Le constructeur a besoin d'un nom et d'un pointeur sur une interaction
    \param name nom du tag
    \param interac pointeur sur l'interaction qui utilise le tag
  */
  Tag (std::string name,Interaction* interac);
  //! destructeur
  ~Tag();
  //! ajoue d'une interaction aux tag deja existant
  /*!
    \param pointeur sur l'interaction qui veux d'ajouter aux tag
  */
  void addInteraction(Interaction* inte);
  //!récupére un le nom du tag
  /*!
    \return  nom du tag
  */
  std::string getName();
  //!revois un pointeur sur la list des interaction qui on ce tag
  /*!
    \return pointeur d'une list de pointeur sur des interactions
  */
  std::list<Interaction*>* getInteraction();
  //!permet de supprimer un pointeur sur une interaction
  /*!
    \param inte pointeur de l'interaction a enlever de la list d'interaction
  */
  void unlinkInteraction(Interaction * inte);
};


#endif
