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

void BanTracker::on_toMainFormBtn_clicked()
{
    Admin *admin = new Admin();
    admin->show();
    this->close();
}

