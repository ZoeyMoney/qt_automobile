#ifndef REGISTERED_H
#define REGISTERED_H

#include <QWidget>

namespace Ui {
class Registered;
}

class Registered : public QWidget
{
    Q_OBJECT

public:
    explicit Registered(QWidget *parent = 0);
    ~Registered();

private slots:
    void on_pushButton_2_clicked();

    void on_btnSubmit_clicked();

private:
    Ui::Registered *ui;

    QString random();   //随机生成
    void style();   //样式
};

#endif // REGISTERED_H
