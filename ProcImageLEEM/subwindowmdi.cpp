#include "subwindowmdi.h"

SubWindowMdi::SubWindowMdi(QWidget *parent, QString str) :
    QMdiSubWindow(parent)
{
    this->update();
    this->repaint();

    out = new OutVideo(this, str);
    this->showMaximized();
    this->showNormal();
    this->setWidget(out);
    this->resize(out->width(),out->height());
    this->setWindowTitle(str);

    out->loadVideo();
}

SubWindowMdi::~SubWindowMdi()
{
    out->~OutVideo();
}
