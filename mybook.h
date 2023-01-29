#ifndef MYBOOK_H
#define MYBOOK_H

#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "borrowdialog.h"
#include "people.h"

class MyBook : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyBook(QWidget *parent);
    void findBorrowedBook(QSqlDatabase &db, QString username);
    QString show_history(QSqlDatabase &db, QString username);
    QString get_curdate(QSqlDatabase &db);
private:
    QSqlQuery *query;
    bool return_confirm;
    int row;

private slots:
    void return_confirm_dialog();
    void deleteThisLine();

};

#endif // MYBOOK_H
