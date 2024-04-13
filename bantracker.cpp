#include "bantracker.h"
#include "ui_bantracker.h"
#include "admin.h"

BanTracker::BanTracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BanTracker)
{
    ui->setupUi(this);
    QTableWidget *banTable = findChild<QTableWidget*>("banTable");
    if (banTable){
        QHeaderView *header = banTable->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);
    }
}

BanTracker::~BanTracker()
{
    delete ui;
}

std::vector<std::string> BanTracker::ParseData(){
    std::vector<std::string> tokens;
    std::ifstream ifs;
    ifs.open("ban_logs.txt");
    if (!ifs.is_open()){
        qDebug() << "файл не открылся";
        return tokens;
    }
    std::string line;
    while(getline(ifs,line, '|')){
        tokens.push_back(line);
    }
    for (const auto& token : tokens){
        qDebug() << QString::fromStdString(token);
    }
    return tokens;
}

void BanTracker::FillTable(){
    std::vector<std::string> items = ParseData();
    ui->banTable->clearContents();
    ui->banTable->setRowCount(0);
    size_t column_count = ui->banTable->columnCount();
    size_t row = ui->banTable->rowCount();
    size_t max = items.size() / column_count;
    if(!ui->maxLineEdit->text().isEmpty()){
        max = items.size() / column_count < ui->maxLineEdit->text().toInt() ? items.size() / column_count : ui->maxLineEdit->text().toInt();
    }
    qDebug() << max;
    for(size_t i = 0; i != max * column_count; ++row){
        ui->banTable->insertRow(row);
        for (size_t col = 0; col < column_count; ++col, ++i){
            ui->banTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(items[i])));
        }
    }
}

void BanTracker::on_toMainFormBtn_clicked()
{
    Admin *admin = new Admin();
    admin->show();
    this->close();
}


void BanTracker::on_getDataBtn_clicked()
{
    FillTable();
}

