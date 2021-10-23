#ifndef HPP_CONTACT
#define HPP_CONTACT
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <list>
#include "tagList.hpp"
#include "interaction.hpp"
#include "histlocal.hpp"


class Interaction;
class TagList;
class HistLocal;
//! class des Contact
/*!
  permet de stocker toutes les informations d'un contact
*/
class Contact {
private:
  //! déclaration des variables privées
  static size_t id_c;
  size_t id;
  size_t interaction_id=0;
  std::string firstName;
  std::string lastName;
  std::string enterprise;
  std::string mail;
  std::string phone;
  std::string pathPicture;
  HistLocal *local_hist = NULL;
  std::list<Interaction*> interaction_lst;
  TagList *tags_lst;

  //! surcharge de <<
  /*!
identique a print_debug mais affiche utilise les flux standar du cpp
  */
  friend std::ostream& operator<<(std::ostream &os, Contact &curr);
public:
  //!déclaration des fonctions publiques
  /*!
    Constructeur
    Un unique constructeur qui demande toutes les informations du contact. Dans les éléments non renseigniés sont gérés en amont
    \param firstName Prénom
    \param lastName Nom
    \param enterprise Entreprise
    \param mail Mail
    \param phone Phone
    \param pathPicture Chemin du fichier photo
    \param lst liste de tags
  */
  Contact (std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture, TagList *lst);
  /*!
    Un destructeur qui free le contact ainsi que toutes les interactions
  */
  ~Contact();
  //! fonction de debug
  /*!
    la fonction affiche tous les champs dans stderr
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
  //! fonction pour ajouter une interaction
  // \param contenue contenu de l'interaction
  void addInteraction(std::string contenue);
  /*! fonction pour ajouter une interaction avec un tag
    \param contenu contenu de l'interaction
    \param tag de l'interaction
  */
  void addInteraction(std::string contenue, std::string tag);

  //! fonction renvoyant la liste des intéractions d'un contact
  std::list<Interaction*>* getInteractionLst();
  //! fonction renvoyant l'identifiant du Contact
  size_t getId();
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
  //! fonction qui renvoie l'historique
  HistLocal *getHist();
  //! fonction qui renvoie l'identifiant de l'intéraction
  size_t getInteractionId(){
    size_t ret = this->interaction_id;
    this->interaction_id++;
    return ret;
  }
  //! erase Interaction
  // \param inte pointeur sur l'intéraction à supprimer
  void eraseInteraction(Interaction *inte);
  //! unlink Interaction
  // \param inte pointeur sur l'intéraction à unlink de la list
  void unlinkInteraction(Interaction *inte);

};


#endif
