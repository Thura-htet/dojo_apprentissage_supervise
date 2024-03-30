#include "loadtrainingmodel.h"
#include "ui_loadtrainingmodel.h"

#include <QFileDialog>

LoadTrainingModel::LoadTrainingModel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoadTrainingModel)
{
    ui->setupUi(this);
    this->defaultPath = "/Users/thura/projects";
    ui->databaseInput->setText(this->defaultPath);
}

LoadTrainingModel::~LoadTrainingModel()
{
    delete ui;
}

void LoadTrainingModel::on_openFileButton_clicked()
{
    QString dbName = QFileDialog::getOpenFileName(this,
                                                  tr("Choose Database"),
                                                  this->defaultPath,
                                                  tr("Sqlite Files (*.db);;"));
    ui->databaseInput->setText(dbName);
    this->selectedDB = ui->databaseInput->text();
}


void LoadTrainingModel::on_pushButton_clicked()
{
    if (!this->selectedDB.isEmpty())
    {
        // Emit the fileSelected signal with the selected file path
        emit fileSelected(this->selectedDB);
    }
}

