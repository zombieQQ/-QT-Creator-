#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <qfile.h>
#include <QVBoxLayout>
#include <memory>

#include "interface/IRecentlyPlayed.h"
#include "ui_RecentlyPlayed.h"
#include "SongsTableWidget.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// ��������qss�ļ�
#define     ScrollAreaQss   "/../src/RecentlyPlayed/scroll_area.qss"

class RecentlyPlayed
	: public QWidget
	, public IRecentlyPlayed
{
	Q_OBJECT

public:
	RecentlyPlayed(QWidget *parent = nullptr);
	~RecentlyPlayed();

	virtual QWidget* GetWidget() override;

private:

	// ��qss�ļ�
	QString OpenQssFile(const std::string& _qssFile);

private:
	Ui::RecentlyPlayedClass ui;

	QScrollArea* scroll_area_ = nullptr;

	std::shared_ptr<SongsTableWidget> table_widget_;
};
