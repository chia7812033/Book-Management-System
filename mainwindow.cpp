#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "borrowdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->libraryPage->askForDataBase(database);
    QObject::connect(ui->bookList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), ui->libraryPage, SLOT(jumpToInfoPage(QListWidgetItem *)));
    QObject::connect(ui->bookList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(findBook(QListWidgetItem *)));
    QObject::connect(ui->lineEdit_search, SIGNAL(textChanged(const QString &)), this, SLOT(search_LineEdit_textChange()));

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->SignUpBox->setVisible(false);
    setUpDatabase();
    query = new QSqlQuery(database);
    ui->libraryPage->setCurrentIndex(0);

    // set advanced botton invisble
    ui->pushButton_advanced->setVisible(false);
    ui->pushButton_edit->setVisible(false);
    ui->pushButton_delete->setVisible(false);

    // display books
    ui->bookList->displayRandomBook(database);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// connect to the database
void MainWindow::setUpDatabase()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("140.113.65.168");
    //database.setHostName("127.0.0.1");
    database.setDatabaseName("librarydb");
    database.setUserName("testuser");
    database.setPassword("password");
    database.setPort(3306);
    database.open();

    query = new QSqlQuery(database);
    query->exec("SET SQL_SAFE_UPDATES=0");
}

// if the log in button is clicked
void MainWindow::on_logIn_button_clicked()
{
    // check there's no user login
    if (people.check_status() == false)
    {
        // load Account
        QString username = ui->lineEdit_username->text();
        QString password = ui->lineEdit_password->text();
        bool is_staff = ui->radioButton_staff->isChecked();

        // if username or password correct
        if (checkAccount(username, password, is_staff))
        {
            // set user info
            people.set_username(username);
            people.login();

            // Show the message of "logic successful
            QMessageBox::information(this, "Login message", "Login Successful");

            // Set login label
            ui->login_label->setText("Welcome " + username);

            // display random books
            ui->bookList->displayRandomBook(database);

            // set log in button to log out
            ui->logIn_button->setText("Log out");
        }
        // if username or password incorrect
        else
        {
            QMessageBox::information(this, "Login message", "Username or password is wrong");

            // Set login label
            ui->login_label->setText("Try again");
        }

        // if is staff, set the advanced button visible
        if (is_staff && people.check_status())
        {
            ui->pushButton_advanced->setVisible(true);
            ui->pushButton_edit->setVisible(true);
            people.set_limit(7);
        }
        else
        {
            people.set_limit(5);
            ui->pushButton_advanced->setVisible(false);
            ui->pushButton_edit->setVisible(false);
        }
    }
    // if someone is login, then log out
    else
    {
        people.reset();
        ui->logIn_button->setText("Log in");
        ui->lineEdit_username->clear();
        ui->lineEdit_password->clear();
        ui->bookList->clear();
        ui->libraryPage->setCurrentIndex(0);
        ui->pushButton_advanced->setVisible(false);
     }

}

// go back to the main page if the lastPage is clicked
void MainWindow::on_lastPage_button_clicked()
{
    ui->libraryPage->setCurrentIndex(0);
}

// search the book in database and store the book info in Class Book
void MainWindow::findBook(QListWidgetItem *item)
{
    // find book in database
    query->exec("SELECT * FROM book WHERE name = '" + item->text() + "'");
    while (query->next())
    {
        book.set_name(query->value(0).toString());
        book.set_author(query->value(1).toString());
        book.set_genre(query->value(2).toString());
        book.set_pages(query->value(3).toInt());
        book.set_publisher(query->value(4).toString());
        book.set_status(query->value(5).toString());
    }

    // display the book info on text edit
    ui->bookInfo->displayBookInfo(book);
}

// when the borrow button clicked, show the confirmation window
void MainWindow::on_borrow_button_clicked()
{
    if (people.check_status())
    {
        BorrowDialog *confirmDialog = new BorrowDialog(nullptr, "Are you sure borrow this book?");
        QObject::connect(confirmDialog, SIGNAL(accepted()), this, SLOT(add_book_myBook()));
        confirmDialog->setModal(true);
        //confirmDialog->exec();
        confirmDialog->show();
    }
    else
    {
        QMessageBox::information(this, "message", "You must log in first");
    }
}

// check the if the account is correct(find if it is in database)
bool MainWindow::checkAccount(QString username, QString password, bool is_staff)
{
    // Generate the execution statement
    QString exec_statement;
    exec_statement = "SELECT * FROM account WHERE username = '";
    exec_statement += username + "' && userpassword = MD5('";
    exec_statement += password + "') && identity = "  + QString::number(is_staff);

    // return ture if the account is matched in database
    query->exec(exec_statement);
    while (query->next())
    {
        if (query->value(1).toString() == username)
            return true;
        else
            return false;
    }
    return false;
}

void MainWindow::add_book_myBook()
{
    int error = book.add_book_myBook(database, people.get_username(), people.get_limit());
    if (error == 0)
        QMessageBox::information(this, "Borrow message", "This book has been borrowed");
    else if (error == 1)
        QMessageBox::information(this, "Borrow message", "Success");
    else if (error == 2)
        QMessageBox::information(this, "Borrow message", "You cannot borrow more than " + QString::number(people.get_limit()) + " books");
}

void MainWindow::on_myBook_button_clicked()
{
    if (people.check_status())
    {
        ui->libraryPage->setCurrentIndex(2);
        ui->myBook->findBorrowedBook(database, people.get_username());
    }
}

void MainWindow::on_LastPage1_clicked()
{
    ui->libraryPage->setCurrentIndex(0);
}

void MainWindow::on_SignInButton_clicked()
{
    // check if there's someone login
    // if not
    if (people.check_status() == false)
    {
        // show the sign up box
        if (ui->SignUpBox->isVisible() == false)
            ui->SignUpBox->setVisible(true);
    }
    else
       QMessageBox::information(this, "message", "You have logged in");
}

void MainWindow::on_SignUpConfirmButton_clicked()
{
    // load Account
    QString name = ui->lineEdit_namesignup->text();
    QString username = ui->lineEdit_usernamesignup->text();
    QString password = ui->lineEdit_passwordsignup->text();
    QString repassword = ui->lineEdit_reentersignup->text();

    if (people.check_username_exist(database, username))
    {

        if (password != repassword)
        {
            QMessageBox::information(this, "message", "Passwords must match");
            ui->lineEdit_passwordsignup->clear();
            ui->lineEdit_reentersignup->clear();
            return;
        }

        people.signUp(database, name, username, password);

        QMessageBox::information(this, "message", "Sign up successful!!");
        ui->SignUpBox->setVisible(false);
    }
    else
    {
        QMessageBox::information(this, "message", "This username has been used");
        ui->lineEdit_usernamesignup->clear();
        ui->lineEdit_passwordsignup->clear();
        ui->lineEdit_reentersignup->clear();
    }
}

void MainWindow::search_LineEdit_textChange()
{
    // set the completer for search_box
    int choice = ui->comboBox->currentIndex();
    ui->lineEdit_search->text_change_slots(database, choice);
}

void MainWindow::on_SearchButton_clicked()
{
    if (ui->lineEdit_search->text() != "")
    {
        // call the search engine to find the books
        QStringList books;
        if (ui->comboBox->currentIndex() == 0)
            books = ui->lineEdit_search->search_book_title(database);
        else if (ui->comboBox->currentIndex() == 1)
            books = ui->lineEdit_search->search_book_author(database);
        else if (ui->comboBox->currentIndex() == 2)
            books = ui->lineEdit_search->search_book_genre(database);
        else if (ui->comboBox->currentIndex() == 3)
            books = ui->lineEdit_search->search_book_publisher(database);



        // jump to main page to display books
        ui->libraryPage->setCurrentIndex(0);
        // clear the book list
        ui->bookList->clear();
        // show the books
        ui->bookList->displaySearchResult(books);
    }
}

void MainWindow::on_pushButton_addConfirm_clicked()
{
    book.set_name(ui->lineEdit_title->text());
    book.set_author(ui->lineEdit_author->text());
    book.set_genre(ui->lineEdit_genre->text());
    book.set_pages(ui->lineEdit_pages->text().toInt());
    book.set_publisher(ui->lineEdit_publisher->text());
    book.set_status(QString::number(ui->comboBox_2->currentIndex()));
    if (ui->groupBox_editbook->title() == "ADD")
    {
        BorrowDialog *confirmDialog = new BorrowDialog(nullptr, "ADD THIS BOOK");
        QObject::connect(confirmDialog, SIGNAL(accepted()), this, SLOT(insert_book()));
        confirmDialog->exec();

    }
    else if (ui->groupBox_editbook->title() == "EDIT")
    {
        BorrowDialog *confirmDialog = new BorrowDialog(nullptr, "EDIT THIS BOOK");
        QObject::connect(confirmDialog, SIGNAL(accepted()), this, SLOT(edit_book()));
        confirmDialog->exec();
    }
    else
    {
        qDebug() << "error";
    }
}

void MainWindow::on_pushButton_main_clicked()
{
    ui->bookList->displayRandomBook(database);
    ui->libraryPage->setCurrentIndex(0);
}

void MainWindow::on_pushButton_addbook_clicked()
{
    ui->groupBox_editbook->setTitle("ADD");
    ui->libraryPage->setCurrentIndex(4);
    ui->lineEdit_title->clear();
    ui->lineEdit_author->clear();
    ui->lineEdit_genre->clear();
    ui->lineEdit_pages->clear();
    ui->lineEdit_publisher->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->pushButton_delete->setVisible(false);
}

void MainWindow::on_pushButton_advanced_clicked()
{
    ui->libraryPage->setCurrentIndex(3);
}

void MainWindow::on_pushButton_history_clicked()
{
    ui->myBook->show_history(database, people.get_username());
}

void MainWindow::on_pushButton_enter_clicked()
{
    QString username_for_search = ui->lineEdit_usernameSearch->text();
    QString name = ui->myBook_2->show_history(database, username_for_search);
    ui->label_11->setText(name);

}

void MainWindow::on_pushButton_HISTORY_clicked()
{
    ui->libraryPage->setCurrentIndex(5);
}

void MainWindow::on_pushButton_username_check_clicked()
{
    QString username = ui->lineEdit_usernamesignup->text();
    if (username != "")
    {
        bool ok = people.check_username_exist(database, username);
        if (ok)
            ui->label_check->setText("OK!");
        else
            ui->label_check->setText("EXISTED");
    }
}

void MainWindow::on_pushButton_edit_clicked()
{
    ui->groupBox_editbook->setTitle("EDIT");
    ui->libraryPage->setCurrentIndex(4);
    ui->lineEdit_title->setText(book.getTitle());
    ui->lineEdit_author->setText(book.getAuthor());
    ui->lineEdit_genre->setText(book.getGenre());
    ui->lineEdit_pages->setText(book.getPage());
    ui->lineEdit_publisher->setText(book.getPublisher());
    if (book.getStatus() == "Available")
        ui->comboBox_2->setCurrentIndex(0);
    else if (book.getStatus() == "Borrowed")
        ui->comboBox_2->setCurrentIndex(1);
    else if (book.getStatus() == "Lost")
        ui->comboBox_2->setCurrentIndex(2);
    book.tmp = book.getTitle();
    ui->pushButton_delete->setVisible(true);
}

void MainWindow::edit_book()
{
    if (book.edit_new_book(database))
    {
        book.set_name(ui->lineEdit_title->text());
        book.set_author(ui->lineEdit_author->text());
        book.set_genre(ui->lineEdit_genre->text());
        book.set_pages(ui->lineEdit_pages->text().toInt());
        book.set_publisher(ui->lineEdit_publisher->text());
        book.set_status(ui->comboBox_2->currentText());
        QMessageBox::information(this, "message", "SUCCESS");
    }
    else
        QMessageBox::information(this, "Error", "FAIL");
}

void MainWindow::insert_book()
{
    qDebug() << "error1";
    if (book.insert_new_book(database))
        QMessageBox::information(this, "message", "SUCCESS");
    else
        QMessageBox::information(this, "Error", "FAIL");
}

void MainWindow::on_pushButton_delete_clicked()
{
    BorrowDialog *confirmDialog = new BorrowDialog(nullptr, "DELETE THIS BOOK");
    confirmDialog->setWindowTitle("WARNING!!!");
    QObject::connect(confirmDialog, SIGNAL(accepted()), this, SLOT(delete_book()));
    confirmDialog->exec();
}

void MainWindow::delete_book()
{
    if (book.delete_this_book(database))
        QMessageBox::information(this, "message", "SUCCESS");
    else
        QMessageBox::information(this, "Error", "FAIL");
    ui->lineEdit_title->clear();
    ui->lineEdit_author->clear();
    ui->lineEdit_genre->clear();
    ui->lineEdit_pages->clear();
    ui->lineEdit_publisher->clear();
    book.tmp  = "";
}
