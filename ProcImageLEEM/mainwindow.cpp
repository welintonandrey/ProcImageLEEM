#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "gallium.h"
#include "openfiledialog.h"
#include <QDesktopWidget>
#include "subwindowmdi.h"


using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Centering window
    QDesktopWidget *desktop = QApplication::desktop();
    int x = (desktop->width() - this->width()) / 2;
    int y = (desktop->height() - this->height()) / 2;
    this->move(x,y);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->ui->listOpenVideo->resize(171,this->height()-85);
    this->ui->mdiOpenVideo->resize(this->width()-171,this->height()-85);
}

void MainWindow::createSubWindow()
{
    SubWindowMdi *subW = new SubWindowMdi(ui->mdiOpenVideo);
    subW->show();
    ui->mdiOpenVideo->update();
    ui->mdiOpenVideo->repaint();

}

void MainWindow::on_actionOpen_triggered()
{
    /*QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Document"),
            QDir::currentPath(),
            tr("Video files (*.avi *.mov);;All files (*.*)") );

    */

    //OpenFileDialog *o = new OpenFileDialog(this);
    //o->show();

    //teste
    createSubWindow();


    /*
    //Load video
    Gallium ga(filename);

    //Threshold + Canny
    ga.segVideo(100);

    //Write Video on file
    ga.writeVideo("out.avi");

    //Exibe o resultado
    int i = 0;
    while (i != ga.getVideoOri().size()) {
        //imshow("Original Video", ga.GetVideoOri().at(i));
        //imshow("Segmented Video", ga.GetVideoSeg().at(i));
        imshow("Uni Video", ga.getVideoSeg().at(i));

        if (waitKey(10) == 27) {
            cout << "esc key is pressed by user" << endl;
            break;
        }
        i++;
    }
    */
}
