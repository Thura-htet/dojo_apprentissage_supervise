#ifndef LOADTRAININGMODEL_H
#define LOADTRAININGMODEL_H

#include <QDialog>

namespace Ui {
class LoadTrainingModel;
}

class LoadTrainingModel : public QDialog
{
    Q_OBJECT

public:
    explicit LoadTrainingModel(QWidget *parent = nullptr);
    ~LoadTrainingModel();

signals:
    void fileSelected(const QString &db);

private slots:
    void on_openFileButton_clicked();

    void on_pushButton_clicked();

private:
    QString defaultPath;
    QString selectedDB;
    Ui::LoadTrainingModel *ui;
};

#endif // LOADTRAININGMODEL_H
