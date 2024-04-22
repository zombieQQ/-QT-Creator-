#pragma once

#include <QtCore/QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QTableWidgetItem>
#include <QLabel>
#include <QPixmap>
#include <QHeaderView>

#include "main_control_global.h"

// 自定义委托事件
class CustomDelegate
	: public QStyledItemDelegate
{
public:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
	{
		// 如果项被选中，则填充选中色
		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());
		else
		{
			// 否则，根据行号设置背景颜色
			int row = index.row();
			QColor backgroundColor = (row % 2 == 0) ? QColor("#fafafa") : QColor("#ffffff");
			painter->fillRect(option.rect, backgroundColor);
		}

		// 最后调用父类的 paint 函数绘制项的内容
		QStyledItemDelegate::paint(painter, option, index);
	}
};

class SongListTableWidget
	: public QTableWidget
{
	Q_OBJECT

public:
	SongListTableWidget(QWidget* parent = nullptr);
	~SongListTableWidget();

public:

	void UpdateUi(const QVector<QVector<QString>>& _songLists);

protected:

	void mouseDoubleClickEvent(QMouseEvent* event) override
	{
		// 空函数体，以禁用鼠标双击事件
		// 可以在此处添加自定义的处理逻辑
	}

private:

	void InitGui();

private:

	int row_ = 0;	// 行数
	int col_ = 0;	// 列数
};