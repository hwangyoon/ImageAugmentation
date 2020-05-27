#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QTextBrowser>
#include "../guicontroller/guicontroller.h"

namespace Ui {
/*class with GUI implementation*/
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLoad_clicked();

    void on_pushButtonProcess_clicked();

    void on_pushButtonPreview_clicked();

    void on_pushButtonOverlay_clicked();

private:
    Ui::MainWindow *ui;
    void viewAlgo();
    void addAlgo(const QStringList& list);
    QList<QListWidgetItem *> findSelectedItems(QListWidget &list);
    QList<QListWidgetItem *> processList(QListWidget &list);
    GuiController controller;
    QStringList makeTxtList(QList<QListWidgetItem*> list);
    QString getFileName();
    bool overlay;
};

#endif // MAINWINDOW_H
