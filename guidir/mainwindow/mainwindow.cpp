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

    add_algo(LIST_ITEMS);

    algo_list->setSelectionMode( QListWidget::MultiSelection );

}

void MainWindow::add_algo(const QStringList& list)
{
    foreach( const QString& item, list ) {
        QListWidgetItem* listItem = new QListWidgetItem( item );
        // listItem->setIcon( QPixmap( item + ".png" ) );
        listItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled );
        listItem->setFlags(listItem->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        listItem->setCheckState(Qt::Unchecked); // AND initialize check state
        ui->listWidget_algo->addItem( listItem );
    }
}

void MainWindow::on_pushButton_process_clicked()
{
    QListWidget *algo_list = ui->listWidget_algo;
    QString what_printed("");
    QList<QListWidgetItem *> selectedItems = find_selected_items(*algo_list);
    foreach (const QListWidgetItem* item, selectedItems) {
        what_printed += " " + item->text();
    }
    // Вернёт строчки алгоритмов, надо переделать в алгоритмы и передать контроллеру?
    QTextBrowser *view_message = ui->textBrowser_message;
    view_message->setText(what_printed);
}

QList<QListWidgetItem *> MainWindow::find_selected_items(QListWidget &list)
{
    QList<QListWidgetItem *> result;

    for(int row = 0; row < list.count(); row++)
    {
             QListWidgetItem *item = list.item(row);
             if (item->checkState() != Qt::Unchecked)
                 result.push_back(item);
    }
    return result;
}
