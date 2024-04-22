#pragma once

#include <QWidget>
#include "ui_CustomTitleBar.h"

#include <QMouseEvent>
#include <qpushbutton.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qfile.h>
#include <QStack>
#include <memory>
#include <QCursor>

#include "Peeling.h"

#define		AppPath		QCoreApplication::applicationDirPath()

#define		QString2StdString(x)	(QString(x).toStdString())
#define		StdString2QString(x)	(QString::fromLocal8Bit(std::string(x).c_str()))

class CustomTitleBar
	: public QWidget
{
	Q_OBJECT

public:
	explicit CustomTitleBar(QWidget *parent = nullptr);
	~CustomTitleBar();

signals:

	void SignalForwardAndBackWard(const bool& _flag);

private:
    // 鼠标按下事件
	void mousePressEvent(QMouseEvent* event) override;

    // 鼠标移动事件，用于实现拖动效果
    void mouseMoveEvent(QMouseEvent* event) override;

    // 绘制自定义标题栏的背景
    void paintEvent(QPaintEvent* event) override;

	// 初始化
	void InitUi();

	// 初始化连接
	void InitConnect();

private slots:
	// 设置qss
	void SettingQss(const std::string& _qssFileName);

private:
	Ui::CustomTitleBarClass ui;

	// 鼠标按下时的初始位置
	QPoint dragStartPosition_;

	Peeling*		peeling_widget_ = new Peeling;

	// 当前qss文件名
	std::string   cur_qss_file_name_;
};
