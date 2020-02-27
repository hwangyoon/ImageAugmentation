#include "uimain.h"
#include "ui_uimain.h"

UImain::UImain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UImain)
{
    ui->setupUi(this);
}

UImain::~UImain()
{
    delete ui;
}
