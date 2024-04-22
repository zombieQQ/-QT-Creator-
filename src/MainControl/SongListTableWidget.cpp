#include "SongListTableWidget.h"

SongListTableWidget::SongListTableWidget(QWidget *parent)
	: QTableWidget(parent)
{
	InitGui();
}

SongListTableWidget::~SongListTableWidget()
{}

void SongListTableWidget::UpdateUi(const QVector<QVector<QString>>&_songLists)
{
	this->clear();

	this->setRowCount(_songLists.size());
	this->setColumnCount(_songLists[0].size() + 1);

	for (int i = 0; i < _songLists.size(); i++)
	{
		QTableWidgetItem* item1 = new QTableWidgetItem(StdString2QString("0" + std::to_string(i + 1)));
		item1->setTextColor(QColor("#EC4141"));
		item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		this->setItem(i, 0, item1);

		QLabel* label = new QLabel();
		if(i % 2)
			label->setStyleSheet("background-color: #FFFFFF;");
		else
			label->setStyleSheet("background-color: #FAFAFA;");

		QPixmap pixmap(_songLists[i][0]);
		label->setPixmap(pixmap);
		this->setCellWidget(i, 1, label);

		QTableWidgetItem* item2 = new QTableWidgetItem(_songLists[i][1]);
		item2->setTextColor(QColor("#333333"));
		item2->setTextAlignment(Qt::AlignVCenter);
		this->setItem(i, 2, item2);

		QTableWidgetItem* item3 = new QTableWidgetItem(_songLists[i][2]);
		item3->setTextColor(QColor("#333333"));
		item3->setTextAlignment(Qt::AlignVCenter);
		this->setItem(i, 3, item3);

		QTableWidgetItem* item4 = new QTableWidgetItem(_songLists[i][3]);
		item4->setTextColor(QColor("#333333"));
		item4->setTextAlignment(Qt::AlignVCenter);
		this->setItem(i, 4, item4);

		QTableWidgetItem* item5 = new QTableWidgetItem(_songLists[i][4]);
		item5->setTextColor(QColor("#333333"));
		item5->setTextAlignment(Qt::AlignVCenter);
		this->setItem(i, 5, item5);
	}

	QHeaderView* verticalHeader = this->verticalHeader();
	verticalHeader->setSectionResizeMode(QHeaderView::Stretch);

	this->setFixedHeight(101 * 5);
	this->setFixedWidth(1012);

	this->setColumnWidth(0, 83);
	this->setColumnWidth(1, 80);
	this->setColumnWidth(2, 349);
	this->setColumnWidth(3, 200);
	this->setColumnWidth(4, 200);
	this->setColumnWidth(5, 100);
}

void SongListTableWidget::InitGui()
{
	this->setItemDelegate(new CustomDelegate());
	// 隐藏表格中的网格线
	this->setShowGrid(false);
	// 隐藏列表头
	this->horizontalHeader()->setVisible(false);
	// 隐藏行表头
	this->verticalHeader()->setVisible(false);
	// 选中一行
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 设置控件不接受焦点
	this->setFocusPolicy(Qt::NoFocus);
}
