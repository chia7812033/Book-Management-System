#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "mylist.h"
#include "book.h"
#include "people.h"
#include "borrowdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUpDatabase();
private slots:
    void on_logIn_button_clicked();

    void on_lastPage_button_clicked();

    void findBook(QListWidgetItem *item);

    void on_borrow_button_clicked();

    void add_book_myBook();

    void on_myBook_button_clicked();

    void on_LastPage1_clicked();

    void on_SignInButton_clicked();

    void on_SignUpConfirmButton_clicked();

    void search_LineEdit_textChange();

    void on_SearchButton_clicked();

    void on_pushButton_addConfirm_clicked();

    void on_pushButton_main_clicked();

    void on_pushButton_addbook_clicked();

    void on_pushButton_advanced_clicked();

    void on_pushButton_history_clicked();

    void on_pushButton_enter_clicked();

    void on_pushButton_HISTORY_clicked();

    void on_pushButton_username_check_clicked();

    void on_pushButton_edit_clicked();

    void edit_book();

    void insert_book();

    void on_pushButton_delete_clicked();

    void delete_book();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QSqlQuery *query;
    Book book;
    People people;
    bool checkAccount(QString, QString, bool);
};
#endif // MAINWINDOW_H
