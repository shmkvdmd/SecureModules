#ifndef BANTRACKER_H
#define BANTRACKER_H
#include "mainwindow.h"
#include "usermanager.h"
#include "fstream"
#include "admin.h"
#include <vector>
#include <QWidget>

namespace Ui {
class BanTracker;
}

class BanTracker : public QWidget
{
    Q_OBJECT

public:
    explicit BanTracker(QWidget *parent = nullptr);
    ~BanTracker();
    std::vector<std::string> ParseData();
    void FillTable();

private slots:
    void on_toMainFormBtn_clicked();

    void on_getDataBtn_clicked();

private:
    Ui::BanTracker *ui;
};

#endif // BANTRACKER_H
