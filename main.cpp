
#include <QApplication>
#include "testcase.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  translator.load("../ccda_en");
  a.installTranslator(&translator);
    a.removeTranslator(&translator);
  Window w;
  w.show();

  return a.exec();
}
