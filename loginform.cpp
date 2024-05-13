#include "loginform.h"
#include "ui_loginform.h"
#include "mainwindow.h"
#include "admin.h"
#include "databasemanager.h"
#include "usermanager.h"
LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    userManager.createUser("admin", "admin", "Администратор");
}

LoginForm::~LoginForm()
{
    delete ui;
}

int block_iter = 0;
void LoginForm::on_loginButton_clicked()
{
    QString login = ui->loginLineEdit->text();
    QString password = ui->passLineEdit->text();
    if (userManager.loginUser(login,password) == ADMIN_ID){
        DatabaseManager::AddSimpleLog("Вход в систему", login);
        Admin *admin = new Admin();
        admin->show();
        this->close();
    }
    else if (DatabaseManager::CheckBan()){
        QMessageBox::warning(this, "Ошибка входа", "Адрес заблокирован. \nПовторите позже.");
        return;
    }
    else if(userManager.loginUser(login,password)){
        DatabaseManager::AddSimpleLog("Вход в систему", login);
        MainWindow *userMainWindow = new MainWindow();
        userMainWindow->show();
        this->close();
    }
    else{
        ++block_iter;
        if (block_iter >= 3){
            DatabaseManager::AddBanInfo("BAN",login);
        }
        QMessageBox::warning(this, "Ошибка входа", "Неудачная попытка входа. \nПроверьте адрес и пароль.");
        DatabaseManager::AddSimpleLog("Ошибка входа в систему");
    }
}

