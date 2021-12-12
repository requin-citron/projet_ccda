#ifndef WIDGETSEARCH_H
#define WIDGETSEARCH_H

#include <QtWidgets>
#include "contactCatalog.hpp"
#include "tagList.hpp"
#include "interaction.hpp"
#include "date.hpp"
//! message quand aucun tag est selectionne doit IMPERATIVEMENT contenir un espace
#define DEFAULT_MESSAGE "None "

class WidgetSearch : public QWidget
{
    Q_OBJECT
public:
    WidgetSearch(ContactCatalog *cata);
    //! pour recharger les composants avec du texte lors d'une changement de language
    void paintInterface();
    //! reload le widget pour qu'il soit a jour
    void reloadSelf();
    //! si on demande une recherche rapide
    void rechAvance(QString &s);
    //! revois l'interaction selectioner (simple clic)
    Interaction *getSelectItem();
    //! get current tag
    QString getTag();
private:
    //! catalogue global de l'app
    ContactCatalog *cata = nullptr;
    //! list des tags
    QComboBox *widgetCombo = new QComboBox();
    //! bouton de suppresion
    QPushButton *widgetSuprr = new QPushButton();
    //! list des interactions de tout le catalogue
    QListWidget *widgetListSearch = new QListWidget();
    //! bouton de retour en arriere
    QPushButton *widgetBack = new QPushButton();
    //! recherche l'interaction depuis le combobox
    Interaction *searchInte(QListWidgetItem* ptr);
public slots:
    //! handler bouton retour en arrire
    void handlerBack();
    //! actualise le list
    void reloadOnChange(const QString &text);
    //! supprime le tag en suppriment touts les tags
    void deleteTag();
    //! slot double click
    void printInter(QListWidgetItem* ptr);
signals:
    //! retour en arriere
    void goBack();
    //! signal double clic sur interaction
    void sigInte(Interaction * inte);

};

#endif // WIDGETSEARCH_H
