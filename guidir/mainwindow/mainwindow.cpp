#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewAlgo();
    QString info = "Привет ^^ \nКак пользоваться этим приложением?.. (мотать вниз для ответа) \n\
                     - Чтобы загрузить картику надо ввести в первое поле адрес загружаемой директории(для загрузки всех изображений из директории) или ничего не вводить(для загрузки одного изображения) и нажать на кнопку LOAD \n\
                     - Чтобы начать обработку надо ввести во второе поле место для сохранения и нажать на кнопку PROCESS \n\
                     - Чтобы обработка не была пустым копированием надо выбрать алгоритмы в списке справа\
(то, как они будут выглядеть можно посмотреть, нажав на кнопку PREVIEW)";
    QTextBrowser *viewMessage = ui->textBrowserInfo;
    viewMessage->setText(info);
    QLabel *label = ui->labelImage;
    QString whatPrinted = "Здесь появится Ваша картинка ^^ \n     (но сначала её стоит загрузить)";
    label->setText(whatPrinted);
    overlay = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getFileName()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("JPG (*.jpg);;All Files (*)"));
    return fileName;
}

void MainWindow::on_pushButtonLoad_clicked()
{
    QTextEdit *textPathIn = ui->textEditPathIn;
    QString pathInText = textPathIn->toPlainText();
    //textPathIn->setText("");
    // Тут надо path передать как путь Controller'у, он даст QImage
    // Забили на это, сами загрузим
    QString pathIn;
    if (pathInText.isEmpty()) {
        pathInText = getFileName();
        pathIn = pathInText;
    }
    else
        pathIn = "samples/animal.jpg";
    QLabel *label = ui->labelImage;
    QPixmap *p=new QPixmap(pathIn);
    QPixmap p1(p->scaled ( 300,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    label->setPixmap(p1); // Здесь картинка включилась (надеюсь)
    controller.savePathIn(pathInText);
    //textPathIn->setText("DONE");
}

void MainWindow::viewAlgo() {
    QListWidget *algoList = ui->listWidgetAlgo;

    static QStringList LIST_ITEMS =
        QStringList() << "Crop from middle"
                      << "Horizontal flip"
                      << "Rotate 45 dg"
                      << "Rotate 90 dg"
                      << "Vertical flip"
                      << "Dithering"
                      << "GaussianNoise"
                      << "Kuwahara"
                      << "Lightening"
                      << "RGBTone"
                      << "WhiteBlack"
                      << "BlurConvolution"
                      << "NegativeConvolution"
                      << "SharpenConvolution"
                      << "EmbrossConvolution"
                      << "LightBlurConvolution"
                      << "LightSharpenConvolution"
                      << "LightEmbrossConvolution"
                      << "GaussBlurConvolution";

    addAlgo(LIST_ITEMS);

    algoList->setSelectionMode( QListWidget::MultiSelection );

}

void MainWindow::addAlgo(const QStringList& list)
{
    foreach( const QString& item, list ) {
        QListWidgetItem* listItem = new QListWidgetItem( item );
        // listItem->setIcon( QPixmap( item + ".png" ) );
        listItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled );
        listItem->setFlags(listItem->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        listItem->setCheckState(Qt::Unchecked); // AND initialize check state
        ui->listWidgetAlgo->addItem( listItem );
    }
}

QList<QListWidgetItem *> MainWindow::processList(QListWidget &list)
{
    QString whatPrinted("");
    QList<QListWidgetItem *> selectedItems = findSelectedItems(list);
    foreach (const QListWidgetItem* item, selectedItems) {
        whatPrinted += " " + item->text();
    }
    QTextBrowser *viewMessage = ui->textBrowserInfo;
    viewMessage->setText(whatPrinted);
    return selectedItems;
}

void MainWindow::on_pushButtonProcess_clicked()
{
    //передам processList();
    QTextEdit *textPathTo = ui->textEditPathOut;
    QString pathTo = textPathTo->toPlainText();
    QString warningFieldEmpty = "Вы не ввели адрес сохранения";
    if (pathTo == "" || pathTo == warningFieldEmpty) {
        textPathTo->setText(warningFieldEmpty);
        return;
    }
    controller.savePathTo(pathTo);
    textPathTo->setText("");
    controller.makeRequest(makeTxtList(findSelectedItems(*ui->listWidgetAlgo)), overlay);
}

QStringList MainWindow::makeTxtList(QList<QListWidgetItem*> list) {
    QStringList txtList;
    foreach(QListWidgetItem* line, list) {
        txtList << line->text();
    }
    return txtList;
}

void MainWindow::on_pushButtonPreview_clicked()
{
    //передам processList();
    QLabel *label = ui->labelImage;
    QStringList txtAlgo = makeTxtList(findSelectedItems(*ui->listWidgetAlgo));
    QImage image = controller.makeRequestPreview(txtAlgo);
    QPixmap p = QPixmap::fromImage(image);
    QPixmap p1(p.scaled ( 300,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    label->setPixmap(p1); // Здесь картинка включилась (надеюсь)
}


QList<QListWidgetItem *> MainWindow::findSelectedItems(QListWidget &list)
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

void MainWindow::on_pushButtonOverlay_clicked()
{
    overlay = !overlay;
    QAbstractButton *button = ui->pushButtonOverlay;
    if (overlay)
        button->setText("Overlay Mode On");
    else
        button->setText("Overlay Mode Off");
}

