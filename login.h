#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_btnSbumit_clicked();

    void on_zh_clicked();

    void on_register_2_clicked();

private:
    Ui::Login *ui;

    void mysql();
};

#endif // LOGIN_H
