#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProgressDialog)
{
    setWindowTitle("Training...");

    ui->setupUi(this);
    ui->trainingProgress->setMinimum(0);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::setMaximum(int max)
{
    ui->trainingProgress->setMaximum(max);
}

void ProgressDialog::on_trainingProgress_valueChanged(int value)
{
    ui->trainingProgress->setValue(value);
}

void ProgressDialog::on_ProgressDialog_accepted()
{
    QDialog::accept();
}
