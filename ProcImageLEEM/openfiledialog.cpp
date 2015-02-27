#include "openfiledialog.h"
#include "ui_openfiledialog.h"

using namespace std;

OpenFileDialog::OpenFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog)
{
    ui->setupUi(this);
    //Centering window
    QDesktopWidget *desktop = QApplication::desktop();
    int x = (desktop->width() - this->width()) / 2;
    int y = (desktop->height() - this->height()) / 2;
    this->move(x,y);
}

OpenFileDialog::~OpenFileDialog()
{
    delete ui;
}

void OpenFileDialog::on_pushButton_clicked()
{
    if(this->ui->stackedWidget->count() > this->ui->stackedWidget->currentIndex()+1){
        this->ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }
}

void OpenFileDialog::on_pushButton_2_clicked()
{
    if(this->ui->stackedWidget->count() > 1){
        this->ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    }
}
