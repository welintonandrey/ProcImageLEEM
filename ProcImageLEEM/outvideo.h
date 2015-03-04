#ifndef OUTVIDEO_H
#define OUTVIDEO_H

#include <QWidget>
#include <QString>
#include "gallium.h"
#include "convertImage.h"
#include <QTimer>

namespace Ui {
class OutVideo;
}

class OutVideo : public QWidget
{
    Q_OBJECT

public:
    explicit OutVideo(QWidget *parent = 0, QString str = "");
    ~OutVideo();
    void loadVideo();
    void saveFileAs(QString str);
    void showMatOnQLabel(int pos);

private slots:
    void on_btPlay_clicked();
    void on_sliderFramePress();
    void on_sliderFrameRelease();
    void on_sliderFrameMove(int);
    void executeVideo();

    void on_btPause_clicked();

private:
    Ui::OutVideo *ui;
    Gallium ga;
    QString path;
    QTimer *timer;
};

#endif // OUTVIDEO_H
