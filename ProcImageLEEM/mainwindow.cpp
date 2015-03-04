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

    //Connections
    connect(this->ui->listOpenVid,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(on_listOpenedItensClick(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

///Event resize windows
void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->ui->listOpenVid->resize(171,this->height()-105);
    this->ui->gbListOpenVideo->resize(171,this->height()-87);
    this->ui->mdiOpenVideo->resize(this->width()-171,this->height()-85);
}

///Create subwindow opened videos
void MainWindow::createSubWindow(QString str)
{
    SubWindowMdi *subW = new SubWindowMdi(ui->mdiOpenVideo, str);
    subW->show();
    this->ui->mdiOpenVideo->update();
    this->ui->mdiOpenVideo->repaint();

    //Cut String for get Name of File
    int j = 0;
    int pos;
    while ((j = str.indexOf("/", j)) != -1) {
        pos = j;
        ++j;
    }
    QString tmp = str.right(str.length() - pos - 1);
    this->ui->listOpenVid->addItem(tmp);

}

///Event open file
void MainWindow::on_actionOpen_triggered()
{
    //Get file name
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open File"),
            QDir::homePath(),
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
             tr("Save File"), "",
             tr("Video files (*.avi *.mov);;All Files (*)"));

    OutVideo *o = (OutVideo*) this->ui->mdiOpenVideo->currentSubWindow()->widget();
    //cout << fileName.toStdString() << endl;
    o->saveFileAs(fileName);
}

void MainWindow::on_actionExit_triggered()
{
    this->~MainWindow();
}

void MainWindow::on_listOpenedItensClick(QListWidgetItem *i)
{
    foreach (QMdiSubWindow *q, this->ui->mdiOpenVideo->subWindowList()) {
        if(!QString::compare(q->windowTitle(),i->text())){
            this->ui->mdiOpenVideo->setActiveSubWindow(q);
        }
    }
}
