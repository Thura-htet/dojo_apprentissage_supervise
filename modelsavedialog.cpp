#include "modelsavedialog.h"
#include "ui_modelsavedialog.h"

ModelSaveDialog::ModelSaveDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModelSaveDialog)
{
    setWindowTitle("Save generated model");

    ui->setupUi(this);
}

ModelSaveDialog::~ModelSaveDialog()
{
    delete ui;
}
