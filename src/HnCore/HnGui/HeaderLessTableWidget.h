#pragma once

#include <QtCore/QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QTableWidgetItem>

#include "interface/IHeaderLessTableWidget.h"

// �Զ���ί���¼�
class CustomDelegate
	: public QStyledItemDelegate
{
public:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
	{
		// ����ѡ�У������ѡ��ɫ
		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());
		else
		{
			// ���򣬸����к����ñ�����ɫ
			int row = index.row();
			QColor backgroundColor = (row % 2 == 0) ? QColor("#fafafa") : QColor("#ffffff");
			painter->fillRect(option.rect, backgroundColor);
		}

		// �����ø���� paint ���������������
		QStyledItemDelegate::paint(painter, option, index);
	}
};

// �Զ����񣬽�ֹ˫���޸�
class CustomTableWidget 
	: public QTableWidget
{
public:
	CustomTableWidget(QWidget* parent = nullptr) : QTableWidget(parent) {}

protected:
	void mouseDoubleClickEvent(QMouseEvent* event) override
	{
		// �պ����壬�Խ������˫���¼�
		// �����ڴ˴�����Զ���Ĵ����߼�
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

	int row_ = 0;	// ����
	int col_ = 0;	// ����
};
