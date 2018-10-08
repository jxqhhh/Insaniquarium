#include "hintdialog_for_level3.h"
#include "ui_hintdialog_for_level3.h"

HintDialog_For_Level3::HintDialog_For_Level3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HintDialog_For_Level3)
{
    ui->setupUi(this);
}

HintDialog_For_Level3::~HintDialog_For_Level3()
{
    delete ui;
}
