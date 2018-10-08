#ifndef HINTWINDOW_H
#define HINTWINDOW_H

#include <QDialog>

namespace Ui {
class HintWindow;
}

class HintWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HintWindow(QWidget *parent = 0);
    ~HintWindow();

private:
    Ui::HintWindow *ui;
};

#endif // HINTWINDOW_H
