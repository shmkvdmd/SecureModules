#ifndef BANTRACKER_H
#define BANTRACKER_H

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

private slots:
    void on_toMainFormBtn_clicked();

private:
    Ui::BanTracker *ui;
};

#endif // BANTRACKER_H
