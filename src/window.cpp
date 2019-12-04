#include "window.hpp"

Window::Window() :
  QMainWindow::QMainWindow() {
  setMinimumSize(400, 300);
  QHBoxLayout* layout = new QHBoxLayout(this);
  Graphics* graphics = new Graphics(this);
  layout->addWidget(graphics);
}

Window::~Window() {}


