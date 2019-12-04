#include <QApplication>
#include <QMainWindow>
#include "window.hpp"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Window window;
  window.resize(500, 500);
  window.setWindowTitle("Window");
  window.show();
  return app.exec();
}
