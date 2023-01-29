#include "searchengine.h"
#include <QDebug>

SearchEngine::SearchEngine(QWidget *parent) : QLineEdit(parent)
{
    StringCompleter.setModel(&model);
    StringCompleter.setCaseSensitivity(Qt::CaseInsensitive);
}

void SearchEngine::text_change_slots(QSqlDatabase &db, int choice)
{
    query = new QSqlQuery(db);
    QString exec_statement;
    if (choice == 0)
        exec_statement = "SELECT * FROM book WHERE name REGEXP '^"
                + this->text() + "'";
    else if (choice == 1)
        exec_statement = "SELECT * FROM book WHERE author REGEXP '^"
                + this->text() + "'";
    else if (choice == 2)
        exec_statement = "SELECT * FROM book WHERE genre REGEXP '^"
                + this->text() + "'";
    else
    {
        choice++;
        exec_statement = "SELECT * FROM book WHERE publisher REGEXP '^"
                + this->text() + "'";
    }
    query->exec(exec_statement);
    QStringList books;
    while (query->next())
    {
        QString qStr = query->value(choice).toString();
        books << qStr;
        // qDebug() << qStr;
    }
    QSet<QString> books_set = QSet<QString>(books.begin(), books.end());
    books =  books_set.values();
    model.setStringList(books);
    this->setCompleter(&StringCompleter);
}

QStringList SearchEngine::search_book_title(QSqlDatabase &db)
{
    QString title = this->text();
    QString exec_statement = "SELECT * FROM book WHERE name REGEXP '"
            + title + "'";
    query = new QSqlQuery(db);
    query->exec(exec_statement);
    QStringList books;
    while (query->next())
    {
        books << query->value(0).toString();
    }

    return books;
}

QStringList SearchEngine::search_book_author(QSqlDatabase &db)
{
    QString title = this->text();
    QString exec_statement = "SELECT * FROM book WHERE author REGEXP '"
            + title + "'";
    query = new QSqlQuery(db);
    query->exec(exec_statement);
    QStringList books;
    while (query->next())
    {
        books << query->value(0).toString();
    }

    return books;
}

QStringList SearchEngine::search_book_genre(QSqlDatabase &db)
{
    QString title = this->text();
    QString exec_statement = "SELECT * FROM book WHERE genre REGEXP '"
            + title + "'";
    query = new QSqlQuery(db);
    query->exec(exec_statement);
    QStringList books;
    while (query->next())
    {
        books << query->value(0).toString();
    }

    return books;
}
QStringList SearchEngine::search_book_publisher(QSqlDatabase &db)
{
    QString title = this->text();
    QString exec_statement = "SELECT * FROM book WHERE publisher REGEXP '"
            + title + "'";
    query = new QSqlQuery(db);
    query->exec(exec_statement);
    QStringList books;
    while (query->next())
    {
        books << query->value(0).toString();
    }

    return books;
}

