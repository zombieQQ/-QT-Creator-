#pragma once

#include <QtCore/QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QTableWidgetItem>

#include "interface/IHeaderLessTableWidget.h"

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

class HeaderLessTableWidget 
	: public QObject
	, public IHeaderLessTableWidget
{
	Q_OBJECT

public:
	HeaderLessTableWidget(QObject *parent = nullptr);
	~HeaderLessTableWidget();

	virtual void* GetWidget() override;

	virtual void SetRowCol(int _row, int _col) override;

	virtual void UpdateTableWidget(const std::vector<std::vector<std::string>>& _table_data) override;

private:

	void InitGui();

	void UpdateRow(int _row, std::vector<std::string> _row_data);

private:

	CustomTableWidget* tableWidget_;

	int row_ = 0;	// 行数
	int col_ = 0;	// 列数
};
