#include "admin.h"
#include "ui_admin.h"
#include "registration.h"
#include "loginform.h"
#include "bantracker.h"
#include "eventtracker.h"
#include "chart.h"
#include "usermanager.h"

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

void Admin::eraseData(const QString& filename){
    std::ofstream ofs;
    ofs.open(filename.toStdString(), std::ofstream::out | std::ofstream::trunc);
    if(!ofs.is_open()){
        QMessageBox::warning(this, "Ошибка", "Файл не открылся");
    }
    ofs.close();
    QMessageBox::information(this, "Успешно", "Файл очищен");
}

void Admin::on_eraseLogsBtn_clicked()
{
    UserManager& userManager = UserManager::instance();
    eraseData("log.txt");
    DatabaseManager::AddSimpleLog("Очистка логов", userManager.getCurrentUserLogin());
}

void Admin::on_eraseBanLogsBtn_clicked()
{
    UserManager& userManager = UserManager::instance();
    DatabaseManager::AddSimpleLog("Очистка истории блокировок", userManager.getCurrentUserLogin());
    eraseData("ban_logs.txt");
}


void Admin::on_toDocsBtn_clicked()
{
    Chart *chart = new Chart();
    chart->show();
    this->close();
}

