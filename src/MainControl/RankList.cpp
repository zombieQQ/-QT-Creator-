#include "RankList.h"

RankList::RankList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitUi();

	InitData();
}

RankList::~RankList()
{}

QWidget* RankList::GetWidget()
{
	CreateSoarTableWidget();

	CreateNewSongTableWidget();

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

void RankList::InitUi()
{
	QString qss = OpenQssFile(ViewAllQss);

	ui.new_song_btn->setStyleSheet(qss);
	ui.soar_btn->setStyleSheet(qss);

	// 获取当前日期
	QDateTime currentDateTime = QDateTime::currentDateTime();

	// 获取当前日期
	QDate currentDate = currentDateTime.date();

	// 获取月份和日期
	int month = currentDate.month();
	int day = currentDate.day();

	QString date = QString::number(month) + StdString2QString("月") + QString::number(day) + StdString2QString("日更新");
	ui.soar_label->setText(StdString2QString("飙升榜") + "\n" + date);
	ui.new_song_label->setText(StdString2QString("新歌榜") + "\n" + date);
}

void RankList::InitData()
{
	soarTableData.push_back({ "1", "302%", "Outlaw（不法之徒）", "Sewas" });
	soarTableData.push_back({ "2", "285%", "爱到1440", "时代少年团" });
	soarTableData.push_back({ "3", "202%", "十二月的奇迹（我望眼欲穿）", "呆呆破" });
	soarTableData.push_back({ "4", "188%", "Qay Raggi（茶的颜色）", "Ahmatjan-Ebrayim" });
	soarTableData.push_back({ "5", "188%", "离别开出花", "就是南方凯（项学凯）" });

	newTableData.push_back({ "1", "202%", "爱丫爱丫（live）", "汪苏泷" });
	newTableData.push_back({ "2", "185%", "冷战", "Vinida (万妮达)" });
	newTableData.push_back({ "3", "302%", "十二月的奇迹（我望眼欲穿）", "呆呆破" });
	newTableData.push_back({ "4", "108%", "幕后生活", "海洋Bo" });
	newTableData.push_back({ "5", "128%", "情书", "薛之谦" });
}

void RankList::CreateSoarTableWidget()
{
	soarTableWidget_ = global_gui_factory_->CreateHeaderLessTableWidget();

	soarTableWidget_->SetRowCol(5, 4);

	soarTableWidget_->UpdateTableWidget(soarTableData);

	QVBoxLayout* layout = new QVBoxLayout(ui.soar_list);
	layout->addWidget((QWidget*)soarTableWidget_->GetWidget());
	layout->setContentsMargins(0, 0, 0, 0);
}

void RankList::CreateNewSongTableWidget()
{
	newSongTableWidget_ = global_gui_factory_->CreateHeaderLessTableWidget();

	newSongTableWidget_->SetRowCol(5, 4);

	newSongTableWidget_->UpdateTableWidget(newTableData);

	QVBoxLayout* layout = new QVBoxLayout(ui.new_song_list);
	layout->addWidget((QWidget*)newSongTableWidget_->GetWidget());

	layout->setContentsMargins(0, 0, 0, 0);
}

QString RankList::OpenQssFile(std::string _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}