#include "hintdialog_for_level4.h"
#include "ui_hintdialog_for_level4.h"

HintDialog_For_Level4::HintDialog_For_Level4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HintDialog_For_Level4)
{
    ui->setupUi(this);
}

HintDialog_For_Level4::~HintDialog_For_Level4()
{
    delete ui;
}
