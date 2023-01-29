#ifndef BORROWDIALOG_H
#define BORROWDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class BorrowDialog;
}

class BorrowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowDialog(QWidget *parent = nullptr, QString t = "");
    ~BorrowDialog();

private slots:

private:
    Ui::BorrowDialog *ui;
};

#endif // BORROWDIALOG_H
