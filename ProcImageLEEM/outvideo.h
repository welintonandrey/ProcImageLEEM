#ifndef OUTVIDEO_H
#define OUTVIDEO_H

#include <QWidget>

namespace Ui {
class OutVideo;
}

class OutVideo : public QWidget
{
    Q_OBJECT

public:
    explicit OutVideo(QWidget *parent = 0);
    ~OutVideo();

private:
    Ui::OutVideo *ui;
};

#endif // OUTVIDEO_H
