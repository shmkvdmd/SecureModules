#include "chart.h"
#include "ui_chart.h"
#include "admin.h"
Chart::Chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);
}

Chart::~Chart()
{
    delete ui;
}

int Chart::GetLogCount(const std::string& filename){
    std::vector<std::string> tokens;
    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs.is_open()){
        qDebug() << "файл не открылся";
        return 0;
    }
    std::string line;
    while(getline(ifs,line, '|')){
        tokens.push_back(line);
    }
    return tokens.size();
}


void Chart::on_getLogCountBtn_clicked()
{

    ui->logLabel->setText("Количество логов: " + QString::number(GetLogCount("log.txt") / 4));
    ui->banLabel->setText("Количество блокировок: " + QString::number(GetLogCount("ban_logs.txt") / 5));
}


void Chart::on_toMenuBtn_clicked()
{
    Admin *admin = new Admin();
    admin->show();
    this->close();
}

