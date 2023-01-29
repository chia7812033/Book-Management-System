#include "library.h"
#include <QDebug>

Library::Library()
{

}

void Library::setUpDatabase()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("librarydb");
    database.setUserName("root");
    database.setPassword("123456789");
    database.setPort(3306);
    bool ok = database.open();
    if (ok)
        qDebug() << "Successful\n";
    else
        qDebug() << "Error";
}
