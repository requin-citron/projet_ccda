#ifndef WIDGETCONTACT_HPP
#define WIDGETCONTACT_HPP

#include <QtWidgets>
#include "contact.hpp"

class WidgetContact : public QWidget
{
    Q_OBJECT
public:
    WidgetContact(std::string url);
    //! pour recharger les composants avec du texte lors d'une changement de language
    void paintInterface();
    //! configurer le contact
    void configContact(Contact* c);
    //! accesseur
    Contact* getContact();
    //! mettre a jours les interactions
    void refreshInteraction();
    //! si on demande une recherche rapide
    void rechAvance(QString s);
private:
    //! l'url de data
    std::string url;
    //! le contact courrant
    Contact* currentContact = nullptr;
    //! les QLabel du formulaire (gerer en global pour pouvoir les traduires)
    QLabel *writePre = new QLabel();
    QLabel *writeNom = new QLabel();
    QLabel *writeEnt = new QLabel();
    QLabel *writeMail = new QLabel();
    QLabel *writeTel = new QLabel();
    //! les QPushButton (gerer en global pour pouvoir les traduires)
    QPushButton *widgetNewInter = new QPushButton();
    QPushButton *widgetSave = new QPushButton();
    QPushButton *widgetDel = new QPushButton();
    QPushButton *widgetPhoto = new QPushButton();
    //! les QLineEdit pour editer le contact
    QLineEdit *widgetFirstName = new QLineEdit();
    QLineEdit *widgetLastName = new QLineEdit();
    QLineEdit *widgetEntreprise = new QLineEdit();
    QLineEdit *widgetMail = new QLineEdit();
    QLineEdit *widgetPhone = new QLineEdit();
    //! la list des interactions
    QListWidget *widgetListInteraction = new QListWidget();
    //! affichage de la photo
    void displayPhoto(QString path);
    //! equivalent a currentContact->getInteractionLst()[index]
    Interaction* getInteraction(int index);
private slots:
    //! pour quitter
    void quitter();
    //! pour supprimer un contact
    void deleteContact();
    //! pour changer de photo
    void choosePhoto();
    //! pour editer la contact
    void changeContact();
    //! afficher une interaction
    void printInter(QListWidgetItem* i);
    //! afficher une nouvelle interaction
    void createInter();
signals:
    //! contact modifie
    void refreshContact(Contact *c);
    //! contact supprimer
    void removeContact(Contact *c);
    //! afficher une interaction
    void printInter(Interaction *i);
};

#endif // WIDGETCONTACT_HPP
