#include "bookinfo.h"

BookInfo::BookInfo(QWidget *parent) : QTextEdit(parent)
{

}

void BookInfo::displayBookInfo(Book &book)
{
    QString info = book.getBookInfo();
    this->setText(info);
}
