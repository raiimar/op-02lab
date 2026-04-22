#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    // Кнопка выбора файла
    void on_buttonSelectFile_clicked();

    // Кнопка загрузки данных
    void on_buttonLoadData_clicked();

    // Кнопка расчёта метрик
    void on_buttonCalculateMetrics_clicked();

    private:
              Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
