#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "admin.h"
#include "usermanager.h"
#include "includes.h"
#include <QWidget>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_backBtn_clicked();

    void on_addUserBtn_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
