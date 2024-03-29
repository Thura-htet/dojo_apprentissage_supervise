#ifndef PANELDBDIALOG_H
#define PANELDBDIALOG_H

#include <QDialog>

namespace Ui {
class PanelDBDialog;
}

class PanelDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PanelDBDialog(QWidget *parent = nullptr);
    QString getURL();
    QString getUsername();
    QString getPassword();
    QString getDB();
    int getPort();

    ~PanelDBDialog();

private slots:
    void on_PanelDBDialog_accepted();

private:
    Ui::PanelDBDialog *ui;
};

#endif // PANELDBDIALOG_H
