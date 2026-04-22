#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iterator.h"
#include "entrypoint.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>

static AppContext context;

// === Конструктор ===
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    doOperation(INITIALIZATION, &context, NULL);

    // делаем таблицу пустой
    ui->tableWidgetData->setColumnCount(7);
    QStringList headers = {
        "Year", "Region", "NatGrowth",
        "Birth", "Death", "DemWeight", "Urban"
    };
    ui->tableWidgetData->setHorizontalHeaderLabels({
        "Year","Region","NatGrowth","Birth","Death","DemWeight","Urban"
    });
}

// === Деструктор ===
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonSelectFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open CSV", "", "*.csv");

    //qDebug() << "Selected file:" << fileName;

    if (!fileName.isEmpty()) {
        ui->lineEditFileName->setText(fileName);
    }
}

// === Загрузка данных ===
void MainWindow::on_buttonLoadData_clicked()
{
    AppParams params;

    QString fileName = ui->lineEditFileName->text();

    //fileName = fileName.trimmed();
    //fileName.replace("file:///", "");

    strncpy(params.filePath, fileName.toStdString().c_str(), sizeof(params.filePath)-1);
    params.filePath[sizeof(params.filePath)-1] = '\0';

    doOperation(LOAD_DATA, &context, &params);

    // Ошибка открытия файла
    if (context.status != STATUS_OK) {
        QMessageBox::warning(this, "Error", "Failed to open file");
        return;
    }

    // Информация о загрузке
    QString info = QString("Total: %1\nValid: %2\nErrors: %3")
                       .arg(context.totalRows)
                       .arg(context.validRows)
                       .arg(context.errorRows);

    QMessageBox::information(this, "Load Result", info);

    // Заполняем таблицу
    ui->tableWidgetData->setRowCount(0);

    Iterator it = iterator_create(context.dataList);

    int rowIndex = 0;
    QString filterRegion = ui->lineEditRegion->text();

    while (iterator_has_next(&it)) {

        DataRow* row = iterator_get(&it);

        if (row != NULL) {

            if (filterRegion.isEmpty() ||
                QString(row->region) == filterRegion) {

                ui->tableWidgetData->insertRow(rowIndex);

                ui->tableWidgetData->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(row->year)));
                ui->tableWidgetData->setItem(rowIndex, 1, new QTableWidgetItem(QString(row->region)));
                ui->tableWidgetData->setItem(rowIndex, 2, new QTableWidgetItem(QString::number(row->natural_population_growth)));
                ui->tableWidgetData->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(row->birth_rate)));
                ui->tableWidgetData->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(row->death_rate)));
                ui->tableWidgetData->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(row->general_demographic_weight)));
                ui->tableWidgetData->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(row->urbanization)));

                rowIndex++;
            }
        }

        iterator_next(&it);
    }
}

// === Расчёт метрик ===
void MainWindow::on_buttonCalculateMetrics_clicked()
{
    AppParams params;

    QString region = ui->lineEditRegion->text();
    QString columnStr = ui->lineEditColumnNumber->text();

    // Проверка колонки
    bool ok;
    int column = columnStr.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid column number");
        return;
    }

    strncpy(params.region, region.toStdString().c_str(), sizeof(params.region)-1);
    params.region[sizeof(params.region)-1] = '\0';
    params.columnIndex = column;

    doOperation(CALCULATE_METRICS, &context, &params);

    if (context.status != STATUS_OK) {
        QMessageBox::warning(this, "Error", "Calculation failed");
        return;
    }

    ui->lineEditMin->setText(QString::number(context.minValue));
    ui->lineEditMax->setText(QString::number(context.maxValue));
    ui->lineEditMedian->setText(QString::number(context.medianValue));
}
