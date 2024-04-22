#pragma once

#include <QWidget>
#include <qcoreapplication.h>
#include <qscrollarea.h>
#include <QScrollBar>
#include <QVBoxLayout>
#include <qfile.h>

#include "interface/IPrivateRoaming.h"
#include "ui_PrivateRoaming.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/PodCast/scroll_area.qss"

class PrivateRoaming
	: public QWidget
	, public IPrivateRoaming
{
	Q_OBJECT

public:
	PrivateRoaming(QWidget *parent = nullptr);
	~PrivateRoaming();

	virtual QWidget* GetWidget() override;

private:

	// 打开qss文件
	QString OpenQssFile(const std::string& _qssFile);

	void SettingQss(const QString& _qss);

private:
	Ui::PrivateRoamingClass ui;

	QScrollArea* scroll_area_ = nullptr;
};
