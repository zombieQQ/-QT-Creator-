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
		// �պ����壬�Խ������˫���¼�
		// �����ڴ˴�����Զ���Ĵ����߼�
	}

private:

	void InitGui();

private:

	int row_ = 0;	// ����
	int col_ = 0;	// ����
};