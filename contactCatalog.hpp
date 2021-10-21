#ifndef CONTACTCATALOG_HPP
#define CONTACTCATALOG_HPP

#include <string>
#include <list>
#include "contact.hpp"
#include "tagList.hpp"

//! class qui englobe Contact et TagList
/*!
  permet de stocker les contact et la list de tags pour simplifier le passage de celle ci dans tout les objets et donc simplifier la vie aux programmeur
*/
class ContactCatalog {
private:
  //! liste de contacts
  std::list<Contact*> contact_lst;
  //! liste de TOUT les tags
  TagList tag_lst;

public:
  //! constructeur
  ContactCatalog();
  //! destructeur
  ~ContactCatalog();
  //!ajoute un contact
  /*!
    permet d'ajouté un contact sans ce préocuper de la taglist
    \param firstName prenom
    \param  lastName nom
    \param enterprise entreprise
    \param mail email
    \param phone numéro de téléphone
    \param pathPicture URI de la photo
  */
  void addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture);
  //! renvois la list de contact
  /*!
    \param pointeur sur une list de contacts
  */
  std::list<Contact*>* getContactLst();
};

#endif
