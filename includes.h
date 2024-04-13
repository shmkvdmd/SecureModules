#ifndef INCLUDES_H
#define INCLUDES_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QDateTime>
#include <QtSql/QSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QTimer>
#include <QThread>
#include <QtSql/QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QStringList>
#include <QMessageBox>
#include <QtSql/QSqlRecord>
#include <QTableWidget>
#include <QWidget>
#include <QDesktopServices>
#include <QHostAddress>
#include <QTcpSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QIntValidator>

#include <fstream>

enum class Log{
    LOGIN_ERROR,
    LOGIN_SUCCESS,
    BAN,
    UNBAN,
    ACC_CREATE,
    EXIT
};

#endif // INCLUDES_H
