#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = nullptr);
    void setMaximum(int max);
    ~ProgressDialog();

private slots:
    void on_trainingProgress_valueChanged(int value);

    void on_ProgressDialog_accepted();

private:
    Ui::ProgressDialog *ui;
};

#endif // PROGRESSDIALOG_H
