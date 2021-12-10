QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contact.cpp \
    contactCatalog.cpp \
    date.cpp \
    histlocal.cpp \
    interaction.cpp \
    main.cpp \
    tag.cpp \
    tagList.cpp \
    window.cpp \
    widgetcontact.cpp \
    widgetmain.cpp \
    widgethist.cpp \
    widgetinter.cpp \
    testcase.cpp

HEADERS += \
    contact.hpp \
    contactCatalog.hpp \
    date.hpp \
    histlocal.hpp \
    interaction.hpp \
    tag.hpp \
    tagList.hpp \
    window.hpp \
    widgetcontact.hpp \
    widgetmain.hpp \
    widgethist.hpp \
    widgetinter.hpp \
    testcase.hpp

TRANSLATIONS = ccda_en.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
