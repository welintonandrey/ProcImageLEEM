#ifndef SUBWINDOWMDI_H
#define SUBWINDOWMDI_H

#include <QMdiSubWindow>
#include "outvideo.h"

namespace Ui {
    class SubWindowMdi;
}

class SubWindowMdi : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit SubWindowMdi(QWidget *parent = 0);
    ~SubWindowMdi();
private:
    //OutWindow *out;
    OutVideo *out;
};

#endif // SUBWINDOWMDI_H
