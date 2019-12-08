
// Qt dependencies
#include <QRubberBand>
#include <QMouseEvent>
#include <QWidget>
#include <QPalette>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QStack>
#include <QPair>
#include <QKeyEvent>
#include <QVector>
#include <QThread>

// stl dependencies
#include <memory>

// custom libraries
#include "complex/complex.hpp"

// in-place dependencies
#include "square_rubber_band.hpp"

#pragma once

class Graphics : public QWidget {
public:
  Graphics(QWidget* parent = nullptr);
  ~Graphics() override = default;

public slots:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

private:
  static int mandelbrotColor(const complex::Complex& point);
  static bool isMandelbrot(const complex::Complex& point);
  static void processPoints(double cx, double cy, double pixelWeight, double sz, const QRect& r, QImage* image, const QRect& e);

  QPoint rubberBandStart;
  std::shared_ptr<QRubberBand> rubberBand;
  double pixelWeight;
  double dx, dy;
  QStack< QPair<QPoint, double> > stack;
  static QVector<QColor> colors;
};

