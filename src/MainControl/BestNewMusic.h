#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFile>
#include <QButtonGroup>
#include <QCoreApplication>
#include <QDomDocument>
#include <QVector>

#include "main_control_global.h"
#include "ui_BestNewMusic.h"
#include "SongListTableWidget.h"

#define		AppPath					QCoreApplication::applicationDirPath()
#define     ScrollAreaQss			"/../src/MainControl/scroll_area.qss"
#define		NavigationBtnQss		"/../src/MainControl/NavigationBtn.qss"
#define		NewSongBtnsQss			"/../src/MainControl/newSongBtns.qss"
#define     ClassifyBtnQss					"/../src/MainControl/song_lists_classify.qss"
#define     SongListonfig			"/../config/BestNewMusic.xml";

class BestNewMusic
	: public QWidget
{
	Q_OBJECT

public:
	BestNewMusic(QWidget *parent = nullptr);
	~BestNewMusic();

	QWidget* GetWidget();

private:

	QString OpenQssFile(const std::string& _qssFile);

	void SetBtnGroup();

	void SetNavigationBtnQss();

	void SetNewSongDVDBtnsQss();

	void SetClassifyBtnsQss();

	void InitUi();

	void InitConnect();

	void ReadConfig(const QString& _songClassify);

private slots:

	void SlotNewSongBtnGroupClicked(QAbstractButton* _btn);

	void SlotNavBtnGroupClicked(QAbstractButton* _btn);

	void SlotClassifyBtnGroupClicked(QAbstractButton* _btn);

private:
	Ui::BestNewMusicClass ui;

	QScrollArea*	scroll_area_;

	QButtonGroup*	navigation_btns_ = new QButtonGroup;
	QButtonGroup*	new_song_btns_	 = new QButtonGroup;
	QButtonGroup*	new_dvd_btns_	 = new QButtonGroup;
	QButtonGroup*	classify_btns_	 = new QButtonGroup;

	std::shared_ptr<SongListTableWidget> table_widget_ = std::make_shared<SongListTableWidget>();
};
