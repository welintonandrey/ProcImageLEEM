#include "subwindowmdi.h"

SubWindowMdi::SubWindowMdi(QWidget *parent) :
    QMdiSubWindow(parent)
{
    this->update();
    this->repaint();

    out = new OutVideo(this);
    this->showMaximized();
    this->showNormal();
    this->setWidget(out);
    this->resize(out->width(),out->height());
    this->setWindowTitle("NomeVideoEntrada");
}

SubWindowMdi::~SubWindowMdi()
{
    out->~OutVideo();
}
