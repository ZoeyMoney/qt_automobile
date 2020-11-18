#include "admin.h"
#include "ui_admin.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include "getintothecar.h"
#include <QTimer>
#include <QStandardItemModel>
#include "getintoinfo.h"
#include <QTableWidgetItem>
#include <QAbstractItemModel>
#include <QDateTime>
#include <QSqlQuery>
#include "adminuser.h"
#include "login.h"

QString globaldata;//全局变量用于窗体传值 根据random随机生成的4位数进行查询
QString TollMoneyAll;   //金额

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    setWindowTitle("当前车辆状态");
    setFixedSize(this->width(),this->height());
    setWindowIcon(QIcon(":/img/favicon.ico"));

    //样式
    style();
    parkinglot_Data();
    free_lane_Data();


    //每隔一秒刷新一次数据
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MoneyAll()));
    timer->start(1000);
}

Admin::~Admin()
{
    delete ui;
}

//样式
void Admin::style()
{
    QString styleBlack = "QLineEdit{color:black;font-family:'微软雅黑'}";
    ui->parkingLotVehicle->setText("0");
    ui->parkingLotVehicle->setStyleSheet(styleBlack);
    ui->parkingLotVehicle->setEnabled(false);
    ui->sidewalkVehicle->setText("0");
    ui->sidewalkVehicle->setStyleSheet(styleBlack);
    ui->sidewalkVehicle->setEnabled(false);
    ui->unknownVehicle->setText("0");
    ui->unknownVehicle->setStyleSheet(styleBlack);
    ui->unknownVehicle->setEnabled(false);
    ui->tollMoneyAll->setEnabled(false);
    ui->tollMoneyAll->setStyleSheet(styleBlack);
    ui->inquirePhone->setPlaceholderText("请输入要查询的手机号");
    ui->inquirePhone->setStyleSheet("QLineEdit{border-radius:5px;border:1px solid #707ba2;padding-left:10px;font-weight:bold;font-family:'微软雅黑'}");
}

//每隔一秒刷新金额
void Admin::MoneyAll()
{
    ui->tollMoneyAll->setText(TollMoneyAll);
}

//停车位数据
void Admin::parkinglot_Data()
{
   // QSqlTableModel *models = new QSqlTableModel(ui->parkingLot);
//    models->setTable("parkinglot");
//    ui->parkingLot->setModel(models);
//    models->select();
    QSqlQueryModel *models = new QSqlQueryModel(ui->parkingLot);
    QString sqlstr = "select id,name,carid,phone,time,seat from parkinglot";
    models->setQuery(sqlstr);
    models->setHeaderData(0,Qt::Horizontal,"车位编号");
    models->setHeaderData(1,Qt::Horizontal,"姓名");
    models->setHeaderData(2,Qt::Horizontal,"carid");
    models->setHeaderData(3,Qt::Horizontal,"手机号");
    models->setHeaderData(4,Qt::Horizontal,"时间");
    models->setHeaderData(5,Qt::Horizontal,"车牌号");
    //models->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->parkingLot->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->parkingLot->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->parkingLot->setSelectionBehavior(QAbstractItemView::SelectRows);
    //qDebug()<<model->rowCount();
    ui->parkingLot->setModel(models);
    QString len = QString::number(models->rowCount()); //查询表中数据多少条
    getIntos = len.toInt();
    ui->parkingLotVehicle->setText(len);
    ui->parkingLot->verticalHeader()->setHidden(true);

    QString findSql = QString("select * from parkinglot");
    //当前时间
    QDateTime datas = QDateTime::currentDateTime();
    QString data = datas.toString("yyyy/MM/dd hh:mm:ss");
    //获取到的时间
    QString dateSql = "";
    query.exec(findSql);
    int money = 0;
    while(query.next())
    {
        dateSql = query.value(4).toString();
       // qDebug() << dateSql;
        QDateTime time1 = QDateTime::fromString(dateSql,"yyyy/MM/dd hh:mm:ss");
        QDateTime time2 = QDateTime::fromString(data,"yyyy/MM/dd hh:mm:ss");
        if(time1.secsTo(time2) / 60 > 60)
        {
            money += (time1.secsTo(time2) / 60 / 60) * 6;
        }
        else
        {
            money +=3;
        }
    }
    //赋值全局金额
    TollMoneyAll = QString::number(money);
    //实时更新金额
    ui->tollMoneyAll->setText(TollMoneyAll);
}
//便车道数据
void Admin::free_lane_Data()
{
   // QSqlTableModel *tabs = new QSqlTableModel(ui->sidewalk);
    //tabs->setTable("free_lane");
   // ui->sidewalk->setModel(tabs);
   // tabs->select();
    QSqlQueryModel *tabs = new QSqlQueryModel(ui->sidewalk);
    QString sqlfind = "select id,name,carid,phone from free_lane";
    tabs->setQuery(sqlfind);
    tabs->setHeaderData(0,Qt::Horizontal,"车位编号");
    tabs->setHeaderData(1,Qt::Horizontal,"姓名");
    tabs->setHeaderData(3,Qt::Horizontal,"手机号");
    ui->sidewalk->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止编辑
    ui->sidewalk->setSelectionBehavior(QAbstractItemView::SelectRows);  //行内选中
    ui->sidewalk->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sidewalk->setModel(tabs);
    QString len = QString::number(tabs->rowCount());
    ui->sidewalkVehicle->setText(len);
    ui->sidewalk->verticalHeader()->setHidden(true);    //去掉tableView左侧id
}

//查询
void Admin::on_pushButton_clicked()
{
    QString phone = ui->inquirePhone->text();
    if(phone == "")
    {
        QMessageBox::information(NULL,"错误","手机号不能为空");
    }
    else
    {
        QSqlTableModel *tabs = new QSqlTableModel(ui->sidewalk);
        tabs->setFilter(QString("phone = '%1'").arg(phone));
        tabs->select();
        QSqlTableModel *tabls = new QSqlTableModel(ui->parkingLot);
        tabls->setTable("parkinglot");
        tabls->setFilter(QString("phone = '%1'").arg(phone));
        ui->parkingLot->setModel(tabls);
        tabls->select();
    }
}
//查询全部数据
void Admin::on_btnFindAll_clicked()
{
    //便道所有数据
    QSqlTableModel *tabs = new QSqlTableModel(ui->sidewalk);
    tabs->setTable("free_lane");
    ui->sidewalk->setModel(tabs);
    tabs->select();

    //停车位所有数据
    QSqlTableModel *tabls = new QSqlTableModel(ui->parkingLot);
    tabls->setTable("parkinglot");
    ui->parkingLot->setModel(tabls);
    tabls->select();
}
//进车
void Admin::on_btnCar_clicked()
{
    GetIntoTheCar *getCar = new GetIntoTheCar;
    getCar->setWindowModality(Qt::ApplicationModal);
    getCar->show();
}
//刷新数据
void Admin::on_pushButton_4_clicked()
{
        QString parkinglot_findSql = QString("select id,name,carid,phone,time,seat from parkinglot");
        QSqlQueryModel *model;
        model = new QSqlQueryModel(ui->parkingLot);
        model->setQuery(parkinglot_findSql);
        model->setHeaderData(0,Qt::Horizontal,"车位编号");
        model->setHeaderData(1,Qt::Horizontal,"姓名");
        model->setHeaderData(2,Qt::Horizontal,"carid");
        model->setHeaderData(3,Qt::Horizontal,"手机号");
        model->setHeaderData(4,Qt::Horizontal,"时间");
        model->setHeaderData(5,Qt::Horizontal,"车牌号");
        ui->parkingLot->setModel(model);

        QString sidewalkFind = QString("select id,name,carid,phone from free_lane");
        model = new QSqlQueryModel(ui->sidewalk);
        model->setQuery(sidewalkFind);
        model->setHeaderData(0,Qt::Horizontal,"车位编号");
        model->setHeaderData(1,Qt::Horizontal,"姓名");
        model->setHeaderData(3,Qt::Horizontal,"手机号");
        ui->sidewalk->setModel(model);
}

//双击触发
void Admin::on_parkingLot_doubleClicked(const QModelIndex &index)
{
    //获取行内的random
    QAbstractItemModel *Imodel=ui->parkingLot->model();
    QModelIndex Iindex = Imodel->index(index.row(),5);
    QVariant datatemp=Imodel->data(Iindex);
    QString name=datatemp.toString();
    globaldata = name;

    getIntoInfo *getInto = new getIntoInfo;
    getInto->setWindowModality(Qt::ApplicationModal);
    getInto->show();

//    QAbstractItemModel *m = (QAbstractItemModel*)index.model();
//    for(int columnIndex = 0;columnIndex<m->columnCount();columnIndex++)
//    {
//        QModelIndex x = m->index(index.row(),columnIndex);
//        QString s = x.data().toString();
//        qDebug() << s;
//        globaldata = s;
//    }
    //QString str = index.data().toString();    //点击什么获取什么内容
}
//用户查询
void Admin::on_pushButton_6_clicked()
{
    adminUser *user = new adminUser;
    user->setWindowModality(Qt::ApplicationModal);
    user->show();
}
//退出
void Admin::on_pushButton_7_clicked()
{
    this->hide();
    Login *login = new Login;
    login->show();
}
