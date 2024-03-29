#include "paneldbdialog.h"
#include "ui_paneldbdialog.h"

PanelDBDialog::PanelDBDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PanelDBDialog)
{
    setWindowTitle("Connect to database");

    ui->setupUi(this);
}

PanelDBDialog::~PanelDBDialog()
{
    delete ui;
}

void PanelDBDialog::on_PanelDBDialog_accepted()
{
    QDialog::accept();
}

QString PanelDBDialog::getURL()
{
    return ui->URLInput->text();
}

QString PanelDBDialog::getUsername()
{
    return ui->usernameInput->text();
}

QString PanelDBDialog::getPassword()
{
    return ui->passwordInput->text();
}

QString PanelDBDialog::getDB()
{
    return ui->DBInput->text();
}

int PanelDBDialog::getPort()
{
    return ui->portInput->text().toInt();
}
