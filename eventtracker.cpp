#include "eventtracker.h"
#include "ui_eventtracker.h"

EventTracker::EventTracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventTracker)
{
    ui->setupUi(this);
    QTableWidget *eventTable = findChild<QTableWidget*>("eventTable");
    if (eventTable){
        QHeaderView *header = eventTable->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);
    }
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
    for (const auto& token : tokens){
    }
    return tokens;
}

void EventTracker::FillTable(){
    std::vector<std::string> items = ParseData();
    ui->eventTable->clearContents();
    ui->eventTable->setRowCount(0);
    size_t column_count = ui->eventTable->columnCount();
    size_t row = ui->eventTable->rowCount();
    size_t max = items.size() / column_count;
    if(!ui->maxCountLineEdit->text().isEmpty()){
        max = items.size() / column_count < ui->maxCountLineEdit->text().toInt() ? items.size() / column_count : ui->maxCountLineEdit->text().toInt();
    }
    for(size_t i = 0; i != max * column_count; ++row){
        ui->eventTable->insertRow(row);
        for (size_t col = 0; col < column_count; ++col, ++i){
            ui->eventTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(items[i])));
        }
    }
}

void EventTracker::on_pushButton_clicked()
{
    Admin *admin = new Admin();
    admin->show();
    this->close();
}


void EventTracker::on_pushButton_2_clicked()
{
    FillTable();
}

