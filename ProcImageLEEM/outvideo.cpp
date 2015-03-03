#include "outvideo.h"
#include "ui_outvideo.h"

OutVideo::OutVideo(QWidget *parent, QString str) :
    QWidget(parent),
    ui(new Ui::OutVideo)
{
    ui->setupUi(this);

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
    unsigned int i = 0;
    while (i != ga.getVideoOri().size()) {
        //Running Window CV
        imshow("Adjust Window", ga.getVideoSeg().at(i));

        //Convert Image
        //Ori
        QPixmap qPixOri = ASM::cvMatToQPixmap(ga.getVideoOri().at(i));
        this->ui->lbVideoOri->setPixmap(qPixOri);
        //Seg
        QPixmap qPixSeg = ASM::cvMatToQPixmap(ga.getVideoSeg().at(i));
        this->ui->lbVideoSeg->setPixmap(qPixSeg);


        if (waitKey(10) == 27) {
            cout << "esc key is pressed by user" << endl;
            break;
        }
        i++;
    }
}

void OutVideo::on_btPlay_clicked()
{
    executeVideo();
}
