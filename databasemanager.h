#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "includes.h"
#include "user.h"
class DatabaseManager
{
public:
    DatabaseManager(const QString &dbName = "securesystem.db",
                        const QString &dbType = "QSQLITE",
                        const QString &hostName = "localhost",
                        int port = 5432,
                        const QString &userName = "",
                        const QString &password = "") {

            // Инициализация базы данных
            db = QSqlDatabase::addDatabase(dbType);
            db.setDatabaseName(dbName);
            db.setHostName(hostName);
            db.setPort(port);
            db.setUserName(userName);
            db.setPassword(password);

            // Подключение к базе данных
            if (!db.open()) {
                qDebug() << "Cannot open database:" << db.lastError().text();
            } else {
                qDebug() << "Database opened successfully.";
               createTable();
            }
        }
        void createTable() {
            QSqlQuery query;
            query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, login TEXT, password TEXT, role TEXT)");
            query.exec("CREATE TABLE IF NOT EXISTS logs (id INTEGER PRIMARY KEY AUTOINCREMENT, log_type TEXT, date TEXT, user TEXT, ip TEXT)");
            query.exec("CREATE TABLE IF NOT EXISTS bans (id INTEGER PRIMARY KEY AUTOINCREMENT, log_type TEXT, user TEXT, block_started TEXT, block_end TEXT, block_status INTEGER, ip TEXT)");
        }

        ~DatabaseManager() {
            db.close();
        }
        void closeDatabase()
        {
            db.close();
        }
        static QString getCurrentUserIpAddress() {
            QList<QHostAddress> ipAddresses;
            QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
            for (const QNetworkInterface& interface : interfaces) {
                if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
                    !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
                    QList<QNetworkAddressEntry> entries = interface.addressEntries();
                    for (const QNetworkAddressEntry& entry : entries) {
                        if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                            ipAddresses.append(entry.ip());
                    }
                }
            }
            if (!ipAddresses.isEmpty())
                return ipAddresses.first().toString();
            else
                return QString();
        }

        static bool AddBanInfo(const QString& log_type = "BAN", const QString& login = QString()){
            QSqlQuery query;
            auto curr_time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            auto block_time = QDateTime::currentDateTime().addSecs(300).toString("yyyy-MM-dd HH:mm:ss");
            std::string log_type_, user_login_, block_started_, block_end_, block_status_, ip_;
            QString ip = getCurrentUserIpAddress();
            QString login_;
            if(login.isEmpty()){
                login_ = "NULL";
            }
            else{
                login_ = login;
            }
            query.prepare("INSERT INTO bans (log_type, user, block_started, block_end, block_status, ip) VALUES (:log_type, :user, :block_started, :block_end, :block_status, :ip)");
            query.bindValue(":log_type", log_type);
            query.bindValue(":user", login_);
            query.bindValue(":block_started", curr_time);
            query.bindValue(":block_end", block_time);
            query.bindValue(":block_status", 1);
            query.bindValue(":ip", ip);
            if(query.exec()){
                std::ofstream out;
                out.open("ban_logs.txt", std::ios::app);
                if(!out.is_open()){
                    qDebug() << "not open";
                }
                log_type_ = log_type.toStdString();
                user_login_ = login_.toStdString();
                block_started_ = curr_time.toStdString();
                block_end_ = block_time.toStdString();
                block_status_ = "Заблокирован";
                ip_ = ip.toStdString();
                out << "LOG_TYPE: " << log_type_ << " |USER_LOGIN: " << user_login_ << " |STARTED: " << block_started_ << " |END: " << block_end_ << " |IP: " <<  ip_ << "|";
                out.close();
                qDebug() << "Лог добавлен.";
                return true;
            }
            else{
                qDebug() << "Ошибка записи лога:" << query.lastError().text();
                return false;
            }
        }

        static bool CheckBan(){
            QSqlQuery query;
            QString ip = getCurrentUserIpAddress();
            int block_stat = 0;
            query.prepare("SELECT block_end, block_status FROM bans WHERE ip = :ip ORDER BY block_end DESC LIMIT 1");
            query.bindValue(":ip", ip);
            if (query.exec() && query.next())
            {
                QDateTime block_end = query.value(0).toDateTime();
                QDateTime curr_time = QDateTime::currentDateTime();
                block_stat = query.value(1).toInt();
                if(curr_time > block_end){
                    query.prepare("UPDATE bans SET block_status = :block_status WHERE ip = :ip");
                    query.bindValue(":block_status", 0);
                    query.bindValue(":ip", ip);
                    query.exec();
                    block_stat = 0;
                }
                return block_stat;
            }
            else
            {
                qDebug() << "Ошибка проверки:" << query.lastError().text();
                return false;
            }
        }


        static bool AddSimpleLog(const QString& log_type, const QString& login = QString()){
            QSqlQuery query;
            auto curr_time = QDateTime::currentDateTime();
            QString ip = getCurrentUserIpAddress();
            std::string log_type_,user_login_,date_,ip_;
            qDebug() << curr_time.toString("yyyy-MM-dd HH:mm:ss");
            qDebug() << ip;
            query.prepare("INSERT INTO logs (log_type, date, user, ip) VALUES (:log_type, :date, :user, :ip)");
            query.bindValue(":log_type", log_type);
            query.bindValue(":date", curr_time.toString("yyyy-MM-dd HH:mm:ss"));
            if (login.isEmpty()) {
                query.bindValue(":user", "NULL");
            } else {
                query.bindValue(":user", login);
            }
            query.bindValue(":ip", ip);
            if (query.exec()) {
                std::ofstream out;
                out.open("log.txt", std::ios::app);
                if(!out.is_open()){
                    qDebug() << "not open";
                }
                log_type_ = log_type.toStdString();
                user_login_ = login.isNull() ? "NULL" : login.toStdString();
                date_ = curr_time.toString("yyyy-MM-dd HH:mm:ss").toStdString();
                ip_ = ip.toStdString();
                out << "LOG_TYPE: " << log_type_ << "|USER_LOGIN: " << user_login_ << "|DATE: " << date_ << "|IP: " << ip_ << "|";
                out.close();
                qDebug() << "Лог добавлен.";
                return true;
            } else {
                qDebug() << "Ошибка записи лога:" << query.lastError().text();
                return false;
            }
        }

        bool SimpleLogToTxt(){
            QSqlQuery query;
            std::ofstream out;
            QString log_type,user_login;
            QDateTime date;
            std::string log_type_,user_login_,date_;
            if (!out.is_open()){
                qDebug() << "файл не открылся";
                return false;
            }
            query.prepare("SELECT * FROM logs");
            if (query.exec()){
                while(query.next()){
                    log_type = query.value("log_type").toString();
                    date = query.value("date").toDateTime();
                    user_login = query.value("user").toString();

                    log_type_ = log_type.toStdString();
                    date_ = date.toString(Qt::ISODate).toStdString();
                    user_login_ = user_login.toStdString();
                    out << "Тип лога: " << log_type_ << " " << "Дата и время: " << date_ << " " << "Логин пользователя: " <<user_login_ << std::endl;
                }
                out.close();
                return true;
            }
            else{
                return false;
            }
        }

        bool isDatabaseOpen() const {
            return db.isOpen();
        }
        bool createUser(const User& user, const QString& hashedPassword) {
            QSqlQuery query;
            query.prepare("INSERT INTO users (login, password, role) VALUES (:login, :password, :role)");
            query.bindValue(":login", user.getLogin());
            query.bindValue(":password", hashedPassword);
            query.bindValue(":role", user.getRole());

            if (query.exec()) {
                qDebug() << "User added successfully.";
                return true;
            } else {
                qDebug() << "Error adding user:" << query.lastError().text();
                return false;
            }
        }
        QSqlDatabase getDB(){
            return db;
        }
        bool doesUserExist(const QString &login, const QString &hashedPassword)
        {
            QSqlQuery query;
            query.prepare("SELECT COUNT(*) FROM users WHERE login = :login AND password = :password");
            query.bindValue(":login", login);
            query.bindValue(":password", hashedPassword);

            if (query.exec() && query.next())
            {
                return query.value(0).toInt() > 0;
            }
            else
            {
                qDebug() << "Error checking user existence:" << query.lastError().text();
                return false;
            }
        }
        QString getUserRole(const QString& login, const QString& hashedPassword){
            QSqlQuery query;
            query.prepare("SELECT role FROM users WHERE login = :login AND password = :password");
            query.bindValue(":login", login);
            query.bindValue(":password", hashedPassword);
            if (query.exec() && query.next())
            {
                return query.value("role").toString();
            }
            else
            {
                qDebug() << "Ошибка получения роли:" << query.lastError().text();
                return QString();
            }
        }


    private:

        QSqlDatabase db;
    };
#endif // DATABASEMANAGER_H
