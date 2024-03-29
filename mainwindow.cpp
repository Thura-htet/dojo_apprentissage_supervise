#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paneldbdialog.h"
#include "./ui_paneldbdialog.h"
#include "progressdialog.h"
#include "ui_paneldbdialog.h"
#include "modelsavedialog.h"
#include "ui_modelsavedialog.h"

#include <cstdlib>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->inputSlider->setMinimum(1);
    ui->inputSlider->setMaximum(255);
    ui->inputSlider->setValue(7);
    ui->paramLabel->setText(QString("Params : %1").arg(7));
    this->input_size = ui->inputSlider->value();
    this->output_size = 1;
    connect(ui->inputSlider, &QSlider::valueChanged, this, &MainWindow::on_inputSlider_valueChanged);

    ui->hiddenSlider->setMinimum(1);
    ui->hiddenSlider->setMaximum(255);
    ui->hiddenSlider->setValue(20);
    ui->nodesLabel->setText(QString("Nodes : %1").arg(20));
    this->hidden_size = ui->hiddenSlider->value();
    connect(ui->hiddenSlider, &QSlider::valueChanged, this, &MainWindow::on_hiddenSlider_valueChanged);

    ui->rateSlider->setMinimum(1);
    ui->rateSlider->setMaximum(99);
    ui->rateSlider->setValue(20);
    ui->nodesLabel->setText(QString("Rate : %1").arg(20));
    this->rate_size = ui->rateSlider->value();
    connect(ui->rateSlider, &QSlider::valueChanged, this, &MainWindow::on_rateSlider_valueChanged);

    ui->labelDial->setText(QString("Epochs : "));
    ui->dial->setMinimum(0);
    ui->dial->setMaximum(500000);
    ui->dial->setSingleStep(10000);
    ui->dial->setValue(400000);
    this->epochs = ui->dial->value();
    ui->labelDial->setText(QString("Epochs : %1").arg(400000));
    QObject::connect(ui->dial, &QDial::valueChanged, [&](int value)
    {
        EPOCHS = value;
        ui->labelDial->setText(QString("Epochs : %1").arg(value));
    });

    connect(ui->trainButton, &QPushButton::clicked, this, &MainWindow::on_trainButton_clicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputSlider_valueChanged(int value)
{
    ui->paramLabel->setText(QString("Params : %1").arg(value));
}


void MainWindow::on_hiddenSlider_valueChanged(int value)
{
    ui->nodesLabel->setText(QString("Nodes : %1").arg(value));
}


void MainWindow::on_rateSlider_valueChanged(int value)
{
    ui->rateLabel->setText(QString("Rate : %1").arg((double)value/100));
}


void MainWindow::on_trainButton_clicked()
{
    // DATABASE CONFIGURATION
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\SLAB45\\Documents\\dojo_models.db");


    // DATABASE CONNECTION
    if (!db.open()) {
        qCritical() << "Failed to open database:" << db.lastError().text();
    }

    // QUERIES GET THE TABLE'S DIMENSIONS
    QSqlQuery query;
    int nRows = 0, nCols = 0;
    QSqlRecord record;
    query.setForwardOnly(false);
    if (query.exec("SELECT * FROM model_training"))
    {
        while (query.next()) {
            // Process the current row
            // Example: Retrieve values from the current row
            // QString columnValue1 = query.value(0).toString(); // Assuming column index 0
            // int columnValue2 = query.value(1).toInt(); // Assuming column index 1
            nRows++;
        }
        qDebug() << nRows;

        nCols = query.record().count();
    }
    else
    {
        qCritical() << "Failed to execute query:" << query.lastError().text();
    }

    // MATRICE INSTANTIATION
    double **matrixX;
    double *matrixY;

    // MEMORY ALLOCATION FOR THE TWO MATRICES
    matrixX = (double **)malloc(nRows * sizeof(double *));
    for (int i=0; i<nRows; i++)
    {
        matrixX[i] = (double *)malloc((nCols+1) * sizeof(double));
    }
    matrixY = (double *)malloc(nRows * sizeof(double));
    // for (int=0; i<nRows; i++)
    // {
    //     matrixX[i] = new double [nCols];
    // }

    double** matrixTableViewTrain = (double **)malloc(nRows*sizeof(double *));
    for (int i=0; i<nRows; i++)
    {
        matrixTableViewTrain[i] = (double *)malloc((nCols) * sizeof(double));
    }

    qDebug()<<"Récupération des données sur table";
    int i = 0;
    if (query.exec("SELECT * FROM model_training"))
    {
        record = query.record();
        query.seek(0);

        while (query.next())
        {
            qDebug()<<"En cours...";

            for (int j = 0; j < nCols-1; j++)
            {
                // qDebug()<<"matriceX";
                matrixX[i][j] = query.value(j).toDouble();
                qDebug()<<"matriceX["<<i<<"]["<<j<<"] : " << matrixX[i][j];
            }

            matrixY[i] = query.value(nCols-1).toDouble();
            qDebug()<<"matriceY["<<i<<"] : " << matrixY[i];

            for (int j = 0; j < nCols; j++)
            {
                matrixTableViewTrain[i][j] = query.value(j).toDouble();
                qDebug()<<"matrixTableViewTrain["<<i<<"]["<<j<<"] : " << matrixTableViewTrain[i][j];
            }

            i++;
        }
        // the matrices seem to have been imported had a seg fault once
    }
    else
    {
        qDebug()<<"Erreur lors de la requête : "<<query.lastError().text();
    }

    // CLOSE DATABASE CONENCTION
    db.close();

    // ALLOCATE MEMORY FOR NEURAL LAYERS (first dimension)
    double **weights_ih = (double **)malloc(this->hidden_size * sizeof(double *));
    double **weights_ho = (double **)malloc(this->output_size * sizeof(double *));

    // ADD RANDOM VALUES FOR IH LAYER
    for (int i=0; i<this->hidden_size;i++)
    {
        // ALLOCATE MEMORY FOR NEURAL LAYERS (second dimension)
        weights_ih[i] = (double *)malloc(this->input_size * sizeof(double));
        for (int j=0; j>this->input_size; j++)
        {
            // ADD RANDOM VALUE AT THE ALLOCATED MEMORY
            weights_ih[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
    qDebug()<<"weights_ih[5][8] : "<<weights_ih[5][8];

    // ADD RANDOM VALUES FOR HO LAYER
    for (int i=0; i<this->output_size; i++)
    {
        // ALLOCATE MEMORY FOR NEURAL LAYERS (second dimension)
        weights_ho[i] = (double *)malloc(this->hidden_size * sizeof(double));
        for (int j=0; j<this->hidden_size; j++)
        {
            // ADD RANDOM VALUE AT THE ALLOCATED MEMORY
            weights_ho[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
    qDebug()<<"weights_ho[0][5] : "<<weights_ho[0][5];

    // LEARNING AND TRAINING LOGIC
    for (int epoch; epoch<this->epochs; epoch++)
    {
        for (int i = 0; i < nRows; i++)
        {
            // PROPAGATION AVANT
            double *hidden = (double *)malloc(this->hidden_size*sizeof(double));
            for (int j = 0; j < this->hidden_size; j++)
            {
                double sum = 0;
                for (int k = 0; k < this->input_size; k++)
                {
                    // why [i][k]/[j][k] ?
                    sum += matrixX[i][k] * weights_ih[]
                }
            }
        }
    }


    // FREE UP ALLOCATED MEMORY
    free(matrixX);
    free(matrixY);
}


void MainWindow::on_predictButton_clicked()
{

}


void MainWindow::on_loadButton_clicked()
{
    panelDialog = new PanelDBDialog(this);
    panelDialog->exec();
}


void MainWindow::on_saveButton_clicked()
{
    modelsaveDialog = new ModelSaveDialog(this);
    modelsaveDialog->exec();
}

