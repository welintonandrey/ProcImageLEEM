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

    //Cut path for get name of file
    int j = 0;
    int pos;
    while ((j = str.indexOf("/", j)) != -1) {
        pos = j;
        ++j;
    }
    QString tmp = str.right(str.length() - pos - 1);
    this->setWindowTitle(tmp);

    //Load video
    out->loadVideo();
}

SubWindowMdi::~SubWindowMdi()
{
    out->~OutVideo();
}
