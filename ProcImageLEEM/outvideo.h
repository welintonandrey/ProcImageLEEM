#ifndef OUTVIDEO_H
#define OUTVIDEO_H

#include <QWidget>
#include <QString>
#include "gallium.h"
#include "convertImage.h"

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
    void executeVideo();
    void saveFileAs(QString str);

private slots:
    void on_btPlay_clicked();

private:
    Ui::OutVideo *ui;
    Gallium ga;
    QString path;
};

#endif // OUTVIDEO_H
