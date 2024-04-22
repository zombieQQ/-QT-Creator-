#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFile>
#include <qbuttongroup.h>
#include <QDesktopServices>
#include <qurl.h>

#include "interface/ILiveBroadcast.h"
#include "ui_LiveBroadcastService.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/Video/scroll_area.qss"

class LiveBroadcastService 
	: public QWidget
	, public ILiveBroadcast
{
	Q_OBJECT

public:
	LiveBroadcastService(QWidget *parent = nullptr);
	~LiveBroadcastService();

	virtual QWidget* GetLiveWidget() override;

private:

	QString OpenQssFile(const std::string& _qssFile);

	void InitUi();

	void InitConnect();

	void SetBtnGroup();

private:
	Ui::LiveBroadcastServiceClass ui;

	QScrollArea* scroll_area_ = nullptr;

	QButtonGroup* btnsGroup_ = new QButtonGroup;
};
