#include "SongLists.h"

SongLists::SongLists(QWidget *parent)
	: QWidget(parent)
	, group_btns_(new QButtonGroup)
	, checked_(false)
{
	ui.setupUi(this);

	InitUi();

	InitConnect();
}

SongLists::~SongLists()
{
	if (group_btns_)
	{
		delete group_btns_;
		group_btns_ = nullptr;
	}
}

QWidget* SongLists::GetWidget()
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

void SongLists::InitUi()
{
	QString qss = OpenQssFile(BtnQss);

	SettingQss(qss);

	group_btns_->addButton(ui.chinese_btn);
	group_btns_->addButton(ui.popular_btn);
	group_btns_->addButton(ui.rock_btn);
	group_btns_->addButton(ui.ballad_btn);
	group_btns_->addButton(ui.electron_btn);
	group_btns_->addButton(ui.alternative_btn);
	group_btns_->addButton(ui.light_music_btn);
	group_btns_->addButton(ui.variety_btn);
	group_btns_->addButton(ui.television_btn);
	group_btns_->addButton(ui.acg_btn);

	// 设置为单选按钮，意味着每次只能有一个按钮被选中
	group_btns_->setExclusive(true);

	ReadConfig(StdString2QString("全部歌单"));
}

void SongLists::InitConnect()
{
	connect(ui.main_control_btn, &QPushButton::clicked, this, &SongLists::SlotAllSongListsClicked);

	connect(group_btns_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &SongLists::SlotBtnGroupClicked);
}

QString SongLists::OpenQssFile(std::string _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void SongLists::SettingQss(QString _qss)
{
	ui.chinese_btn->setStyleSheet(_qss);
	ui.popular_btn->setStyleSheet(_qss);
	ui.rock_btn->setStyleSheet(_qss);
	ui.ballad_btn->setStyleSheet(_qss);
	ui.electron_btn->setStyleSheet(_qss);
	ui.alternative_btn->setStyleSheet(_qss);
	ui.light_music_btn->setStyleSheet(_qss);
	ui.variety_btn->setStyleSheet(_qss);
	ui.television_btn->setStyleSheet(_qss);
	ui.acg_btn->setStyleSheet(_qss);
}

void SongLists::ReadConfig(QString _btnText)
{
	QString filePath = AppPath + AllSongListsConfig;

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

	QDomElement nodeList = root.elementsByTagName(_btnText).at(0).toElement();

	QString titlePath = AppPath + nodeList.elementsByTagName("TitlePath").at(0).toElement().text();
	QPixmap pixmap(titlePath);

	ui.title_label->setPixmap(pixmap);

	QString titleColor = nodeList.elementsByTagName("TitleColor").at(0).toElement().text();
	ui.title_widget->setStyleSheet("border-radius: 10px;background-color: " + titleColor + ";");

	QString titleDescirbe1 = nodeList.elementsByTagName("TitleDescirbe1").at(0).toElement().text();
	ui.title_desc1->setText(titleDescirbe1);

	QString titleDescirbe2 = nodeList.elementsByTagName("TitleDescirbe2").at(0).toElement().text();
	ui.title_desc2->setText(titleDescirbe2);

	QDomNodeList pngLists = nodeList.elementsByTagName("Png");
	for (int i = 0; i < pngLists.count(); i++)
	{
		QDomElement node = pngLists.at(i).toElement();

		QString songPath = AppPath + node.elementsByTagName("SongPath").at(0).toElement().text();
		QString songDesc = node.elementsByTagName("SongDescribe").at(0).toElement().text();

		QPixmap pixmap(songPath);

		switch (i)
		{
		case 0:
			ui.song_label_1->setPixmap(pixmap);
			ui.desc_label_1->setText(songDesc);
			break;
		case 1:
			ui.song_label_2->setPixmap(pixmap);
			ui.desc_label_2->setText(songDesc);
			break;
		case 2:
			ui.song_label_3->setPixmap(pixmap);
			ui.desc_label_3->setText(songDesc);
			break;
		case 3:
			ui.song_label_4->setPixmap(pixmap);
			ui.desc_label_4->setText(songDesc);
			break;
		default:
			break;
		}
	}
}

void SongLists::SlotAllSongListsClicked()
{	
	if (!song_lists_classify_)
	{
		song_lists_classify_ = std::make_shared<SongListsClassify>(this);

		connect(song_lists_classify_.get(), &SongListsClassify::SignalClickedBtn, this, &SongLists::SlotClickedBtn);
	}

	if (!checked_)
	{
		song_lists_classify_->move(33, 310);
		song_lists_classify_->show();
	}
	else
		song_lists_classify_->hide();

	checked_ = !checked_;
}

void SongLists::SlotClickedBtn(QString _btnText)
{
	if (_btnText.compare(StdString2QString("全部歌单")) == 0)
	{
		ui.main_control_btn->setText(_btnText);

		song_lists_classify_->hide();
		checked_ = !checked_;

		group_btns_->setExclusive(false);

		for each (auto it in group_btns_->buttons())
			it->setChecked(false);
	}
	else
	{
		group_btns_->setExclusive(true);

		for each (auto it in group_btns_->buttons())
		{
			if (it->text() == _btnText)
			{
				ui.main_control_btn->setText(_btnText);
				it->setChecked(true);

				song_lists_classify_->hide();
				checked_ = !checked_;

				break;
			}
		}
	}

	ReadConfig(_btnText);
}

void SongLists::SlotBtnGroupClicked(QAbstractButton* _btn)
{
	QPushButton* clickedBtn = qobject_cast<QPushButton*>(_btn);

	ui.main_control_btn->setText(clickedBtn->text());

	ReadConfig(clickedBtn->text());
}
