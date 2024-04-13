#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "eventtracker.h"
#include "loginform.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    EventTracker *userEventTracker = new EventTracker();
    userEventTracker->show();
    this->close();
}


void MainWindow::on_exitBtn_clicked()
{
    LoginForm *loginForm = new LoginForm();
    loginForm->show();
    this->close();
}

