#include "outvideo.h"
#include "ui_outvideo.h"
#include <QTimer>
#include <QDebug>

OutVideo::OutVideo(QWidget *parent, QString str) :
    QWidget(parent),
    ui(new Ui::OutVideo)
{
    ui->setupUi(this);

    path = str;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(executeVideo()));

    //Connect slots Slider
    connect(ui->horizontalSlider,SIGNAL(sliderPressed()),this,SLOT(on_sliderFramePress()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(on_sliderFrameRelease()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(on_sliderFrameMove(int)));
}

OutVideo::~OutVideo()
{
    delete ui;
}

void OutVideo::loadVideo(){
    //Load video
    ga = (path);

    //Set maximum horizontalslider value with Frames
    this->ui->horizontalSlider->setMaximum(ga.getFrames());

    //Threshold + Canny
    ga.segVideo(100);

    //Show first frame
    showMatOnQLabel(0);
}

void OutVideo::saveFileAs(QString str){
    ga.writeVideo(str.toStdString() + ".avi");
}

void OutVideo::executeVideo(){
    //Get position
    int i = ga.getPosVideo();

    //Running Window CV
    //imshow("Adjust Window", ga.getVideoSeg().at(i));

    //Show CV::Mat on QLabel
    showMatOnQLabel(i);

    //Increment Video Position
    i++;
    ga.setPosVideo(i);
    ga.setPosVideoAux(i);

    this->ui->horizontalSlider->setValue(i);
}

void OutVideo::showMatOnQLabel(int pos)
{
    if(pos >= ga.getFrames()){
        qDebug() << "Fim do vídeo";

        this->timer->stop();
    }
    else{
        //Convert Image
        //Ori
        QPixmap qPixOri = ASM::cvMatToQPixmap(ga.getVideoOri().at(pos));
        this->ui->lbVideoOri->setPixmap(qPixOri);
        //Seg
        QPixmap qPixSeg = ASM::cvMatToQPixmap(ga.getVideoSeg().at(pos));
        this->ui->lbVideoSeg->setPixmap(qPixSeg);
    }
}

void OutVideo::on_btPlay_clicked()
{
    this->timer->start(1000/ga.getFps());
}

void OutVideo::on_btPause_clicked()
{
    this->timer->stop();
}

void OutVideo::on_sliderFramePress()
{
    this->timer->stop();
}

void OutVideo::on_sliderFrameRelease()
{
    if(ga.getPosVideo() == ga.getPosVideoAux() && ga.getPosVideo() != 0)
        this->timer->start(1000/ga.getFps());
}

void OutVideo::on_sliderFrameMove(int mv)
{
    if(mv <= 0)
        mv = 1;

    this->timer->stop();

    ga.setPosVideo(mv-1);

    showMatOnQLabel(mv-1);
}


