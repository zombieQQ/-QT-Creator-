#include "SongListsClassify.h"

SongListsClassify::SongListsClassify(QWidget *parent)
	: QWidget(parent)
	, group_btns_(new QButtonGroup)
{
	ui.setupUi(this);

	InitUi();
}

SongListsClassify::~SongListsClassify()
{}

void SongListsClassify::InitUi()
{
	QString qss = OpenQssFile(BtnQss);

	SettingQss(qss);

	group_btns_->addButton(ui.main_control_btn);
	group_btns_->addButton(ui.chinese_btn);
	group_btns_->addButton(ui.pushButton_4);
	group_btns_->addButton(ui.pushButton_5);
	group_btns_->addButton(ui.pushButton_6);
	group_btns_->addButton(ui.pushButton_7);
	group_btns_->addButton(ui.pushButton_9);
	group_btns_->addButton(ui.pushButton_10);
	group_btns_->addButton(ui.pushButton_11);
	group_btns_->addButton(ui.pushButton_12);
	group_btns_->addButton(ui.pushButton_13);

	group_btns_->setExclusive(true);

	ui.pushButton_2->setEnabled(false);
	ui.pushButton_8->setEnabled(false);

	connect(group_btns_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &SongListsClassify::SlotBtnGroupClicked);
}

QString SongListsClassify::OpenQssFile(std::string _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void SongListsClassify::SettingQss(QString _qss)
{
	ui.main_control_btn->setStyleSheet(_qss);
	ui.chinese_btn->setStyleSheet(_qss);
	ui.pushButton_4->setStyleSheet(_qss);
	ui.pushButton_6->setStyleSheet(_qss);
	ui.pushButton_5->setStyleSheet(_qss);
	ui.pushButton_7->setStyleSheet(_qss);
	ui.pushButton_9->setStyleSheet(_qss);
	ui.pushButton_10->setStyleSheet(_qss);
	ui.pushButton_11->setStyleSheet(_qss);
	ui.pushButton_12->setStyleSheet(_qss);
	ui.pushButton_13->setStyleSheet(_qss);
}

void SongListsClassify::SlotBtnGroupClicked(QAbstractButton* _btn)
{
	QPushButton* clickedBtn = qobject_cast<QPushButton*>(_btn);

	emit SignalClickedBtn(clickedBtn->text());
}