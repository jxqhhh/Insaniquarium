#ifndef GAMEFAILEDDIALOG_H
#define GAMEFAILEDDIALOG_H

#include <QDialog>

namespace Ui {
class GameFailedDialog;
}

class GameFailedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameFailedDialog(QWidget *parent = 0);
    ~GameFailedDialog();

private:
    Ui::GameFailedDialog *ui;
};

#endif // GAMEFAILEDDIALOG_H
