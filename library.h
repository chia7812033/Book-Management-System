#ifndef LIBRARY_H
#define LIBRARY_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include "book.h"

class Library
{
public:
    Library();
    void setUpDatabase();
private:
    QSqlDatabase database;
    QSqlQuery *query;
    Book book;
};

#endif // LIBRARY_H
