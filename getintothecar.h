#ifndef GETINTOTHECAR_H
#define GETINTOTHECAR_H

#include <QWidget>

namespace Ui {
class GetIntoTheCar;
}

class GetIntoTheCar : public QWidget
{
    Q_OBJECT

public:
    explicit GetIntoTheCar(QWidget *parent = 0);
    ~GetIntoTheCar();

private slots:
    void on_btnInput_clicked();

private:
    Ui::GetIntoTheCar *ui;

    QString time();

    void style();
};

#endif // GETINTOTHECAR_H
