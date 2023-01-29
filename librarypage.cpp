#include "librarypage.h"
#include <QDebug>

LibraryPage::LibraryPage(QWidget *parent) : QStackedWidget(parent)
{

}

void LibraryPage::jumpToInfoPage(QListWidgetItem *item)
{
    // qDebug() << item->text();
    this->setCurrentIndex(1);
    findBook(item, *database);
}

QString LibraryPage::findBook(QListWidgetItem *item, QSqlDatabase &db)
{
    query = new QSqlQuery(db);
    query->exec("SELECT * FROM book WHERE name = '" + item->text() + "'");
    while (query->next())
        qDebug() << query->value(1).toString();

    return query->value(1).toString();
}

void LibraryPage::askForDataBase(QSqlDatabase &db)
{
    this->database = &db;
}
