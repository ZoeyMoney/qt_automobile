#include "login.h"
#include "ui_login.h"
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "registered.h"
#include "admin.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setWindowTitle("登录");
    this->setFixedSize(this->width(),this->height());   //禁止窗口缩放

    ui->imgPortrait->setPixmap(QPixmap(":/img/header.jpg"));    //在label内添加图片
    ui->imgPortrait->setScaledContents(true);   //填充整个label大小
    ui->headerPortrait->setPixmap(QPixmap(":/img/header.jpg"));
    ui->headerPortrait->setScaledContents(true);

    ui->lineName->setPlaceholderText("请输入用户名");
    ui->linePwd->setEchoMode(QLineEdit::Password);
    ui->linePwd->setPlaceholderText("请输入密码");

    QString borderNone = "QPushButton{border:none;}QPushButton:hover{color:#4e6ef2;}";
    ui->lineName->setStyleSheet("QLineEdit{border-bottom: none;font-size:14px;font-family:'微软雅黑'}");
    ui->linePwd->setStyleSheet("QLineEdit{font-size:14px;font-family:'微软雅黑'}");
    ui->register_2->setStyleSheet(borderNone);
    ui->zh->setStyleSheet(borderNone);
    ui->register_2->setCursor(Qt::PointingHandCursor);
    ui->zh->setCursor(Qt::PointingHandCursor);
    ui->btnSbumit->setStyleSheet("QPushButton{border-radius:5px;border:1px solid #4e6ef2;background:#4e6ef2;color:white;font-weight:bold;font-family:'微软雅黑'}"
                                 "QPushButton:hover{background:#4662D9;}");
    ui->btnSbumit->setCursor(Qt::PointingHandCursor);
    ui->btnSbumit->setShortcut(Qt::Key_Enter);

    mysql();
}

Login::~Login()
{
    delete ui;
}

//数据库
void Login::mysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("antomobile");
    if(!db.open())
    {
        QMessageBox::information(NULL,"错误","数据库用户名或密码错误");
        return;
    }
}

//提交
void Login::on_btnSbumit_clicked()
{
    QString name = ui->lineName->text();
    QString pwd = ui->linePwd->text();
    if(name == "" || pwd == "")
    {
        QMessageBox::information(NULL,"错误","用户名或密码不能为空",QMessageBox::Yes);
    }
    else
    {
        QString MysqlFind = QString("select * from userpwd where name='%1' and pwd='%2'").arg(name).arg(pwd);
        QSqlQuery query;
        query.exec(MysqlFind);
        if(query.first())
        {
            QMessageBox::information(NULL,"成功","登录成功！",QMessageBox::Yes);
            Admin *admin = new Admin;
            admin->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(NULL,"失败","登录失败！");
        }
    }



}

//找回密码
void Login::on_zh_clicked()
{
    QMessageBox::information(NULL,"错误","暂未开发");
}

//注册密码
void Login::on_register_2_clicked()
{
    Registered *reg = new Registered;
    reg->show();
    this->hide();
}
