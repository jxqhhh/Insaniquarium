#ifndef HINTDIALOGFORWIN_H
#define HINTDIALOGFORWIN_H

#include <QDialog>

namespace Ui {
class HintDialogForWin;
}

class HintDialogForWin : public QDialog
{
    Q_OBJECT

public:
    explicit HintDialogForWin(QWidget *parent = 0);
    ~HintDialogForWin();

private:
    Ui::HintDialogForWin *ui;
};

#endif // HINTDIALOGFORWIN_H
