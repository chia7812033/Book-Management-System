#ifndef LIBRARYPAGE_H
#define LIBRARYPAGE_H

#include <QStackedWidget>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlDatabase>

class LibraryPage : public QStackedWidget
{
    Q_OBJECT
public:
    LibraryPage(QWidget *parent);
    void askForDataBase(QSqlDatabase &db);
private:
    QString findBook(QListWidgetItem *, QSqlDatabase &db);
    QSqlQuery *query;
    QSqlDatabase *database;
private slots:
    void jumpToInfoPage(QListWidgetItem *);

};

#endif // LIBRARYPAGE_H
