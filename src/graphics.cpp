#include "window.hpp"
#include "graphics.hpp"

QVector<QColor> Graphics::colors = {Qt::white, Qt::blue, Qt::red, Qt::green, Qt::black};

Graphics::Graphics(QWidget* parent) :
  QWidget(parent),
  pixelWeight(1),
  dx(0), dy(0) {
  rubberBand = std::make_shared<QRubberBand>(QRubberBand::Rectangle, this);
  setFocusPolicy(Qt::StrongFocus);
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
    if (rubberBand->rect().isNull()) {
      return;
    }
    int x = qMin(event->x(), rubberBandStart.x());
    int y = qMin(event->y(), rubberBandStart.y());
    double k1 = 1.0 * rubberBand->rect().width() / width();
    double k2 = 1.0 * rubberBand->rect().height() / height();
    dx = dx + x * pixelWeight;
    dy = dy + y * pixelWeight;
    pixelWeight *= qMax(k1, k2);
    stack.push(qMakePair(rubberBandStart, qMax(k1, k2)));
    QWidget::update();
  }
}

void Graphics::paintEvent(QPaintEvent* event) {
  static const int blockSize = 50;
  int w = width();
  int h = height();
  int cx = w / 2;
  int cy = h / 2;
  double sz = qMin(width(), height());
  QRect r = event->rect();
  QImage image(r.width(), r.height(), QImage::Format_RGB32);
//  for (int x = r.left(); x <= r.right(); ++x) {
//    for (int y = r.top(); y <= r.bottom(); ++y) {
//      double rx = 3.0 * (x * pixelWeight - (cx - dx)) / sz;
//      double ry = 3.0 * (y * pixelWeight - (cy - dy)) / sz;
//      int xInside = x - r.left();
//      int yInside = y - r.top();
//      if (isMandelbrot(complex::Complex(rx, ry))) {
//        image.setPixelColor(xInside, yInside, Qt::black);
//      } else {
//        image.setPixelColor(xInside, yInside, Qt::white);
//      }
//    }
//  }
  QVector<QThread*> threads;
  for (int x = r.left(); x <= r.right(); x += blockSize) {
    for (int y = r.top(); y <= r.bottom(); y += blockSize) {
      int szx = qMin(blockSize, r.right() - x + 1);
      int szy = qMin(blockSize, r.bottom() - y + 1);
      QThread* thread = QThread::create(&Graphics::processPoints, cx - dx, cy - dy, pixelWeight, sz, r, &image, QRect(x, y, szx, szy));
      thread->start();
      threads.push_back(thread);
    }
  }
  for (auto t : threads) {
    t->wait();
  }
  QPainter painter(this);
  painter.drawImage(r.topLeft(), image);
}

bool Graphics::isMandelbrot(const complex::Complex &point) {
  complex::Complex z = 0;
  for (int i = 0; i < 50; ++i) {
    z = z * z + point;
    if (z.getReal() * z.getReal() + z.getImaginary() * z.getImaginary() > 4) {
      return false;
    }
  }
  return true;
}

int Graphics::mandelbrotColor(const complex::Complex& point) {
  int t = 0;
  complex::Complex z = 0;
  while (t + 1 < 300) {
    ++t;
    z = z * z + point;
    if (z.getReal() * z.getReal() + z.getImaginary() * z.getImaginary() > 4) {
      break;
    }
  }
  return t / 60;
}

void Graphics::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
}

void Graphics::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    if (stack.isEmpty()) {
      return;
    }
    QPoint r = stack.top().first;
    double k = stack.top().second;
    stack.pop();
    pixelWeight /= k;
    dx = dx - r.x() * pixelWeight;
    dy = dy - r.y() * pixelWeight;
    QWidget::update();
  }
  QWidget::keyPressEvent(event);
}
void Graphics::processPoints(double cx, double cy, double pixelWeight, double sz, const QRect& r, QImage* image, const QRect& e) {
  for (int x = e.left(); x <= e.right(); ++x) {
    for (int y = e.top(); y <= e.bottom(); ++y) {
      double rx = 3.0 * (x * pixelWeight - cx) / sz;
      double ry = 3.0 * (y * pixelWeight - cy) / sz;
      int xInside = x - r.left();
      int yInside = y - r.top();
//      if (isMandelbrot(complex::Complex(rx, ry))) {
//        image->setPixelColor(xInside, yInside, Qt::black);
//      } else {
//        image->setPixelColor(xInside, yInside, Qt::white);
//      }
      image->setPixelColor(xInside, yInside, colors[mandelbrotColor(complex::Complex(rx, ry))]);
    }
  }
}

