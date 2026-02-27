#ifndef CPUIDWINDOW_H
#define CPUIDWINDOW_H

#include <QMainWindow>

namespace Ui {
class cpuidwindow;
}

class cpuidwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit cpuidwindow(QWidget *parent = nullptr);
    ~cpuidwindow();

private:
    Ui::cpuidwindow *ui;
};

#endif // CPUIDWINDOW_H
