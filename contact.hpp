#ifndef HPP_CONTACT
#define HPP_CONTACT
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <list>
#include "interaction.hpp"

//! class Contact
/*!
  permet de stocker toutes les informations d'un
  contact.
*/

class Contact {
private:
  //! declaration des variables privées
  std::string firstName;
  std::string lastName;
  std::string enterprise;
  std::string mail;
  std::string phone;
  std::string pathPicture;
  struct tm date;
  std::list<Interaction*> interactions;

  //!surcharge de <<
  /*!
  identique a print_debug mais affiche utilise les flux standar du cpp
  */
  friend std::ostream& operator<<(std::ostream &os, Contact &curr);
public:
  //! declaration des fonctions publique
  //! Constructeur
  /*!
    Un unique constructeur qui demande toute les informations
    du contact. Dans les éléments non rensegnier sont géré en amont
    \param firstName Prenom
    \param lastName Nom
    \param enterprise Entreprise
    \param mail Mail
    \param phone Phone
    \param pathPicture Chemain du fichier photo
    \param date Date de creation
  */
  Contact (std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture);
  //! fonction de debug
  /*!
    la fonction affiche tout les champs dans stderr
  */
  void print_debug();
  //! fonction de mofication de firstName
  void setFirstName(std::string fn);
  //! fonction de mofication de lastName
  void setLastName(std::string ln);
  //! fonction de mofication de enterprise
  void setEnterprise(std::string et);
  //! fonction de mofication de mail
  void setMail(std::string ml);
  //! fonction de mofication de phone
  void setPhone(std::string ph);
  //! fonction de mofication de pathPicture
  void setPathPicture(std::string path);
  //! fonction de mofication de date
  void setDate(struct tm &da);

  //! fonction renvoyant firstName
  std::string getFirstName();
  //! fonction renvoyant lastName
  std::string getLastName();
  //! fonction renvoyant enterprise
  std::string getEnterprise();
  //! fonction renvoyant mail
  std::string getMail();
  //! fonction renvoyant phone
  std::string getPhone();
  //! fonction renvoyant pathPicture
  std::string getPathPicture();
  //! fonction renvoyant date
  struct tm getDate();

};

#endif
