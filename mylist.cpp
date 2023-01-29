#include "mylist.h"
#include <QDebug>

myList::myList(QWidget *parent) : QListWidget(parent)
{

}


// select random books from database
void myList::displayRandomBook(QSqlDatabase &db)
{
    this->clear();
    query = new QSqlQuery(db);
    query->exec("SELECT * FROM book AS t1 JOIN (SELECT name FROM book ORDER BY RAND() LIMIT 30) as t2 ON t1.name=t2.name");
    while (query->next())
    {
        QListWidgetItem *item = new QListWidgetItem;
        QString qStr = query->value(0).toString();
        item->setText(qStr);

        this->addItem(item);
    }
}

// display the book the user borrowed
void myList::findBorrowedBook(QSqlDatabase &db, QString username)
{
    query = new QSqlQuery(db);
    query->exec("SELECT * FROM borrowlist WHERE username = '" + username + "'");
    while (query->next())
    {
        QListWidgetItem *item = new QListWidgetItem;
        QString qStr = query->value(1).toString();
        item->setText(qStr);

        this->addItem(item);
    }
}

void myList::displaySearchResult(QStringList books)
{
    for (int i = 0; i < books.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        QString qStr = books[i];
        item->setText(qStr);

        this->addItem(item);
    }
}
