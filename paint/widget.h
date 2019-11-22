#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QScrollArea>

namespace Ui {
class Widget;
}

class QTimer;
class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = nullptr);

	bool eventFilter(QObject *watched, QEvent *event);
	void paint();


	~Widget();

private:
	Ui::Widget *ui;

	QScrollArea *pArea;
	QWidget * qw;

	QTimer *m_pTimer;
	int num;

public slots:
	void handleTimeout();

protected:
	void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
