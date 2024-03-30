#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paneldbdialog.h"
#include "progressdialog.h"
#include "modelsavedialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_inputSlider_valueChanged(int value);

    void on_hiddenSlider_valueChanged(int value);

    void on_rateSlider_valueChanged(int value);

    void on_trainButton_clicked();

    void on_predictButton_clicked();

    void on_loadButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;

    int input_size;
    int hidden_size;
    double learning_rate;
    int output_size;
    int epochs;


    PanelDBDialog *panelDialog;
    ProgressDialog *progressDialog;
    ModelSaveDialog *modelsaveDialog;
};
#endif // MAINWINDOW_H
