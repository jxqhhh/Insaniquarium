#ifndef HINTDIALOG_FOR_LEVEL4_H
#define HINTDIALOG_FOR_LEVEL4_H

#include <QDialog>

namespace Ui {
class HintDialog_For_Level4;
}

class HintDialog_For_Level4 : public QDialog
{
    Q_OBJECT

public:
    explicit HintDialog_For_Level4(QWidget *parent = 0);
    ~HintDialog_For_Level4();

private:
    Ui::HintDialog_For_Level4 *ui;
};

#endif // HINTDIALOG_FOR_LEVEL4_H
