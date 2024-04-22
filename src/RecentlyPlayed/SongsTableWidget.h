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
// �����ļ�
#define		ConfigFile		"/../config/RecentlyPlay.xml"
// ͼƬ·��
#define		TagFile		"/../res/�������/"

// �Զ���ί���¼�
class CustomDelegate
	: public QStyledItemDelegate
{
public:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
	{
		if (option.state & QStyle::State_Selected)	// ����ѡ�У������ѡ��ɫ
			painter->fillRect(option.rect, option.palette.highlight());
		else
		{
			// ���򣬸����к����ñ�����ɫ
			int row = index.row();
			QColor backgroundColor = (row % 2 == 0) ? QColor("#ffffff") : QColor("#fafafa");
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
