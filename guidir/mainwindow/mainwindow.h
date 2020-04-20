#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QTextBrowser>
#include "../guicontroller/guicontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_process_clicked();

    void on_pushButton_preview_clicked();

private:
    Ui::MainWindow *ui;
    void view_algo();
    void add_algo(const QStringList& list);
    QList<QListWidgetItem *> find_selected_items(QListWidget &list);
    QList<QListWidgetItem *> process_list(QListWidget &list);
    GuiController controller;
    QStringList make_txt_list(QList<QListWidgetItem*> list);
};

#endif // MAINWINDOW_H
