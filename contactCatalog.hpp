#ifndef CONTACTCATALOG_HPP
#define CONTACTCATALOG_HPP

#include <string>
#include <list>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
//json specific
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include "contact.hpp"
#include "interaction.hpp"
#include "tag.hpp"
#include "tagList.hpp"
#include "histlocal.hpp"
#include "interaction.hpp"

//! Class qui englobe Contact et TagList
/*!
  permet de stocker les contacts et la list de tags pour simplifier le passage de celle-ci dans tous les objets
*/
class ContactCatalog {
private:
  std::string pathBdd;
  //! liste de contacts
  std::list<Contact*> contact_lst;
  //! liste de TOUS les tags
  TagList tag_lst;
  //! historique local
  HistLocal *local_hist = NULL;
  //! crée une connexion a la base de donnee
  void initDbConnexion(std::string path);
  //! supprime la connexion a la base de donnee
  void eraseDbConnexion();

  //!wipe Database
  /*!
   Attention il faut que la db soit ouverte.
   */
  void cleanDataBase();
  //! sauvegarde le catalogue dans la DB interne
  void safeSaveDataBase(std::string path);
  //! importation de la base de donnée interne
  void safeLoadDataBase(std::string path);

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
    \return le contact
  */
  Contact* addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture);
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
  //! sauvegarde le catalogue dans la DB
  void saveDataBase(std::string path);
  //! importation de la base de donnée
  void loadDataBase(std::string path);
  //! sauvegarde en json
  std::string saveJson();
  //! renvois un pointeur sur l'object tag_list
  /*!
    \return pointeur sur la list global des tags
   */
  TagList *getTagList();

};

#endif
