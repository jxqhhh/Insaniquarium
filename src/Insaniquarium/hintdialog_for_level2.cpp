#include "hintdialog_for_level2.h"
#include "ui_hintdialog_for_level2.h"

HintDialog_For_Level2::HintDialog_For_Level2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HintDialog_For_Level2 )
{
    ui->setupUi(this);
}

HintDialog_For_Level2::~HintDialog_For_Level2()
{
    delete ui;
}
