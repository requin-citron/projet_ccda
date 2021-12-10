
#include <QApplication>
#include "testcase.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Window w(&a);
  w.show();
  return a.exec();
}
