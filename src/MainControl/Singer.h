#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QFile>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QButtonGroup>
#include <QDomDocument>

#include "ui_Singer.h"
#include "main_control_global.h"

#define		AppPath					QCoreApplication::applicationDirPath()
#define     BtnQss					"/../src/MainControl/SingerClassfiy.qss"
#define		SingerNameBtnQss		"/../src/MainControl/SingerNameBtn.qss"

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/MainControl/scroll_area.qss"

#define     SingerConfig	"/../config/Singer.xml";

class Singer : public QWidget
{
	Q_OBJECT

public:
	Singer(QWidget *parent = nullptr);
	~Singer();

	QWidget* GetWidget();

private:

	QString OpenQssFile(const std::string& _qssFile);

	void SettingClassifyQss(const QString& _qss);

	void SettingNameBtnQss(const QString& _qss);

	void InitUi();

	void InitConnect();

	void InitButtonGroup();

	void UpdateUi();

private slots:

	void SlotLanguagesBtnGroupClicked(QAbstractButton* _btn);

	void SlotClassifyBtnGroupClicked(QAbstractButton* _btn);

	void SlotPopularBtnGroupClicked(QAbstractButton* _btn);

private:
	Ui::SingerClass ui;

	QScrollArea*	scrollArea_;

	QButtonGroup*	languagesBtnGroup_;
	QButtonGroup*	classifyBtnGroup_;
	QButtonGroup*	popularBtnGroup_;
	QButtonGroup*	userBtnGroup_;
	QButtonGroup*	nameBtnGroup_;

	QString			languages_ = StdString2QString("全部");
	QString			classify_ = StdString2QString("全部");
	QString			popular_ = StdString2QString("热门");
};
