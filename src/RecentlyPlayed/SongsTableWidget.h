#pragma once

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QTableWidgetItem>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFont>

#include "recently_played_global.h"

#define		AppPath		QCoreApplication::applicationDirPath()
// 配置文件
#define		ConfigFile		"/../config/RecentlyPlay.xml"
// 图片路径
#define		TagFile		"/../res/最近播放/"

// 自定义委托事件
class CustomDelegate
	: public QStyledItemDelegate
{
public:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
	{
		if (option.state & QStyle::State_Selected)	// 如果项被选中，则填充选中色
			painter->fillRect(option.rect, option.palette.highlight());
		else
		{
			// 否则，根据行号设置背景颜色
			int row = index.row();
			QColor backgroundColor = (row % 2 == 0) ? QColor("#ffffff") : QColor("#fafafa");
			painter->fillRect(option.rect, backgroundColor);
		}

		// 最后调用父类的 paint 函数绘制项的内容
		QStyledItemDelegate::paint(painter, option, index);
	}
};

// 自定义表格，禁止双击修改
class CustomTableWidget
	: public QTableWidget
{
public:
	CustomTableWidget(QWidget* parent = nullptr) : QTableWidget(parent) {}

protected:
	void mouseDoubleClickEvent(QMouseEvent* event) override
	{
		// 空函数体，以禁用鼠标双击事件
		// 可以在此处添加自定义的处理逻辑
	}
};

class SongsTableWidget
	: public QObject
{
	Q_OBJECT

public:
	SongsTableWidget(QWidget *parent = nullptr);
	~SongsTableWidget();

	QWidget* GetWidget();

private:

	void InitGui();

	void UpdateRow(int _row, const QVector<QString>& _row_data);

	void ReadConfig();

	void AddTitle();

private:

	CustomTableWidget* tableWidget_;
};
