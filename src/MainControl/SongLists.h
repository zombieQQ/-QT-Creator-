#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QFile>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QtXml/QDomDocument>

#include "ui_SongLists.h"
#include "main_control_global.h"
#include "SongListsClassify.h"

#define		AppPath		QCoreApplication::applicationDirPath()
#define     BtnQss		"/../src/MainControl/song_lists_classify.qss"

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/MainControl/scroll_area.qss"

#define     AllSongListsConfig	"/../config/AllSongLists.xml";

class SongLists : public QWidget
{
	Q_OBJECT

public:
	SongLists(QWidget *parent = nullptr);
	~SongLists();

	QWidget* GetWidget();

private:

	// 打开qss文件
	QString OpenQssFile(std::string _qssFile);

	// 设置qss
	void SettingQss(QString _qss);

	void InitUi();

	void InitConnect();

	// 读配置文件设置界面
	void ReadConfig(QString _btnText);

private slots:

	void SlotAllSongListsClicked();

	void SlotClickedBtn(QString _btnText);

	void SlotBtnGroupClicked(QAbstractButton* _btn);

private:
	Ui::SongListsClass ui;

	bool			checked_;

	QButtonGroup*	group_btns_;

	QScrollArea*	scroll_area_;

	std::shared_ptr<SongListsClassify> song_lists_classify_;
};
