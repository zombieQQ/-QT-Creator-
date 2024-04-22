#include "BestNewMusic.h"

BestNewMusic::BestNewMusic(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitUi();

	InitConnect();
}

BestNewMusic::~BestNewMusic()
{}

QWidget* BestNewMusic::GetWidget()
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

QString BestNewMusic::OpenQssFile(const std::string& _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}

void BestNewMusic::SetBtnGroup()
{
	navigation_btns_->addButton(ui.newSongBtn);
	navigation_btns_->addButton(ui.newDVDBtn);
	navigation_btns_->setExclusive(true);

	new_song_btns_->addButton(ui.newSongBtn1);
	new_song_btns_->addButton(ui.newSongBtn2);
	new_song_btns_->addButton(ui.newSongBtn3);
	new_song_btns_->addButton(ui.newSongBtn4);
	new_song_btns_->addButton(ui.newSongBtn5);
	new_song_btns_->addButton(ui.newSongBtn6);
	new_song_btns_->setExclusive(true);

	new_dvd_btns_->addButton(ui.dvdBtn1);
	new_dvd_btns_->addButton(ui.dvdBtn2);
	new_dvd_btns_->addButton(ui.dvdBtn3);
	new_dvd_btns_->addButton(ui.dvdBtn4);
	new_dvd_btns_->addButton(ui.dvdBtn5);
	new_dvd_btns_->setExclusive(true);

	classify_btns_->addButton(ui.recommBtn);
	classify_btns_->addButton(ui.dvdAllBtn);
	classify_btns_->setExclusive(true);
}

void BestNewMusic::SetNavigationBtnQss()
{
	QString qss = OpenQssFile(NavigationBtnQss);

	ui.newSongBtn->setStyleSheet(qss);
	ui.newDVDBtn->setStyleSheet(qss);
}

void BestNewMusic::SetNewSongDVDBtnsQss()
{
	QString qss = OpenQssFile(NewSongBtnsQss);

	for (auto btn : new_song_btns_->buttons())
		btn->setStyleSheet(qss);

	for (auto btn : new_dvd_btns_->buttons())
		btn->setStyleSheet(qss);
}

void BestNewMusic::SetClassifyBtnsQss()
{
	QString qss = OpenQssFile(ClassifyBtnQss);

	for (auto btn : classify_btns_->buttons())
		btn->setStyleSheet(qss);
}

void BestNewMusic::InitUi()
{
	SetBtnGroup();

	SetNavigationBtnQss();

	SetNewSongDVDBtnsQss();

	SetClassifyBtnsQss();

	ui.newSongBtn->setChecked(true);
	ui.newSongBtn1->setChecked(true);

	ui.dvdBtn1->setChecked(true);
	ui.recommBtn->setChecked(true);

	ui.stackedWidget->setCurrentIndex(0);

	QVBoxLayout* layout = new QVBoxLayout(ui.songListsWidget);
	layout->addWidget(table_widget_.get());
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

	ReadConfig(StdString2QString("全部"));
}

void BestNewMusic::InitConnect()
{
	connect(new_song_btns_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &BestNewMusic::SlotNewSongBtnGroupClicked);
	
	connect(navigation_btns_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &BestNewMusic::SlotNavBtnGroupClicked);

	connect(classify_btns_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &BestNewMusic::SlotClassifyBtnGroupClicked);
}

void BestNewMusic::ReadConfig(const QString& _songClassify)
{
	QString filePath = AppPath + SongListonfig;

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

	QDomElement node = doc.elementsByTagName(_songClassify).at(0).toElement();
	QDomNodeList songLists = node.elementsByTagName("Song");

	QVector<QVector<QString>> songListsTemp;

	for (int i = 0; i < songLists.count(); i++)
	{
		QVector<QString> temp;

		QDomElement node1 = songLists.at(i).toElement();

		temp.push_back(AppPath + node1.elementsByTagName("PngPath").at(0).toElement().text());
		temp.push_back(node1.elementsByTagName("SongName").at(0).toElement().text());
		temp.push_back(node1.elementsByTagName("SingerName").at(0).toElement().text());
		temp.push_back(node1.elementsByTagName("Album").at(0).toElement().text());
		temp.push_back(node1.elementsByTagName("Duration").at(0).toElement().text());

		songListsTemp.push_back(temp);
	}

	if (songListsTemp.size() > 0)
		table_widget_->UpdateUi(songListsTemp);
}

void BestNewMusic::SlotNavBtnGroupClicked(QAbstractButton* _btn)
{
	if (_btn->text() == StdString2QString("新歌速递"))
		ui.stackedWidget->setCurrentIndex(0);
	else
		ui.stackedWidget->setCurrentIndex(1);
}

void BestNewMusic::SlotClassifyBtnGroupClicked(QAbstractButton* _btn)
{

}

void BestNewMusic::SlotNewSongBtnGroupClicked(QAbstractButton* _btn)
{
	ReadConfig(_btn->text());
}