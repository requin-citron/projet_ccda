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
    Interaction* currentInter = nullptr;
    bool textChange = false;
    QLabel *widgetNameContact = new QLabel();
    QTextEdit *widgetContenu = new QTextEdit();
    QListWidget *widgetListTodo = new QListWidget();
    QLineEdit *widgetTags = new QLineEdit();
    QPushButton *widgetSave = new QPushButton();
    QPushButton *widgetDel = new QPushButton();
    void refreshTodo();
private slots:
    void editText();
    void saveText();
    void delInter();
    void editTag();
signals:
    void refreshInteraction();
    void deleteInteraction();
};

#endif // WIDGETINTER_HPP
