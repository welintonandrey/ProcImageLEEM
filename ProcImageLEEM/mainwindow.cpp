#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "gallium.h"
#include "openfiledialog.h"
#include <QDesktopWidget>
#include "subwindowmdi.h"

#include "convertImage.h"
using namespace ASM;

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

///Event resize windows
void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->ui->listOpenVideo->resize(171,this->height()-85);
    this->ui->mdiOpenVideo->resize(this->width()-171,this->height()-85);
}

///Create subwindow opened videos
void MainWindow::createSubWindow(QString str)
{
    SubWindowMdi *subW = new SubWindowMdi(ui->mdiOpenVideo, str);
    subW->show();
    ui->mdiOpenVideo->update();
    ui->mdiOpenVideo->repaint();

}

///Event open file
void MainWindow::on_actionOpen_triggered()
{
    //Get file name
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Document"),
            QDir::currentPath(),
            tr("Video files (*.avi *.mov);;All files (*.*)") );

    if(!filename.toStdString().empty())
    {
        //Create SubWindow
        createSubWindow(filename);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save Address Book"), "",
             tr("Address Book (*.abk);;All Files (*)"));

    OutVideo *o = (OutVideo*) this->ui->mdiOpenVideo->currentSubWindow()->widget();
    cout << fileName.toStdString() << endl;
    o->saveFileAs(fileName);
}

void MainWindow::on_actionExit_triggered()
{
    this->~MainWindow();
}
