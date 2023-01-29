#include "people.h"

People::People()
{
    username = "";
    is_login = false;
}

void People::set_username(QString name)
{
    username = name;
}

void People::login()
{
    is_login = true;
}
void People::logout()
{
    is_login = false;
}

QString People::get_username()
{
    return username;
}

bool People::check_status()
{
    return is_login;
}

void People::reset()
{
    name = "";
    username = "";
    logout();
}

void People::signUp(QSqlDatabase &db, QString name, QString username, QString password)
{
    query = new QSqlQuery(db);
    QString exec_statement = "INSERT INTO account(name, username, userpassword) VALUES ('"
                             + name + "', '"
                             + username + "', MD5('"
                             + password + "'))";
    query->exec(exec_statement);
}

void People::set_limit(int l)
{
    limit = l;
}

int People::get_limit()
{
    return limit;
}

bool People::check_username_exist(QSqlDatabase &db, QString username)
{
    query = new QSqlQuery(db);
    QString exec_statement = "SELECT * from account WHERE username = '"
                             + username + "'";
    query->exec(exec_statement);
    while(query->next())
        return false;
    return true;
}
