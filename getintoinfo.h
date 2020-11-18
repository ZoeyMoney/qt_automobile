#ifndef GETINTOINFO_H
#define GETINTOINFO_H

#include <QWidget>

namespace Ui {
class getIntoInfo;
}

class getIntoInfo : public QWidget
{
    Q_OBJECT

public:
    explicit getIntoInfo(QWidget *parent = 0);
    ~getIntoInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::getIntoInfo *ui;
};

#endif // GETINTOINFO_H
