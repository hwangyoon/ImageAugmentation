#ifndef UIMAIN_H
#define UIMAIN_H

#include <QDialog>

namespace Ui {
class UImain;
}

class UImain : public QDialog
{
    Q_OBJECT

public:
    explicit UImain(QWidget *parent = nullptr);
    ~UImain();

private:
    Ui::UImain *ui;
};

#endif // UIMAIN_H
