#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QSqlQuery>

class SearchEngine : public QLineEdit
{
    Q_OBJECT
public:
    SearchEngine(QWidget *parent);
    void text_change_slots(QSqlDatabase &db, int choice);
    QStringList search_book_title(QSqlDatabase &db);
    QStringList search_book_author(QSqlDatabase &db);
    QStringList search_book_genre(QSqlDatabase &db);
    QStringList search_book_publisher(QSqlDatabase &db);
private:
    QCompleter StringCompleter;
    QCompleter *ModelCompleter;
    QStringListModel model;
    QSqlQuery *query;
};
#endif // SEARCHENGINE_H
