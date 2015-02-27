#include "outvideo.h"
#include "ui_outvideo.h"

OutVideo::OutVideo(QWidget *parent, QString str) :
    QWidget(parent),
    ui(new Ui::OutVideo)
{
    ui->setupUi(this);
    this->ui->gbOriginal->setStyleSheet(QStringLiteral("QGroupBox{border:2px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}"));
    this->ui->gbSegmented->setStyleSheet(QStringLiteral("QGroupBox{border:2px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}"));

    path = str;
}

OutVideo::~OutVideo()
{
    delete ui;
}

void OutVideo::loadVideo(){
    //Load video
    ga = (path);

    //Threshold + Canny
    ga.segVideo(100);
}

void OutVideo::saveFileAs(QString str){
    ga.writeVideo(str.toStdString() + ".avi");
}

void OutVideo::executeVideo(){
    int i = 0;
    while (i != ga.getVideoOri().size()) {
        imshow("Window Test", ga.getVideoSeg().at(i));

        if (waitKey(10) == 27) {
            cout << "esc key is pressed by user" << endl;
            break;
        }
        i++;
    }
}
