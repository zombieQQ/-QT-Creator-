#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>

#include "main_control_global.h"
#include "ui_recommend_song_list.h"

class RecommendSongList
	: public QWidget
{
	Q_OBJECT

public:
	RecommendSongList(QWidget *parent = nullptr);
	~RecommendSongList();

private:

	void InitConnect();

signals:

	void SignalRecommendBtnClicked();

private slots:

	void SlotRecommendBtnClicked();

private:
	Ui::RecommendSongListClass ui;
};
