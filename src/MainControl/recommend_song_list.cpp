#include "recommend_song_list.h"

RecommendSongList::RecommendSongList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitConnect();
}

RecommendSongList::~RecommendSongList()
{}

void RecommendSongList::InitConnect()
{
	connect(ui.recommendBtn, &QPushButton::clicked, this, &RecommendSongList::SlotRecommendBtnClicked);
}

void RecommendSongList::SlotRecommendBtnClicked()
{
	emit SignalRecommendBtnClicked();
}