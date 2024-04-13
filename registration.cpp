#include "registration.h"
#include "ui_registration.h"
Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_backBtn_clicked()
{
    Admin *admin = new Admin();
    admin->show();
    this->close();
}


void Registration::on_addUserBtn_clicked()
{
    QString login = ui->loginLineEdit->text();
    QString password = ui->passLineEdit->text();
    QString role = ui->rolesList->currentText();
    UserManager& userManager = UserManager::instance();
    if (!login.isEmpty() && !password.isEmpty()){
        if (userManager.createUser(login,password,role)){
            ui->loginLineEdit->clear();
            ui->passLineEdit->clear();
            ui->rolesList->setCurrentIndex(0);
            DatabaseManager::AddSimpleLog("Добавление нового пользователя", userManager.getCurrentUserLogin());
            QMessageBox::information(this, "Регистрация", "Пользователь успешно зарегистрирован.");
        }
        else{
            QMessageBox::warning(this, "Ошибка регистрации", "Неудачная попытка регистрации.\nПопробуйте еще раз");
        }
    }
    else{
        QMessageBox::warning(this, "Ошибка регистрации", "Необходимо заполнить все поля");
    }
}

