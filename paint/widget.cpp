#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QScrollArea>
#include <QDebug>
#include <QTimer>

#define TIMER_TIMEOUT   (5*1000)

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);


	//设置窗口固定大小
	this->setMinimumSize(1000, 1000);
	this->setMaximumSize(1000, 1000);

	pArea = new QScrollArea(this); //在主窗口放一个自动滚动区pArea
	qw = new QWidget(pArea); //在自动滚动区中放一个窗口qw
	pArea->setWidget(qw); //设置滚动窗口qw
	pArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	pArea->setGeometry(200,130,500,500);
	qw->setGeometry(0,0,500,500);

	//qw->scrollAreaWidgetContents->setLayout(myformLayout);

	//ui->label->installEventFilter(this);
	this->qw->installEventFilter(this);


	m_pTimer = new QTimer(this);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
	m_pTimer->start(TIMER_TIMEOUT);

	num = 0;
}

Widget::~Widget()
{
	delete ui;
}


void Widget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::blue,4));//设置画笔形式
	painter.drawLine(20,20,220,220);//画直线
//	painter.drawLine(20,220,220,20);
//	painter.drawEllipse(20,20,200,200);//画圆
//	painter.drawRect(20,20,200,200);//画矩形
}

//bool Widget::eventFilter(QObject *watched, QEvent *event)   //用过滤器eventFilter（）拦截QLabel中的QEvent::Paint事件
//{
//	if(watched ==ui->label && event->type() == QEvent::Paint)
//		paint();

//	return QWidget::eventFilter(watched,event);
//}

//void Widget::paint()     //绘图
//{
//	QPainter painter(ui->label);
//	painter.setPen(Qt::blue);
//   // painter.drawLine(100,100,200,200);
//	painter.drawEllipse(30,15,50,65);
//	painter.drawLine(0,100,111,100);

//}


bool Widget::eventFilter(QObject *watched, QEvent *event)   //用过滤器eventFilter（）拦截QLabel中的QEvent::Paint事件
{
	if(watched ==this->qw && event->type() == QEvent::Paint)
		paint();

	return QWidget::eventFilter(watched,event);
}
void Widget::paint()     //绘图
{
	QPainter painter(this->qw);
	painter.setPen(QPen(Qt::red,2));//设置画笔形式
//	painter.drawLine(20,20,220,220);//画直线
//	painter.drawLine(20,220,220,20);
//	painter.drawEllipse(20,20,200,200);//画圆
//	painter.drawRect(20,20,200,200);//画矩形
	painter.drawLine(20+num,20+num,20+num, 40+num);
	qDebug() << "paint" << 20+num  << 20+num << 20+num << 40+num << endl;
}

void Widget::handleTimeout()
{
	num += 10;
	qDebug()<<"Enter timeout processing function" << num << endl;
	qw->update();
}

