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

	// ��ȡ��ǰ����
	QDateTime currentDateTime = QDateTime::currentDateTime();

	// ��ȡ��ǰ����
	QDate currentDate = currentDateTime.date();

	// ��ȡ����
	int day = currentDate.day();

	ui.dateLabel->setText(QString::number(day));
}
