#ifndef WIDGETINTER_HPP
#define WIDGETINTER_HPP

#include <QtWidgets>
#include "interaction.hpp"

class WidgetInter : public QWidget
{
    Q_OBJECT
public:
    WidgetInter();
    //! pour recharger les composants avec du texte lors d'une changement de language
    void paintInterface();
    Interaction* getInter();
    //! configurer l'interaction
    void configInter(Interaction* i);
    //! si on demande une recherche rapide
    void rechAvance(QString s);
private:
    //! l'interaction courrante
    Interaction* currentInter = nullptr;
    //! permet de savoir si le contenue a change pour enregistrer si besoin
    bool textChange = false;
    //! les composants
    QLabel *widgetNameContact = new QLabel();
    QTextEdit *widgetContenu = new QTextEdit();
    QListWidget *widgetListTodo = new QListWidget();
    QLineEdit *widgetTags = new QLineEdit();
    QPushButton *widgetSave = new QPushButton();
    QPushButton *widgetDel = new QPushButton();
    //! rafraichir les todos
    void refreshTodo();
private slots:
    //! modifier le contenu
    void editText();
    //! enregistrer le contenu
    void saveText();
    //! suppriemr une interaction
    void delInter();
    //! enregistrer les tags
    void editTag();
signals:
    //! quitter WidgetInter en sauvgardant
    void refreshInteraction();
    //! quitter WidgetInter en supprimant
    void deleteInteraction();
};

#endif // WIDGETINTER_HPP
