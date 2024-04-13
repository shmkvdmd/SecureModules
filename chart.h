#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <fstream>
#include <string>
#include <vector>
namespace Ui {
class Chart;
}

class Chart : public QWidget
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr);
    ~Chart();
    int GetLogCount(const std::string& filename);
    std::vector<std::string> ParseData();

private slots:
    void on_getLogCountBtn_clicked();

    void on_toMenuBtn_clicked();

private:
    Ui::Chart *ui;
};

#endif // CHART_H
