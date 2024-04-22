#include "RecommendSong.h"

RecommendSong::RecommendSong(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitUi();
}

RecommendSong::~RecommendSong()
{}

void RecommendSong::SetPlayMusicPng(const bool& _flag)
{
	song_table_widget_->SetPlayMusicPng(_flag);
}

void RecommendSong::InitUi()
{
	QVBoxLayout* layout = new QVBoxLayout;
	ui.widget->setLayout(layout);
	layout->addWidget(song_table_widget_->GetWidget());
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0, 0);

	// 获取当前日期
	QDateTime currentDateTime = QDateTime::currentDateTime();

	// 获取当前日期
	QDate currentDate = currentDateTime.date();

	// 获取日期
	int day = currentDate.day();

	ui.dateLabel->setText(QString::number(day));
}
