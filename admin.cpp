#include "admin.h"
#include "ui_admin.h"
#include "registration.h"
#include "loginform.h"
#include "bantracker.h"
#include "eventtracker.h"

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    Registration *reg = new Registration();
    reg->show();
    this->close();
}


void Admin::on_exitBtn_clicked()
{
    LoginForm *loginForm = new LoginForm();
    loginForm->show();
    this->close();
}


void Admin::on_toEventFormBtn_clicked()
{
    EventTracker *userEventTracker = new EventTracker();
    userEventTracker->show();
    this->close();
}


void Admin::on_toBanFormBtn_clicked()
{
    BanTracker *banTracker = new BanTracker();
    banTracker->show();
    this->close();
}

