#include "mybook.h"
#include <QDebug>
#include <QPushButton>


MyBook::MyBook(QWidget *parent) : QTableWidget(parent)
{
    return_confirm = false;
    row = -1;
}

// display the book the user borrowed
void MyBook::findBorrowedBook(QSqlDatabase &db, QString username)
{
    this->clear();
    this->setColumnCount(3);

    QStringList hlabels;
    hlabels << "Title" << "Overdue date" << "Return";
    this->setHorizontalHeaderLabels(hlabels);

    query = new QSqlQuery(db);
    query->exec("SELECT * FROM borrowlist WHERE username = '" + username + "'");
    this->setRowCount(query->size());
    int i = 0;
    while (query->next())
    {
        for (int j = 0; j < 2; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QString qStr = query->value(j+1).toString();
            item->setText(qStr);
            this->setItem(i, j, item);
        }
        QPushButton *b = new QPushButton("return",this);
        this->setCellWidget(i, 2,b);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(deleteThisLine()));
        i++;
    }
}

void MyBook::deleteThisLine()
{
    //sender(): QPushButton
    QWidget *w = qobject_cast<QWidget *>(sender()->parent());
    if(w)
    {
        // find the row should be deleted
        row = this->indexAt(w->pos()).row();

        BorrowDialog *confirmDialog = new BorrowDialog(nullptr, "Do you want to return this book?");
        QObject::connect(confirmDialog, SIGNAL(accepted()), this, SLOT(return_confirm_dialog()));
        confirmDialog->setModal(true);
        //confirmDialog->exec();
        confirmDialog->show();
    }
}

void MyBook::return_confirm_dialog()
{
    // set the borrowed status to not borrowed
    QString title =  this->takeItem(row, 0)->text();
    QString exec_statement;
    exec_statement = "UPDATE book SET is_borrowed = 0 WHERE name = '";
    exec_statement += title + "'";
    query->exec(exec_statement);

    // set book in history to unborrowed
    exec_statement = "UPDATE history SET status = 0 WHERE book_title = '";
    exec_statement += title + "'";
    query->exec(exec_statement);

    // delete the borrow record
    exec_statement = "DELETE FROM borrowlist WHERE bookname = '";
    exec_statement += title + "'";
    query->exec(exec_statement);


    this->removeRow(row);
    this->setCurrentCell(0, 0);
}

QString MyBook::show_history(QSqlDatabase &db, QString username)
{
    QString name = "";
    this->clear();
    this->setColumnCount(4);

    QStringList hlabels;
    hlabels << "Title" << "Borrowed date" << "Overdue date" << "Status";
    this->setHorizontalHeaderLabels(hlabels);

    query = new QSqlQuery(db);

    query->exec("SELECT * FROM account WHERE username = '" + username + "'");
    while(query->next())
    {
        name = query->value(3).toString();
    }

    query->exec("SELECT * FROM history WHERE username = '" + username + "'");
    this->setRowCount(query->size());
    int i = 0;
    while (query->next())
    {
        for (int j = 1; j < 5; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            QString qStr = query->value(j+1).toString();
            if (j == 4)
            {
                if (qStr == "0")
                    qStr = "Returned";
                else if (qStr == "1")
                    qStr = "Borrowed";
                else if (qStr == "2")
                    qStr = "Lost";
            }
            item->setText(qStr);
            this->setItem(i, j - 1, item);
        }
        i++;
    }

    return name;
}

// get current date from database
QString MyBook::get_curdate(QSqlDatabase &db)
{
    query = new QSqlQuery(db);
    query->exec("select curdate()");
    QString date = query->value(0).toString();

    return date;
}

