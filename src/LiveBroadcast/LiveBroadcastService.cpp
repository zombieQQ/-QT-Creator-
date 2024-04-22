#include "LiveBroadcastService.h"

LiveBroadcastService::LiveBroadcastService(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitUi();

	InitConnect();
}

LiveBroadcastService::~LiveBroadcastService()
{}

QWidget* LiveBroadcastService::GetLiveWidget()
{
	scroll_area_ = new QScrollArea;
	QScrollBar* verticalScrollBar = scroll_area_->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	scroll_area_->setFrameShape(QFrame::NoFrame);
	scroll_area_->setWidgetResizable(true);  // 设置滚动区域自动调整大小

	// 创建一个内部的小部件，放置在滚动区域中
	QWidget* contentWidget = new QWidget(scroll_area_);
	QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);

	contentLayout->addWidget(this);

	// 设置滚动区域的小部件
	scroll_area_->setWidget(contentWidget);

	return scroll_area_;
}

QString LiveBroadcastService::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void LiveBroadcastService::InitUi()
{
	SetBtnGroup();
}

void LiveBroadcastService::InitConnect()
{
	connect(btnsGroup_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), [=](QAbstractButton* _btn) {
		QDesktopServices::openUrl(QUrl("https://look.163.com/"));
	});
}

void LiveBroadcastService::SetBtnGroup()
{
	btnsGroup_->addButton(ui.pushButton);
	btnsGroup_->addButton(ui.pushButton_2);
	btnsGroup_->addButton(ui.pushButton_3);
	btnsGroup_->addButton(ui.pushButton_4);
	btnsGroup_->addButton(ui.pushButton_5);
	btnsGroup_->addButton(ui.pushButton_6);
	btnsGroup_->addButton(ui.pushButton_7);
	btnsGroup_->addButton(ui.pushButton_8);
	btnsGroup_->addButton(ui.pushButton_9);
	btnsGroup_->setExclusive(true);
}
