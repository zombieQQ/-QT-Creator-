#include "HeaderLessTableWidget.h"

HeaderLessTableWidget::HeaderLessTableWidget(QObject* parent)
	: QObject(parent)
	, tableWidget_(new CustomTableWidget)
{
	InitGui();
}

HeaderLessTableWidget::~HeaderLessTableWidget()
{}

void* HeaderLessTableWidget::GetWidget()
{
	if (tableWidget_)
		return (void*)tableWidget_;
}

void HeaderLessTableWidget::SetRowCol(int _row, int _col)
{
	row_ = _row;
	col_ = _col;

	tableWidget_->setRowCount(_row);
	tableWidget_->setColumnCount(_col);
}

void HeaderLessTableWidget::UpdateTableWidget(const std::vector<std::vector<std::string>>& _table_data)
{
	for (int i = 0;i < _table_data.size();i++)
	{
		UpdateRow(i, _table_data[i]);
	}
}

void HeaderLessTableWidget::InitGui()
{
	tableWidget_->setItemDelegate(new CustomDelegate());
	// 隐藏表格中的网格线
	tableWidget_->setShowGrid(false);
	// 隐藏列表头
	tableWidget_->horizontalHeader()->setVisible(false);
	// 隐藏行表头
	tableWidget_->verticalHeader()->setVisible(false);
	// 选中一行
	tableWidget_->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 设置控件不接受焦点
	tableWidget_->setFocusPolicy(Qt::NoFocus);
}

void HeaderLessTableWidget::UpdateRow(int _row, std::vector<std::string> _row_data)
{
	QTableWidgetItem* item1 = new QTableWidgetItem(StdString2QString(_row_data[0]));
	if(_row < 3)
		item1->setTextColor(QColor("#ec416a"));
	else
		item1->setTextColor(QColor("#969696"));

	item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	tableWidget_->setItem(_row, 0, item1);

	QTableWidgetItem* item2 = new QTableWidgetItem(StdString2QString(_row_data[1]));
	item2->setTextColor(QColor("#b39393"));
	item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	tableWidget_->setItem(_row, 1, item2);

	QTableWidgetItem* item3 = new QTableWidgetItem(StdString2QString(_row_data[2]));
	item3->setTextColor(QColor("#969696"));
	item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	tableWidget_->setItem(_row, 2, item3);

	QTableWidgetItem* item4 = new QTableWidgetItem(StdString2QString(_row_data[3]));
	item4->setTextColor(QColor("#b39393"));
	item4->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	tableWidget_->setItem(_row, 3, item4);

	QHeaderView* verticalHeader = tableWidget_->verticalHeader();
	verticalHeader->setSectionResizeMode(QHeaderView::Stretch);

	tableWidget_->setColumnWidth(0, 30);
	tableWidget_->setColumnWidth(1, 60);
	tableWidget_->setColumnWidth(2, 304);
	tableWidget_->setColumnWidth(3, 303);
}
