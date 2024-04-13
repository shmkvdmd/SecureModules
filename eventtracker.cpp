#include "eventtracker.h"
#include "ui_eventtracker.h"
#include "mainwindow.h"
#include "usermanager.h"
#include "fstream"
#include "admin.h"
#include <vector>
EventTracker::EventTracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventTracker)
{
    ui->setupUi(this);
    ui->eventTable->setColumnWidth(0, 300);
    ui->eventTable->setColumnWidth(1, 200);
    ui->eventTable->setColumnWidth(2, 200);
    ui->eventTable->setColumnWidth(3, 150);
    ui->maxCountLineEdit->setValidator(new QIntValidator(0, 999, this));
}

EventTracker::~EventTracker()
{
    delete ui;
}

std::vector<std::string> EventTracker::ParseData(){
    std::vector<std::string> tokens;
    std::ifstream ifs;
    ifs.open("log.txt");
    if (!ifs.is_open()){
        qDebug() << "файл не открылся";
        return tokens;
    }
    std::string line;
    while(getline(ifs,line, '|')){
        tokens.push_back(line);
    }
    tokens.pop_back();
    for (const auto& token : tokens){
        qDebug() << QString::fromStdString(token);
    }
    return tokens;
}

void EventTracker::FillTable(){
    std::vector<std::string> items = ParseData();
    ui->eventTable->clearContents();
    ui->eventTable->setRowCount(0);
    size_t column_count = ui->eventTable->columnCount();
    size_t row = ui->eventTable->rowCount();
    size_t max = items.size() / 4;
    if(!ui->maxCountLineEdit->text().isEmpty()){
        max = items.size() / 4 < ui->maxCountLineEdit->text().toInt() ? items.size() / 4 : ui->maxCountLineEdit->text().toInt();
    }
    qDebug() << max;
    for(size_t i = 0; i != max * 4; ++row){
        ui->eventTable->insertRow(row);
        for (size_t col = 0; col < column_count; ++col, ++i){
            ui->eventTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(items[i])));
        }
    }
}

void EventTracker::on_pushButton_clicked()
{
    UserManager& userManager = UserManager::instance();
    if(userManager.getCurrentUserRole() == "Администратор"){
        Admin *admin = new Admin();
        admin->show();
        this->close();
    }
    else{
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    }
}


void EventTracker::on_pushButton_2_clicked()
{
    FillTable();
}

