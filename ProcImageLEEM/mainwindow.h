#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionOpen_triggered();
    void createSubWindow(QString str);
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_listOpenedItensClick(QListWidgetItem*);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
