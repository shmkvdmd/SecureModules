#ifndef EVENTTRACKER_H
#define EVENTTRACKER_H

#include <QWidget>

namespace Ui {
class EventTracker;
}

class EventTracker : public QWidget
{
    Q_OBJECT

public:
    explicit EventTracker(QWidget *parent = nullptr);
    ~EventTracker();
    std::vector<std::string> ParseData();
    void FillTable();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EventTracker *ui;
};

#endif // EVENTTRACKER_H
