#include <QApplication>
#include <QTextEdit>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTextEdit textEdit;
    QPushButton quitButton("Quit");

    QObject::connect(&quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout layout;
    layout.addWidget(&textEdit);
    layout.addWidget(&quitButton);

    QWidget window;
    window.setLayout(&layout);
    window.setWindowTitle("Hello world!");

    window.show();

    return app.exec();
}
