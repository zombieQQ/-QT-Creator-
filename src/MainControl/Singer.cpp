#include "Singer.h"

Singer::Singer(QWidget *parent)
	: QWidget(parent)
	, languagesBtnGroup_(new QButtonGroup)
	, classifyBtnGroup_(new QButtonGroup)
	, popularBtnGroup_(new QButtonGroup)
	, userBtnGroup_(new QButtonGroup)
	, nameBtnGroup_(new QButtonGroup)
{
	ui.setupUi(this);

	InitUi();

	InitConnect();
}

Singer::~Singer()
{}

QWidget* Singer::GetWidget()
{
	scrollArea_ = new QScrollArea;
	QScrollBar* verticalScrollBar = scrollArea_->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	scrollArea_->setFrameShape(QFrame::NoFrame);
	scrollArea_->setWidgetResizable(true);  // 设置滚动区域自动调整大小

	// 创建一个内部的小部件，放置在滚动区域中
	QWidget* contentWidget = new QWidget(scrollArea_);
	QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);

	contentLayout->addWidget(this);

	// 设置滚动区域的小部件
	scrollArea_->setWidget(contentWidget);

	return scrollArea_;
}

QString Singer::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);	
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void Singer::SettingClassifyQss(const QString& _qss)
{
	for (const auto& it : languagesBtnGroup_->buttons())
		it->setStyleSheet(_qss);

	for (const auto& it : classifyBtnGroup_->buttons())
		it->setStyleSheet(_qss);

	for (const auto& it : popularBtnGroup_->buttons())
		it->setStyleSheet(_qss);
}

void Singer::SettingNameBtnQss(const QString& _qss)
{
	for (const auto& it : nameBtnGroup_->buttons())
		it->setStyleSheet(_qss);

	for (const auto& it : userBtnGroup_->buttons())
		it->setStyleSheet(_qss);
}

void Singer::InitUi()
{
	InitButtonGroup();

	// 设置歌手分类
	QString qss = OpenQssFile(BtnQss);

	SettingClassifyQss(qss);

	// 设置歌手名字按钮
	qss = OpenQssFile(SingerNameBtnQss);

	SettingNameBtnQss(qss);

	UpdateUi();
}

void Singer::InitConnect()
{
	connect(languagesBtnGroup_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &Singer::SlotLanguagesBtnGroupClicked);
	connect(classifyBtnGroup_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &Singer::SlotClassifyBtnGroupClicked);
	connect(popularBtnGroup_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &Singer::SlotPopularBtnGroupClicked);
}

void Singer::InitButtonGroup()
{
	languagesBtnGroup_->addButton(ui.languagesBtn);
	languagesBtnGroup_->addButton(ui.languagesBtn_2);
	languagesBtnGroup_->addButton(ui.languagesBtn_3);
	languagesBtnGroup_->addButton(ui.languagesBtn_4);
	languagesBtnGroup_->addButton(ui.languagesBtn_5);
	languagesBtnGroup_->addButton(ui.languagesBtn_6);
	languagesBtnGroup_->setExclusive(true);

	classifyBtnGroup_->addButton(ui.classifyBtn);
	classifyBtnGroup_->addButton(ui.classifyBtn_2);
	classifyBtnGroup_->addButton(ui.classifyBtn_3);
	classifyBtnGroup_->addButton(ui.classifyBtn_4);
	classifyBtnGroup_->setExclusive(true);

	popularBtnGroup_->addButton(ui.popularBtn);
	popularBtnGroup_->addButton(ui.popularBtn_2);
	popularBtnGroup_->addButton(ui.popularBtn_3);
	popularBtnGroup_->addButton(ui.popularBtn_4);
	popularBtnGroup_->addButton(ui.popularBtn_5);
	popularBtnGroup_->addButton(ui.popularBtn_6);
	popularBtnGroup_->addButton(ui.popularBtn_7);
	popularBtnGroup_->addButton(ui.popularBtn_8);
	popularBtnGroup_->addButton(ui.popularBtn_9);
	popularBtnGroup_->addButton(ui.popularBtn_10);
	popularBtnGroup_->addButton(ui.popularBtn_11);
	popularBtnGroup_->addButton(ui.popularBtn_12);
	popularBtnGroup_->addButton(ui.popularBtn_13);
	popularBtnGroup_->addButton(ui.popularBtn_14);
	popularBtnGroup_->addButton(ui.popularBtn_15);
	popularBtnGroup_->addButton(ui.popularBtn_16);
	popularBtnGroup_->addButton(ui.popularBtn_17);
	popularBtnGroup_->addButton(ui.popularBtn_18);
	popularBtnGroup_->addButton(ui.popularBtn_19);
	popularBtnGroup_->addButton(ui.popularBtn_20);
	popularBtnGroup_->addButton(ui.popularBtn_21);
	popularBtnGroup_->addButton(ui.popularBtn_22);
	popularBtnGroup_->addButton(ui.popularBtn_23);
	popularBtnGroup_->addButton(ui.popularBtn_24);
	popularBtnGroup_->addButton(ui.popularBtn_25);
	popularBtnGroup_->addButton(ui.popularBtn_26);
	popularBtnGroup_->addButton(ui.popularBtn_27);
	popularBtnGroup_->addButton(ui.popularBtn_28);
	popularBtnGroup_->setExclusive(true);

	userBtnGroup_->addButton(ui.userBtn, 0);
	userBtnGroup_->addButton(ui.userBtn_2, 1);
	userBtnGroup_->addButton(ui.userBtn_3, 2);
	userBtnGroup_->addButton(ui.userBtn_4, 3);
	userBtnGroup_->addButton(ui.userBtn_5, 4);
	userBtnGroup_->addButton(ui.userBtn_6, 5);
	userBtnGroup_->addButton(ui.userBtn_7, 6);
	userBtnGroup_->addButton(ui.userBtn_8, 7);
	userBtnGroup_->addButton(ui.userBtn_9, 8);
	userBtnGroup_->addButton(ui.userBtn_10, 9);
	userBtnGroup_->setExclusive(true);

	nameBtnGroup_->addButton(ui.nameBtn, 0);
	nameBtnGroup_->addButton(ui.nameBtn_2, 1);
	nameBtnGroup_->addButton(ui.nameBtn_3, 2);
	nameBtnGroup_->addButton(ui.nameBtn_4, 3);
	nameBtnGroup_->addButton(ui.nameBtn_5, 4);
	nameBtnGroup_->addButton(ui.nameBtn_6, 5);
	nameBtnGroup_->addButton(ui.nameBtn_7, 6);
	nameBtnGroup_->addButton(ui.nameBtn_8, 7);
	nameBtnGroup_->addButton(ui.nameBtn_9, 8);
	nameBtnGroup_->addButton(ui.nameBtn_10, 9);
	nameBtnGroup_->setExclusive(false);
}

void Singer::UpdateUi()
{
	QString filePath = AppPath + SingerConfig;

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

	QDomElement languageNode = root.elementsByTagName(languages_).at(0).toElement();
	QDomElement classifyNode = languageNode.elementsByTagName(classify_).at(0).toElement();
	QDomElement popularNode = classifyNode.elementsByTagName(popular_).at(0).toElement();

	QDomNodeList pngLists = popularNode.elementsByTagName("png");
	for (int i = 0; i < pngLists.count(); i++)
	{
		QDomElement node = pngLists.at(i).toElement();

		QString singerPath = AppPath + node.elementsByTagName("SingerPath").at(0).toElement().text();
		QString singerName = node.elementsByTagName("SingerName").at(0).toElement().text();

		QPixmap pixmap(singerPath);

		userBtnGroup_->button(i)->setIcon(QIcon(pixmap));
		nameBtnGroup_->button(i)->setText(singerName);
	}
}

void Singer::SlotClassifyBtnGroupClicked(QAbstractButton* _btn)
{
	QPushButton* clickedBtn = qobject_cast<QPushButton*>(_btn);
	classify_ = clickedBtn->text();

	UpdateUi();
}

void Singer::SlotPopularBtnGroupClicked(QAbstractButton* _btn)
{
	QPushButton* clickedBtn = qobject_cast<QPushButton*>(_btn);
	popular_ = clickedBtn->text();

	UpdateUi();
}

void Singer::SlotLanguagesBtnGroupClicked(QAbstractButton* _btn)
{
	QPushButton* clickedBtn = qobject_cast<QPushButton*>(_btn);
	languages_ = clickedBtn->text();

	UpdateUi();
}