#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view_algo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_load_clicked()
{
    QTextEdit *text_path = ui->textEdit_path;
    QString path = text_path->toPlainText();
    text_path->setText("");
    // Тут надо path передать как путь Controller'у, он даст QImage
    QImage image;
    QLabel *label = ui->label_image;
    label->setPixmap(QPixmap::fromImage(image)); // Здесь картинка включилась (надеюсь)
}

void MainWindow::view_algo() {
    QListWidget *algo_list = ui->listWidget_algo;

    static QStringList LIST_ITEMS =
        QStringList() << "C++" << "Python" << "Java" << "C#" << "PHP" << "Ruby" << "JavaScript";

    foreach( const QString& item, LIST_ITEMS ) {
        QListWidgetItem* listItem = new QListWidgetItem( item );
        listItem->setIcon( QPixmap( item + ".png" ) );
        // Включаем возможность редактирования
        listItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
        algo_list->addItem( listItem );
    }

    algo_list->setSelectionMode( QListWidget::MultiSelection );

}

void MainWindow::on_pushButton_process_clicked()
{
    QListWidget *algo_list = ui->listWidget_algo;
    QString what_printed("");
    foreach (const QListWidgetItem* item, algo_list->selectedItems()) {
        what_printed += " " + item->text();
    }
    // Вернёт строчки алгоритмов, надо переделать в алгоритмы и передать контроллеру?
    QTextBrowser *view_message = ui->textBrowser_message;
    view_message->setText(what_printed);
}
