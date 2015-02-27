#include "outvideo.h"
#include "ui_outvideo.h"

OutVideo::OutVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutVideo)
{
    ui->setupUi(this);
}

OutVideo::~OutVideo()
{
    delete ui;
}
