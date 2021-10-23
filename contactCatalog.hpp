#ifndef CONTACTCATALOG_HPP
#define CONTACTCATALOG_HPP

#include <string>
#include <list>
#include "contact.hpp"
#include "tagList.hpp"
#include "histlocal.hpp"

//! Class qui englobe Contact et TagList
/*!
  permet de stocker les contacts et la list de tags pour simplifier le passage de celle-ci dans tous les objets
*/
class ContactCatalog {
private:
  //! liste de contacts
  std::list<Contact*> contact_lst;
  //! liste de TOUS les tags
  TagList tag_lst;
  //! historique local
  HistLocal *local_hist = NULL;

public:
  //! constructeur
  ContactCatalog();
  //! destructeur
  ~ContactCatalog();
  //! Ajoute un contact
  /*!
    permet d'ajouter un contact sans se préocuper de la taglist
    \param firstName prenom
    \param lastName nom
    \param enterprise entreprise
    \param mail email
    \param phone numéro de téléphone
    \param pathPicture URI de la photo
  */
  void addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture);
  //! renvoie la list de contact
  /*!
    \return pointeur sur une list de contacts
  */
  std::list<Contact*>* getContactLst();
  //! renvoie un pointeur sur l'historique
  /*!
    \return renvoie un pointeur sur l'objet de l'historique
  */
  HistLocal *getHist();
  //! supprime un contact a partir de son pointeur
  /*!
    \param c pointeur sur contact
  */
  void eraseContact(Contact *c);
};

#endif
