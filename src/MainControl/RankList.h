#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QFile>
#include <QDateTime>
#include <vector>
#include <string>
#include <QTableWidget>

#include "ui_RankList.h"
#include "main_control_global.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/MainControl/scroll_area.qss"

#define     ViewAllQss		"/../src/MainControl/view_all.qss"

class RankList : public QWidget
{
	Q_OBJECT

public:
	RankList(QWidget *parent = nullptr);
	~RankList();

	QWidget* GetWidget();

private:

	QString OpenQssFile(std::string _qssFile);

	void InitUi();

	void InitData();

	void CreateSoarTableWidget();

	void CreateNewSongTableWidget();

private:
	Ui::RankListClass ui;

	QScrollArea* scroll_area_;

	std::vector<std::vector<std::string>>	soarTableData;
	std::vector<std::vector<std::string>>	newTableData;

	IHeaderLessTableWidgetSPtr soarTableWidget_;
	IHeaderLessTableWidgetSPtr newSongTableWidget_;
};
