#include "book.h"
#include <QVariant>
#include <QDebug>

Book::Book() : Collections()
{
    title = "";
    author = "";
    genre = "";
    pages = 0;
    publisher = "";
}

void Book::set_name(QString str)
{
    title = str;
}

void Book::set_author(QString str)
{
    author = str;
}

void Book::set_genre(QString str)
{
    genre = str;
}

void Book::set_pages(int p)
{
    pages = p;
}

void Book::set_publisher(QString str)
{
    publisher = str;
}

void Book::set_status(QString str)
{
    if (str == "0")
        status = "Available";
    else if (str == "1")
        status = "Borrowed";
    else if (str == "2")
        status = "Lost";
}

QString Book::getBookInfo()
{
    QString info = "";
    info += "Title : "; info += title;
    info += "\nAuthor : "; info += author;
    info += "\nGenre : "; info += genre;
    info += "\nPages : "; info += QString::number(pages);
    info += "\nPublisher : "; info += publisher;
    info += "\nStatus : "; info += status;

    return info;
}

QString Book::getTitle()
{
    return title;
}

QString Book::getAuthor()
{
    return author;
}
QString Book::getPage()
{
    return QString::number(pages);
}
QString Book::getPublisher()
{
    return publisher;
}
QString Book::getGenre()
{
    return genre;
}
QString Book::getStatus()
{
    return status;
}

int Book::add_book_myBook(QSqlDatabase &db, QString username, int limit)
{
    query = new QSqlQuery(db);

    QString exec_statement;

    // check if the the book borrowed hit the limit
    exec_statement = "select COUNT(username) from borrowlist where username = '" + username + "'";
    query->exec(exec_statement);
    while(query->next())
    {
        if (query->value(0).toInt() >= limit)
            return 2;
    }

    // check the book is borrowed or not
    exec_statement = "SELECT * FROM book WHERE name = '";
    exec_statement += title + "'";
    query->exec(exec_statement);

    while(query->next())
    {
        if (query->value(5).toInt() == 0)
        {
            // Generate the execution statement for add a book
            exec_statement = "INSERT INTO borrowlist(username, bookname, expired) VALUES ('";
            exec_statement += username + "', '";
            exec_statement += title + "', ADDDATE(CURDATE(), INTERVAL 30 DAY))";
            query->exec(exec_statement);

            // set book to borrowed
            exec_statement = "UPDATE book SET is_borrowed = 1 WHERE name = '";
            exec_statement += title + "'";
            query->exec(exec_statement);

            // add to history
            exec_statement = "INSERT INTO history(username, book_title, borrowed_date, expired_date, status) VALUES ('";
            exec_statement += username + "', '";
            exec_statement += title + "', CURDATE(), ADDDATE(CURDATE(), INTERVAL 30 DAY), 1)";
            query->exec(exec_statement);

            return 1;
        }
        else
            return 0;
    }
    return 0;
}

bool Book::insert_new_book(QSqlDatabase &db)
{
    query = new QSqlQuery(db);
    QString exec_statement;

    // Generate the execution statement for add a book
    exec_statement = "INSERT INTO book(name, author, genre, pages, publisher) VALUES ('";
    exec_statement += title + "', '"
                   + author + "', '"
                   + genre  + "', '"
                   + QString::number(pages) + "', '"
                   + publisher + "')";
    bool result = query->exec(exec_statement);

    if (result)
        return true;
    return false;
}

bool Book::edit_new_book(QSqlDatabase &db)
{
    query = new QSqlQuery(db);
    QString exec_statement;

    exec_statement = "SET SQL_SAFE_UPDATES=0";
    query->exec(exec_statement);

    exec_statement = "DELETE FROM book WHERE name = '" + tmp + "'";
    query->exec(exec_statement);

    bool result = insert_new_book(db);

    int s = -1;
    if (status == "Available")
        s = 0;
    else if (status == "Borrowed")
        s = 1;
    else if (status == "Lost")
        s = 2;
    exec_statement = "UPDATE book SET is_borrowed=" + QString::number(s) + " WHERE name='" + title + "'";
    query->exec(exec_statement);

    exec_statement = "UPDATE borrowlist SET bookname='" + title + "' WHERE bookname='" + tmp + "'";
    query->exec(exec_statement);

    if (status == "Available")
    {
        exec_statement = "DELETE FROM borrowlist WHERE bookname = '" + title + "'";
        query->exec(exec_statement);
        exec_statement = "UPDATE history SET status=0 WHERE book_title='" + tmp + "'";
        query->exec(exec_statement);
    }

    if (result)
        return true;
    return false;
}

bool Book::delete_this_book(QSqlDatabase &db)
{
    query = new QSqlQuery(db);
    QString exec_statement = "SET SQL_SAFE_UPDATES=0";
    query->exec(exec_statement);

    if (status == "Borrowed")
    {
        exec_statement = "DELETE FROM borrowlist WHERE bookname = '" + title + "'";
        query->exec(exec_statement);
        exec_statement = "UPDATE history SET status=0 WHERE book_title='" + title + "'";
        query->exec(exec_statement);
    }

    exec_statement = "DELETE FROM book WHERE name = '" + tmp + "'";
    query->exec(exec_statement);

    return true;
}
