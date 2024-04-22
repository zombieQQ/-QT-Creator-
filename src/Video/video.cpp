#include "video.h"

video::video(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitUi();

	InitConnect();
}

video::~video()
{}

QWidget* video::GetVideoWidget()
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

void video::InitUi()
{
	QString qss = OpenQssFile(BtnQss);

	SettingQss(qss);

	SetBtnGroup();

	ui.sceneBtn->setChecked(true);
	ui.inlandBtn->setChecked(true);

	pngLabels.push_back(ui.pngLabel);
	pngLabels.push_back(ui.pngLabel_2);
	pngLabels.push_back(ui.pngLabel_3);
	pngLabels.push_back(ui.pngLabel_4);
	pngLabels.push_back(ui.pngLabel_5);
	pngLabels.push_back(ui.pngLabel_6);

	desLabels.push_back(ui.desLabel);
	desLabels.push_back(ui.desLabel_2);
	desLabels.push_back(ui.desLabel_3);
	desLabels.push_back(ui.desLabel_4);
	desLabels.push_back(ui.desLabel_5);
	desLabels.push_back(ui.desLabel_6);

	authorLabels.push_back(ui.auLabel);
	authorLabels.push_back(ui.auLabel_2);
	authorLabels.push_back(ui.auLabel_3);
	authorLabels.push_back(ui.auLabel_4);
	authorLabels.push_back(ui.auLabel_5);
	authorLabels.push_back(ui.auLabel_6);

	ReadConfig(StdString2QString("现场"));
}

void video::InitConnect()
{
	connect(btns_group_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &video::SlotBtnGroupClicked);
}

void video::SettingQss(const QString& _qss)
{
	ui.sceneBtn->setStyleSheet(_qss);
	ui.coverBtn->setStyleSheet(_qss);
	ui.danceBtn->setStyleSheet(_qss);
	ui.bgmBtn->setStyleSheet(_qss);
	ui.mvBtn->setStyleSheet(_qss);
	ui.lifeBtn->setStyleSheet(_qss);
	ui.gameBtn->setStyleSheet(_qss);
	ui.acgBtn->setStyleSheet(_qss);
	ui.bestBtn->setStyleSheet(_qss);

	ui.inlandBtn->setStyleSheet(_qss);
	ui.hongKongBtn->setStyleSheet(_qss);
	ui.EuropeBtn->setStyleSheet(_qss);
	ui.JapanBtn->setStyleSheet(_qss);
	ui.KoreaBtn->setStyleSheet(_qss);
}

void video::SetBtnGroup()
{
	btns_group_->addButton(ui.sceneBtn);
	btns_group_->addButton(ui.coverBtn);
	btns_group_->addButton(ui.danceBtn);
	btns_group_->addButton(ui.bgmBtn);
	btns_group_->addButton(ui.mvBtn);
	btns_group_->addButton(ui.lifeBtn);
	btns_group_->addButton(ui.gameBtn);
	btns_group_->addButton(ui.acgBtn);
	btns_group_->addButton(ui.bestBtn);
	btns_group_->setExclusive(true);
}

void video::ReadConfig(const QString& _name)
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

	QDomElement nodeList = root.elementsByTagName(_name).at(0).toElement();

	QDomNodeList videoLists = nodeList.elementsByTagName(StdString2QString("视频"));
	for (int i = 0; i < videoLists.count(); i++)
	{
		QDomElement node = videoLists.at(i).toElement();

		QString videoPng = AppPath + node.elementsByTagName("PngPath").at(0).toElement().text();
		QString describe = node.elementsByTagName("Describe").at(0).toElement().text();
		QString author = node.elementsByTagName("Author").at(0).toElement().text();

		QPixmap pixmap(videoPng);
		pngLabels[i]->setPixmap(pixmap);

		desLabels[i]->setText(describe);
		authorLabels[i]->setText(author);
	}
}

QString video::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";
	
	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void video::SlotBtnGroupClicked(QAbstractButton* _btn)
{
	ui.allBtn->setText(_btn->text());

	ReadConfig(_btn->text());
}