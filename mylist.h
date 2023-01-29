#ifndef MYLIST_H
#define MYLIST_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

class myList : public QListWidget
{
    Q_OBJECT
public:
    explicit myList(QWidget *parent);
    void displayRandomBook(QSqlDatabase &db);
    void findBorrowedBook(QSqlDatabase &db, QString username);
    void displaySearchResult(QStringList);
private:
    QSqlQuery *query;
signals:
    //void itemDoubleClicked(QListWidgetItem *item);
private slots:
    void a(QListWidgetItem *item)
    {
        qDebug() << item->text();
    }

};


#endif // MYLIST_H
