#include "getintothecar.h"
#include "ui_getintothecar.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QSqlQuery>
#include <QDateTime>
#include <QTime>

GetIntoTheCar::GetIntoTheCar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetIntoTheCar)
{
    ui->setupUi(this);

    style();
    setWindowIcon(QIcon(":/img/favicon.ico"));


}

GetIntoTheCar::~GetIntoTheCar()
{
    delete ui;
}

QString GetIntoTheCar::time()
{
    QDateTime datas = QDateTime::currentDateTime();
    QString data = datas.toString("yyyy/MM/dd hh:mm:ss");
    return data;
}

void GetIntoTheCar::style()
{
    setWindowTitle("进车录入");
    setFixedSize(this->width(),this->height());
    ui->labelHeader->setStyleSheet("QLabel{background-color:gray;font-size:16px;font-family:'微软雅黑';color:white;}");
    ui->labelHeader->setAlignment(Qt::AlignCenter);
}

//提交
void GetIntoTheCar::on_btnInput_clicked()
{
    QString name = ui->lineName->text();
    QString caiId = ui->lineCarId->text();
    QString phone = ui->linePhone->text();
    QString carNumber = ui->lineCarNumber->text();
    QString times = time();
//    QTime time;
//    time = QTime::currentTime();
//    qsrand(time.msec()+time.second()*1000);
    QString random = "";
    for(int i = 0;i < 4;i++)
    {
        int ran = qrand() % 10;
        random+=QString("%1").arg(ran,1,10);
    }
    QString insert = QString("insert into parkinglot(name,carid,phone,time,seat,random) values ('%1','%2','%3','%4','%5','%6')").
            arg(name).arg(caiId).arg(phone).arg(times).arg(carNumber).arg(random);
    QSqlQuery query;


//    qDebug() << name + ","+caiId+","+phone+","+times+","+carNumber;
//    qDebug() << insert;

    if(name != "" || caiId != "" || phone != ""
            || carNumber != "")
    {
        if(query.exec(insert))
        {
            QMessageBox::information(NULL,"成功","录入成功");
            this->hide();
        }
    }
    else
    {
        QMessageBox::information(NULL,"错误","输入框里不能有空");
        return;
    }

}
