#include "getintoinfo.h"
#include "ui_getintoinfo.h"
#include <QDebug>
#include "admin.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>

extern QString globaldata;
extern QString TollMoneyAll;
int money = 0; //定义全局变量 出车

getIntoInfo::getIntoInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getIntoInfo)
{
    ui->setupUi(this);
    setWindowTitle("详情");
    setFixedSize(this->width(),this->height());
    setWindowIcon(QIcon(":/img/favicon.ico"));

//    ui->automobileCarid->setText(globaldata);
    //qDebug() <<"2"<< globaldata;

    ui->lineHeader->setText("汽车详情");
    ui->lineHeader->setStyleSheet("QLabel{background-color:gray;font-size:16px;font-family:'微软雅黑';color:white;}");
    ui->lineHeader->setAlignment(Qt::AlignCenter);
    ui->automobileId->setEnabled(false);
    ui->automobileName->setEnabled(false);
    ui->automobileCarid->setEnabled(false);
    ui->automobilePhone->setEnabled(false);
    ui->automobileTime->setEnabled(false);
    ui->automobileSeat->setEnabled(false);
    ui->automobileMoney->setEnabled(false);
    QString styleColor = "QLineEdit{color:block;font-size:14px;font-family:'微软雅黑';}";
    ui->automobileId->setStyleSheet(styleColor);
    ui->automobileName->setStyleSheet(styleColor);
    ui->automobileCarid->setStyleSheet(styleColor);
    ui->automobilePhone->setStyleSheet(styleColor);
    ui->automobileTime->setStyleSheet(styleColor);
    ui->automobileSeat->setStyleSheet(styleColor);
    ui->automobileMoney->setStyleSheet(styleColor);
    QDateTime datas = QDateTime::currentDateTime();
    QString data = datas.toString("yyyy/MM/dd hh:mm:ss");
    QString sqlData = "";
    QString FindSql = QString("select * from parkinglot where seat = '%1'").arg(globaldata);
    QSqlQuery query;
    query.exec(FindSql);
    if(query.next())
    {
        ui->automobileId->setText(query.value(0).toString());
        ui->automobileName->setText(query.value(1).toString());
        ui->automobileCarid->setText(query.value(2).toString());
        ui->automobilePhone->setText(query.value(3).toString());
        ui->automobileTime->setText(query.value(4).toString());
        ui->automobileSeat->setText(query.value(5).toString());
        sqlData+=query.value(4).toString();
        QDateTime time1 = QDateTime::fromString(sqlData,"yyyy/MM/dd hh:mm:ss");
        QDateTime time2 = QDateTime::fromString(data,"yyyy/MM/dd hh:mm:ss");
        if(time1.secsTo(time2) / 60 > 60)
        {
            //qDebug() <<"已超过一小时";
            money = (time1.secsTo(time2) / 60 / 60) * 6;
            ui->automobileMoney->setText(QString::number(money));
        }
        else
        {
            //qDebug() <<"未超过一小时";
            ui->automobileMoney->setText("3");
        }
    }

}

getIntoInfo::~getIntoInfo()
{
    delete ui;
}

//出车
void getIntoInfo::on_pushButton_clicked()
{

    QString findSql = QString("select * from parkinglot where name = '%1'").arg(globaldata);  //查询数据
    QString name = "";
    QString carid = "";
    QString phone = "";
    QString random = "";
    QSqlQuery query;
    query.exec(findSql);
    if(query.next())
    {
        name = query.value(1).toString();
        carid = query.value(2).toString();
        phone = query.value(3).toString();
        random = query.value(6).toString();
    }
    else
    {
        return;
    }
    //插入
    QString insert = QString("insert into free_lane(name,carid,phone,random) values ('%1','%2','%3','%4')").
            arg(name).arg(carid).arg(phone).arg(random);
    QString del = QString("delete from parkinglot where random = '%1'").arg(random);
    if(query.exec(insert))
    {
        QMessageBox::information(NULL,"成功","出车成功");
        query.exec(del);
        int num = (TollMoneyAll.toInt()-money);
        TollMoneyAll = QString::number(num);
        this->hide();
        return;
    }
    else
    {
        QMessageBox::information(NULL,"失败","插入失败");
        return;
    }
}
