#include "LocalAndDownload.h"

LocalAndDownload::LocalAndDownload(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

LocalAndDownload::~LocalAndDownload()
{}

QWidget* LocalAndDownload::GetWidget()
{
	scroll_area_ = new QScrollArea;
	QScrollBar* verticalScrollBar = scroll_area_->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	scroll_area_->setFrameShape(QFrame::NoFrame);
	scroll_area_->setWidgetResizable(true);  // ���ù��������Զ�������С

	// ����һ���ڲ���С�����������ڹ���������
	QWidget* contentWidget = new QWidget(scroll_area_);
	QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);

	contentLayout->addWidget(this);

	// ���ù��������С����
	scroll_area_->setWidget(contentWidget);

	return scroll_area_;
}

QString LocalAndDownload::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}