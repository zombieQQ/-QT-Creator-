#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <qfile.h>
#include <QVBoxLayout>

#include "interface/IMyLikeMusic.h"
#include "ui_MyLikeMusic.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/MyLikeMusic/scroll_area.qss"

class MyLikeMusic
	: public QWidget
	, public IMyLikeMusic
{
	Q_OBJECT

public:
	MyLikeMusic(QWidget *parent = nullptr);
	~MyLikeMusic();

	virtual QWidget* GetWidget() override;

private:

	// 打开qss文件
	QString OpenQssFile(const std::string& _qssFile);

private:
	Ui::MyLikeMusicClass ui;

	QScrollArea* scroll_area_ = nullptr;
};
