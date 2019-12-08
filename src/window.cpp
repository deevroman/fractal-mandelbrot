#include "window.hpp"

Window::Window() :
  QMainWindow::QMainWindow() {
  setMinimumSize(400, 300);
  Graphics* graphics = new Graphics(this);
  setCentralWidget(graphics);
}

Window::~Window() {}


