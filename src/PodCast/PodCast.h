#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <qfile.h>

#include "interface/IPodCast.h"
#include "ui_PodCast.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/PodCast/scroll_area.qss"

class PodCast 
	: public QWidget
	, public IPodCast
{
	Q_OBJECT

public:
	PodCast(QWidget *parent = nullptr);
	~PodCast();

	virtual QWidget* GetWidget() override;

private:

	// 打开qss文件
	QString OpenQssFile(const std::string& _qssFile);

	void SettingQss(const QString& _qss);

private:
	Ui::PodCastClass ui;

	QScrollArea* scroll_area_ = nullptr;
};
