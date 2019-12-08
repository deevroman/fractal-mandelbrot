#include <QApplication>
#include "window.hpp"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Window window;
  window.setFixedSize(1024, 1024);
  window.setWindowTitle("Window");
  window.show();
  return app.exec();
}
