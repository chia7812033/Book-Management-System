#include "borrowdialog.h"
#include "ui_borrowdialog.h"
#include <QMessageBox>

BorrowDialog::BorrowDialog(QWidget *parent, QString t) :
    QDialog(parent),
    ui(new Ui::BorrowDialog)
{
    ui->setupUi(this);
    ui->label->setText(t);
}

BorrowDialog::~BorrowDialog()
{
    delete ui;
}
