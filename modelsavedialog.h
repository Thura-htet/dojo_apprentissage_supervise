#ifndef MODELSAVEDIALOG_H
#define MODELSAVEDIALOG_H

#include <QDialog>

namespace Ui {
class ModelSaveDialog;
}

class ModelSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelSaveDialog(QWidget *parent = nullptr);
    ~ModelSaveDialog();

private:
    Ui::ModelSaveDialog *ui;
};

#endif // MODELSAVEDIALOG_H
