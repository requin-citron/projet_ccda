#ifndef WIDGETMAIN_HPP
#define WIDGETMAIN_HPP

#include <QtWidgets>
#include "contactCatalog.hpp"

class WidgetMain : public QWidget
{
public:
    WidgetMain(ContactCatalog *cata);
private:
    ContactCatalog *cata;
    QListWidget *widgetListContact = new QListWidget();
    std::vector<QListWidgetItem*> listItem;
};

#endif // WIDGETMAIN_HPP
