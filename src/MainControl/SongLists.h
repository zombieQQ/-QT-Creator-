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

// ��������qss�ļ�
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

	// ��qss�ļ�
	QString OpenQssFile(std::string _qssFile);

	// ����qss
	void SettingQss(QString _qss);

	void InitUi();

	void InitConnect();

	// �������ļ����ý���
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
