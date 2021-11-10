#ifndef HISTLOCAL_HPP
#define HISTLOCAL_HPP
#include <list>
#include <string>
#include <time.h>
#include "tag.hpp"
#include "contact.hpp"
#include "interaction.hpp"
#include "date.hpp"

/*!
    définition des flags utilisés aprés dans le reste du code pour spécifier le type de log
*/
#define CREATE_CONTACT 13
#define DELETE_CONTACT 14
#define CHANGE_LAST_NAME 1
#define CHANGE_FIRST_NAME 2
#define CHANGE_ENTREPRISE_NAME 3
#define CHANGE_MAIL 4
#define CHANGE_PHONE 5
#define CHANGE_PATH_PICTURE 6
#define CHANGE_DATE 7
#define ADD_INTERACTION 8
#define DELETE_INTERACTION 9

#define CHANGE_CONTENUE 10
#define ADD_TAG 11
#define DELETE_TAG 12


class Contact;
class Interaction;

//! class qui gére les historiques locaux des objets
/*!
  permet d'ajouter des éléments dans l'historique que ce soit pour les contacts ou pour les interactions
*/
class HistLocal {
private:
  //! liste de pointeur sur des paires string et date
  std::list<std::pair<std::string, Date>*> hist_lst;

public:
  //! constructeur
  HistLocal();
  //! destructeur
  ~HistLocal();
  //! insert un élément dans l'historique concernant un contact
  /*!
    \param conta pointeur sur le contact
    \param flag flag provenant des constantes de préprocesseur qui permettent de préciser la nature de l'entrée
  */
  void insertHist(Contact *conta, char flag);
  //! insert un élément dans l'historique concernant une interaction
  /*!
    \param conta pointeur sur le contact
    \param inte pointeur sur l'interaction
    \param flag flag provenant des constantes de préprocesseur qui permettent de préciser la nature de l'entrée
  */
  void insertHist(Contact *conta, Interaction *inte, char flag);
  //! insert un élément dans l'historique en passant directement par la db
  /*!
    \param contenue chaine de l'historique
    \param date chaine contenant la date
   */
  void insertHist(std::string contenue, std::string date);
  //! renvoie la liste de toutes les entrées
  /*!
    \return pointeur sur une liste de paires string et date
  */
  std::list<std::pair<std::string, Date>*>* getLst();
};


#endif
