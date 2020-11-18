#ifndef ADMINUSER_H
#define ADMINUSER_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class adminUser;
}

class adminUser : public QWidget
{
    Q_OBJECT

public:
    explicit adminUser(QWidget *parent = 0);
    ~adminUser();

private slots:
    void on_searchFind_clicked();

    void on_SearchNameAll_clicked();

private:
    Ui::adminUser *ui;

    QSqlQueryModel *model;

    void style();
    void userAdmin();
};

#endif // ADMINUSER_H
