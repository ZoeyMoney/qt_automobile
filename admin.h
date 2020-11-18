#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();

private slots:
    void on_pushButton_clicked();

    void on_btnFindAll_clicked();

    void on_btnCar_clicked();

    void on_pushButton_4_clicked();

    void on_parkingLot_doubleClicked(const QModelIndex &index);

    void MoneyAll();


    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Admin *ui;
    int getIntos = 0;
    QSqlQuery query;

    void style();
    void parkinglot_Data(); //停车场数据
    void free_lane_Data();  //便道数据
   // void find_parkinglot_data(const QString phone); //查询停车场数据
  //  void find_free_lane_data(const QString phone); //查询便道数据
    void tabclick(const QModelIndex &index);


};

#endif // ADMIN_H
