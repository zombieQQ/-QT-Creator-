#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QDateTime>

#include "SongsTableWidget.h"
#include "ui_RecommendSong.h"

class RecommendSong
	: public QWidget
{
	Q_OBJECT

public:
	RecommendSong(QWidget *parent = nullptr);
	~RecommendSong();

	void SetPlayMusicPng(const bool& _flag);

private:

	void InitUi();

private:
	Ui::RecommendSongClass ui;

	std::shared_ptr<SongsTableWidget> song_table_widget_ = std::make_shared<SongsTableWidget>();
};
