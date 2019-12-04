#include "window.hpp"

Graphics::Graphics(QWidget* parent) :
  QWidget(parent) {
  rubberBand = std::make_shared<QRubberBand>(QRubberBand::Rectangle, this);
  QPalette pal = palette();
  pal.setColor(QPalette::Window, Qt::green);
  setAutoFillBackground(true);
  setPalette(pal);
  auto layout = new QHBoxLayout(this);
}

void Graphics::mousePressEvent(QMouseEvent* event) {
  rubberBandStart = event->pos();
  if (rubberBand) {
    rubberBand->setGeometry(QRect(rubberBandStart, QSize(0, 0)));
    rubberBand->show();
  }
}

void Graphics::mouseMoveEvent(QMouseEvent* event) {
  if (rubberBand) {
    rubberBand->setGeometry(QRect(rubberBandStart, event->pos()).normalized());
  }
}

void Graphics::mouseReleaseEvent(QMouseEvent* event) {
  if(rubberBand) {
    rubberBand->hide();
  }
}

void Graphics::resizeEvent(QResizeEvent* event) {
  qDebug() << "resizeEvent: " << event->size();
  QWidget::resizeEvent(event);
}

void Graphics::paintEvent(QPaintEvent* event) {
  qDebug() << "paintEvent: " << event->rect();
  QWidget::paintEvent(event);
}

Graphics::~Graphics() {}


