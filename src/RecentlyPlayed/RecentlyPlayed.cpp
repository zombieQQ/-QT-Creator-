#include "RecentlyPlayed.h"

RecentlyPlayed::RecentlyPlayed(QWidget *parent)
	: QWidget(parent)
	, table_widget_(std::make_shared<SongsTableWidget>())
{
	ui.setupUi(this);

}

RecentlyPlayed::~RecentlyPlayed()
{}

QWidget* RecentlyPlayed::GetWidget()
{
	scroll_area_ = new QScrollArea;
	QScrollBar* verticalScrollBar = scroll_area_->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	QVBoxLayout* layout = new QVBoxLayout;
	ui.widget->setLayout(layout);
	layout->addWidget(table_widget_->GetWidget());
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

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

QString RecentlyPlayed::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}
