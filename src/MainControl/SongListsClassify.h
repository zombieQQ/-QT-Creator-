#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QFile>

#include "ui_SongListsClassify.h"
#include "main_control_global.h"

#define		AppPath		QCoreApplication::applicationDirPath()
#define     BtnQss   "/../src/MainControl/song_lists_classify.qss"

class SongListsClassify : public QWidget
{
	Q_OBJECT

public:
	SongListsClassify(QWidget *parent = nullptr);
	~SongListsClassify();

signals:

	void SignalClickedBtn(QString _btnText);

private slots:

	void SlotBtnGroupClicked(QAbstractButton* _btn);

private:

	// ��qss�ļ�
	QString OpenQssFile(std::string _qssFile);

	// ����qss
	void SettingQss(QString _qss);

	void InitUi();

private:
	Ui::SongListsClassifyClass ui;

	QButtonGroup* group_btns_;
};
