#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view_algo();
    QString info = "Привет ^^ \nКак пользоваться этим приложением?.. (мотать вниз для ответа) \n\
                     - Чтобы загрузить картику надо ввести в первое поле адрес загружаемой картинки и нажать на кнопку LOAD \n\
                     - Чтобы начать обработку надо ввести во второе поле место для сохранения и нажать на кнопку PROCESS \n\
                     - Чтобы обработка не была пустым копированием надо выбрать алгоритмы в списке справа\
(то, как они будут выглядеть можно посмотреть, нажав на кнопку PREVIEW)";
    QTextBrowser *view_message = ui->textBrowser_info;
    view_message->setText(info);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_load_clicked()
{
    QTextEdit *text_path_in = ui->textEdit_path_in;
    QString path_in = text_path_in->toPlainText();
    text_path_in->setText("");
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

QList<QListWidgetItem *> MainWindow::process_list(QListWidget &list)
{
    QString what_printed("");
    QList<QListWidgetItem *> selectedItems = find_selected_items(list);
    foreach (const QListWidgetItem* item, selectedItems) {
        what_printed += " " + item->text();
    }
    QTextBrowser *view_message = ui->textBrowser_info;
    view_message->setText(what_printed);
    return selectedItems;
}

void MainWindow::on_pushButton_process_clicked()
{
    //передам process_list();
}

void MainWindow::on_pushButton_preview_clicked()
{
    //передам process_list();
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
