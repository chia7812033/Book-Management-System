#ifndef BOOKINFO_H
#define BOOKINFO_H

#include <QTextEdit>
#include "book.h"

class BookInfo : public QTextEdit
{
    Q_OBJECT
public:
    BookInfo(QWidget *parent);
    void displayBookInfo(Book &book);
};

#endif // BOOKINFO_H
