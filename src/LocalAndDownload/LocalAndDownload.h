#pragma once

#include <QWidget>
#include <QFile>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

#include "interface/ILocalAndDownload.h"
#include "ui_LocalAndDownload.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// ��������qss�ļ�
#define     ScrollAreaQss   "/../src/LocalAndDownload/scroll_area.qss"

class LocalAndDownload
	: public QWidget
	, public ILocalAndDownload
{
	Q_OBJECT

public:
	LocalAndDownload(QWidget *parent = nullptr);
	~LocalAndDownload();

	virtual QWidget* GetWidget() override;

private:

	// ��qss�ļ�
	QString OpenQssFile(const std::string& _qssFile);

private:
	Ui::LocalAndDownloadClass ui;

	QScrollArea* scroll_area_ = nullptr;
};
