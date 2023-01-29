#ifndef PEOPLE_H
#define PEOPLE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class People
{
private:
    QString username;
    QString name;
    bool is_login;
    bool is_admin;
    QSqlQuery *query;
    int limit;
public:
    People();
    void set_username(QString name);
    void login();
    void logout();
    QString get_username();
    bool check_status();
    void reset();
    void signUp(QSqlDatabase &db, QString name, QString username, QString password);
    void set_limit(int);
    int get_limit();
    bool check_username_exist(QSqlDatabase &db, QString username);
};

#endif // PEOPLE_H
