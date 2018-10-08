#include "hintdialogforwin.h"
#include "ui_hintdialogforwin.h"

HintDialogForWin::HintDialogForWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HintDialogForWin)
{
    ui->setupUi(this);
}

HintDialogForWin::~HintDialogForWin()
{
    delete ui;
}
