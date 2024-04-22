#include "follow_with.h"

FollowWith::FollowWith(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

FollowWith::~FollowWith()
{}

QWidget* FollowWith::GetWidget()
{
	scroll_area_ = new QScrollArea;
	QScrollBar* verticalScrollBar = scroll_area_->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	scroll_area_->setFrameShape(QFrame::NoFrame);
	scroll_area_->setWidgetResizable(true);  // 设置滚动区域自动调整大小

	QVBoxLayout* layout = new QVBoxLayout;
	ui.widget->setLayout(layout);

	ReadConfig();

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

QString FollowWith::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void FollowWith::InitUi(const QVector<QString>& _msg)
{
	Trends* trends = trend_service_->CreateNewTrend();
	trends->InitUi(_msg);

	ui.widget->layout()->addWidget(trends);
	//ui.widget->layout()->setContentsMargins(0, 0, 0, 0);
}

void FollowWith::ReadConfig()
{
	QString filePath = AppPath + ConfigFile;

	QFile qssFile(filePath);
	if (!qssFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QDomDocument doc;
	if (!doc.setContent(&qssFile))
	{
		qssFile.close();
		return;
	}

	qssFile.close();

	// 获取根元素
	QDomElement root = doc.documentElement();

	QDomNodeList node = root.elementsByTagName("Trend");
	for (int i = 0; i < node.count(); i++)
	{
		QVector<QString> msg;

		QDomElement temp = node.at(i).toElement();

		QString headPath = AppPath + temp.elementsByTagName("HeadPath").at(0).toElement().text();
		QString pngPath = AppPath + temp.elementsByTagName("PngPath").at(0).toElement().text();
		QString userName = temp.elementsByTagName("UserName").at(0).toElement().text();
		QString describe = temp.elementsByTagName("Describe").at(0).toElement().text();
		QString like = temp.elementsByTagName("Like").at(0).toElement().text();
		QString share = temp.elementsByTagName("Share").at(0).toElement().text();
		QString comment = temp.elementsByTagName("Comment").at(0).toElement().text();
		QString time = temp.elementsByTagName("Time").at(0).toElement().text();

		msg.push_back(headPath);
		msg.push_back(userName);
		msg.push_back(describe);
		msg.push_back(pngPath);
		msg.push_back(like);
		msg.push_back(share);
		msg.push_back(comment);
		msg.push_back(time);

		InitUi(msg);
	}

	// 创建弹簧
	QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

	// 添加弹簧到布局
	ui.widget->layout()->addItem(spacer);
}
