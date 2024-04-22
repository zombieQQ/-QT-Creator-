#include "Trends.h"

Trends::Trends(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Trends::~Trends()
{}

void Trends::InitUi(const QVector<QString> _msg)
{
	QPixmap pixmap(_msg[0]);
	ui.headLabel->setPixmap(pixmap);

	ui.userLabel->setText(_msg[1]);
	ui.desLabel->setText(_msg[2]);
	
	QPixmap pngPixmap(_msg[3]);
	ui.pngLabel->setPixmap(pngPixmap);

	ui.likeBtn->setText(_msg[4]);
	ui.shareBtn->setText(_msg[5]);
	ui.commentBtn->setText(_msg[6]);
	ui.timeLabel->setText(_msg[7]);
}
