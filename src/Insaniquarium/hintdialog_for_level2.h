#ifndef HINTDIALOG_FOR_LEVEL2_H
#define HINTDIALOG_FOR_LEVEL2_H

#include <QDialog>

namespace Ui {
class HintDialog_For_Level2 ;
}

class HintDialog_For_Level2 : public QDialog
{
    Q_OBJECT

public:
    explicit HintDialog_For_Level2(QWidget *parent = 0);
    ~HintDialog_For_Level2();

private:
    Ui::HintDialog_For_Level2  *ui;
};

#endif // HINTDIALOG_FOR_LEVEL2_H
