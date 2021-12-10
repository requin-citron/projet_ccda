
#include <QApplication>
#include "testcase.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile file("../style/test.qss");
  file.open(QFile::ReadOnly | QFile::Text);
  QTextStream stream(&file);
  a.setStyleSheet(stream.readAll());
  Window w;
  w.giveApp(&a);
  w.show();

  return a.exec();
}
