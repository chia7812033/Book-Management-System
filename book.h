#ifndef BOOK_H
#define BOOK_H
#include "collections.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class Book : public Collections
{
private:
    QString title;
    QString author;
    QString genre;
    int pages;
    QString publisher;
    QSqlQuery *query;
    QString status;
public:
    Book();
    void set_name(QString str);
    void set_author(QString str);
    void set_genre(QString str);
    void set_pages(int p);
    void set_publisher(QString str);
    void set_status(QString str);
    QString getBookInfo();
    QString getTitle();
    QString getAuthor();
    QString getPage();
    QString getPublisher();
    QString getGenre();
    QString getStatus();
    int add_book_myBook(QSqlDatabase &db, QString username, int limit);
    bool insert_new_book(QSqlDatabase &db);
    bool edit_new_book(QSqlDatabase &db);
    bool delete_this_book(QSqlDatabase &db);
    QString tmp;
};
#endif // BOOK_H
