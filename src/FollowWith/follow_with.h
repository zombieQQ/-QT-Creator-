#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <qfile.h>
#include <QVBoxLayout>
#include <QtXml/QDomDocument>
#include <QSpacerItem>

#include "interface/IFollowWith.h"
#include "ui_FollowWith.h"
#include "TrendService.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/FollowWith/scroll_area.qss"

// 配置文件
#define		ConfigFile		"/../config/FollowWith.xml"

class FollowWith
	: public QWidget
	, public IFollowWith
{
	Q_OBJECT

public:
	FollowWith(QWidget *parent = nullptr);
	~FollowWith();

	virtual QWidget* GetWidget() override;

private:

	// 打开qss文件
	QString OpenQssFile(const std::string& _qssFile);

	void InitUi(const QVector<QString>& _msg);

	void ReadConfig();

private:
	Ui::FollowWithClass ui;

	QScrollArea* scroll_area_ = nullptr;

	std::shared_ptr<TrendService> trend_service_ = std::make_shared<TrendService>();
};
