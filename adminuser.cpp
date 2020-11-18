#include "adminuser.h"
#include "ui_adminuser.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlTableModel>


adminUser::adminUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminUser)
{
    ui->setupUi(this);

    setWindowTitle("用户管理");
    setFixedSize(this->width(),this->height());
    setWindowIcon(QIcon(":/img/favicon.ico"));

    style();
    userAdmin();
}

adminUser::~adminUser()
{
    delete ui;
}

//样式
void adminUser::style()
{
    ui->searchName->setStyleSheet("QLineEdit{border-radius:5px;border:1px solid #707ba2;padding-left:10px;font-weight:bold;font-family:'微软雅黑'}");
    ui->searchName->setPlaceholderText("请输入要查询的用户名");
    ui->tableView->verticalHeader()->setHidden(true);
}
//数据
void adminUser::userAdmin()
{
    QString findUser = "select id,name,pwd from userpwd";
    model = new QSqlQueryModel(ui->tableView);
    model->setQuery(findUser);
    model->setHeaderData(0,Qt::Horizontal,"用户编号");
    model->setHeaderData(1,Qt::Horizontal,"用户名");
    model->setHeaderData(2,Qt::Horizontal,"密码");
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void adminUser::on_searchFind_clicked()
{
    QString name = ui->searchName->text();
    if(name == "")
    {
        QMessageBox::information(NULL,"错误","搜索框不能为空");
    }
    else
    {
        QString findSql = QString("select name from userpwd where name = '%1'").arg(name);
        model = new QSqlQueryModel(ui->tableView);
        model->setQuery(findSql);
        ui->tableView->setModel(model);
        if(model->rowCount() > 0)
        {
             QString findUser = QString("select id,name,pwd from userpwd where name = '%1'").arg(name);
             model->setQuery(findUser);
             model->setHeaderData(0,Qt::Horizontal,"用户编号");
             model->setHeaderData(1,Qt::Horizontal,"用户名");
             model->setHeaderData(2,Qt::Horizontal,"密码");
             ui->tableView->setModel(model);
        }
        else
        {
            model->setHeaderData(0,Qt::Horizontal,"无");
            QMessageBox::information(NULL,"错误","未查到有此数据");

        }
    }
}
//查询全部
void adminUser::on_SearchNameAll_clicked()
{
        userAdmin();
}
