#include "registered.h"
#include "ui_registered.h"
#include "login.h"
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <QSqlQuery>

Registered::Registered(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registered)
{
    ui->setupUi(this);

    //标题
    setWindowTitle("注册");
    //禁止缩放
    setFixedSize(this->width(),this->height());
    //随机数渲染
    ui->lineCode->setText(random());
    style();
    setWindowIcon(QIcon(":/img/favicon.ico"));
}

//随机数
QString Registered::random()
{
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    QString codes = "";
    for(int i = 0;i <4;i++)
    {
        int rando = qrand() %10;
        codes += QString("%1").arg(rando,1,10);
    }
    return codes;
}

//样式
void Registered::style()
{
    ui->lineName->setPlaceholderText("请输入用户名");
    ui->linePwd->setPlaceholderText("请输入密码");
    ui->confirmPwd->setPlaceholderText("确认密码");
    ui->code->setPlaceholderText("请输入验证码");
    ui->linePwd->setEchoMode(QLineEdit::Password);
    ui->confirmPwd->setEchoMode(QLineEdit::Password);
    QString style = "QLineEdit{font-size:14px;font-weight:bold;font-family:'微软雅黑'}";
    ui->lineName->setStyleSheet(style);
    ui->linePwd->setStyleSheet(style);
    ui->confirmPwd->setStyleSheet(style);
    ui->code->setStyleSheet(style);
    ui->lineCode->setStyleSheet(style);
    ui->btnSubmit->setShortcut(Qt::Key_Enter);

    //禁止编辑
    ui->lineCode->setEnabled(false);   //禁止编辑
    //将随机数边框背景调透明
    ui->lineCode->setStyleSheet("QLineEdit{border:none;background-color:transparent;color:black;font-size:14px;font-weight:bold;font-family:'微软雅黑A'}");
}

Registered::~Registered()
{
    delete ui;
}
//返回登录页面
void Registered::on_pushButton_2_clicked()
{
    this->hide();
    Login *log = new Login();
    log->show();
}
//注册用户后 将返回登录页面
void Registered::on_btnSubmit_clicked()
{
    QString name = ui->lineName->text();    //获取用户名
    QString pwd = ui->linePwd->text();      //获取密码
    QString confirmPwd = ui->confirmPwd->text();    //获取确认密码
    QString code = ui->code->text();    //获取验证码
    QString add = QString("insert into userpwd(name,pwd) values ('%1','%2')").arg(name).arg(pwd); //数据库插入
    QString find = QString("select * from userpwd where name = '%1'").arg(name);//数据库查询用户名
    QSqlQuery query;
    if(name == "")
    {
        QMessageBox::information(NULL,"错误","用户名不能为空");
        return;
    }
    else if(pwd == "")
    {
        QMessageBox::information(NULL,"错误","密码不能为空");
        return;
    }
    else if(confirmPwd == "")
    {
        QMessageBox::information(NULL,"错误","确认密码不能为空");
        return;
    }
    else if(code == "")
    {
        QMessageBox::information(NULL,"错误","验证码不能为空");
        return;
    }
    if(pwd != confirmPwd)
    {
        QMessageBox::information(NULL,"错误","密码与确认密码不一致");
        return;
    }
    if(ui->lineCode->text() != code)
    {
        QMessageBox::information(NULL,"错误","验证码错误");
        ui->lineCode->setText(random());
        return;
    }

    query.exec(find);
    if(query.first())
    {
        QMessageBox::information(NULL,"错误","用户名已存在");
        return;
    }
    else
    {
        if(query.exec(add))
        {
            QMessageBox::information(NULL,"成功","注册成功");
            this->hide();
            Login *log = new Login;
            log->show();
        }
        else
        {
            QMessageBox::information(NULL,"错误","数据出错");
        }
    }
}
