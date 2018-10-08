#include "gamefaileddialog.h"
#include "ui_gamefaileddialog.h"

GameFailedDialog::GameFailedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameFailedDialog)
{
    ui->setupUi(this);
}

GameFailedDialog::~GameFailedDialog()
{
    delete ui;
}
