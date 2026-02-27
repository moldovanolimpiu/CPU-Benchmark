#include "mandelbrotwidget.h"
#include <QPainter>
#include "mandelbrot.h"

MandelbrotWidget::MandelbrotWidget(const std::vector<int>& iters,
                                   int width, int height, int maxIter,
                                   QWidget * parent)
    : QWidget(parent)
{


    image = makeImage(iters,width,height,maxIter);

    setFixedSize(width, height);

}
void MandelbrotWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

