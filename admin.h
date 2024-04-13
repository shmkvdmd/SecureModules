#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_pushButton_clicked();

    void on_exitBtn_clicked();

    void on_toEventFormBtn_clicked();

    void on_toBanFormBtn_clicked();

    void on_eraseLogsBtn_clicked();

    void on_eraseBanLogsBtn_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
