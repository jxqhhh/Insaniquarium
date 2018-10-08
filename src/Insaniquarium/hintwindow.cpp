#include "hintwindow.h"
#include "ui_hintwindow.h"

HintWindow::HintWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HintWindow)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap pixmap(":/image/image/level2_hint.png");
    this->raise();
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);
}

HintWindow::~HintWindow()
{
    delete ui;
}
