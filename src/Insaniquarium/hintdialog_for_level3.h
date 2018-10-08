#ifndef HINTDIALOG_FOR_LEVEL3_H
#define HINTDIALOG_FOR_LEVEL3_H

#include <QDialog>

namespace Ui {
class HintDialog_For_Level3;
}

class HintDialog_For_Level3 : public QDialog
{
    Q_OBJECT

public:
    explicit HintDialog_For_Level3(QWidget *parent = 0);
    ~HintDialog_For_Level3();

private:
    Ui::HintDialog_For_Level3 *ui;
};

#endif // HINTDIALOG_FOR_LEVEL3_H
