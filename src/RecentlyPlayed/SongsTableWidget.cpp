#include "SongsTableWidget.h"

SongsTableWidget::SongsTableWidget(QWidget *parent)
	: QObject(parent)
	, tableWidget_(new CustomTableWidget)
{
	InitGui();

	ReadConfig();
}

SongsTableWidget::~SongsTableWidget()
{}

QWidget* SongsTableWidget::GetWidget()
{
	if(tableWidget_)
		return tableWidget_;
}

void SongsTableWidget::InitGui()
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

void SongsTableWidget::UpdateRow(int _row, const QVector<QString>& _row_data)
{
	tableWidget_->setItem(_row, 0, new QTableWidgetItem("0" + QString::number(_row)));
	tableWidget_->item(_row, 0)->setTextAlignment(Qt::AlignCenter);
	tableWidget_->item(_row, 0)->setTextColor(QColor("#CCCCCC"));

	QWidget* cellWidget = new QWidget();
	cellWidget->setMaximumSize(484, 44);

	if(_row % 2)
		cellWidget->setStyleSheet("background-color: #FAFAFA;");
	else 
		cellWidget->setStyleSheet("background-color: #FFFFFF;");

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(10, 10, 10, 10);
	cellWidget->setLayout(layout);

	QLabel* titleLabel = new QLabel(_row_data[0]);
	int labelWidth = _row_data[0].length() * QFontMetrics(titleLabel->font()).width("X");
	titleLabel->setFixedWidth(labelWidth);
	titleLabel->setStyleSheet("color: #323232");
	QFont font("宋体", 9); // 创建宋体字体，大小为9
	titleLabel->setFont(font); // 设置字体

	layout->addWidget(titleLabel);

	QStringList list = _row_data[1].split('|');
	for (int i = 0; i < list.count(); i++)
	{
		QLabel* tagLabel = new QLabel;
		QString pngPath = AppPath + StdString2QString(TagFile) + list[i] + ".png";
		QPixmap pixmap(pngPath);
		tagLabel->setPixmap(pngPath);

		layout->addWidget(tagLabel);
	}
	layout->addStretch();

	tableWidget_->setCellWidget(_row, 1, cellWidget);

	tableWidget_->setItem(_row, 2, new QTableWidgetItem(_row_data[2]));

	tableWidget_->setItem(_row, 3, new QTableWidgetItem(_row_data[3]));
	tableWidget_->item(_row, 3)->setTextColor(QColor("#CCCCCC"));
}

void SongsTableWidget::ReadConfig()
{
	QString filePath = AppPath + ConfigFile;

	QFile qssFile(filePath);
	if (!qssFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QDomDocument doc;
	if (!doc.setContent(&qssFile))
	{
		qssFile.close();
		return;
	}

	qssFile.close();

	// 获取根元素
	QDomElement root = doc.documentElement();

	QDomNodeList node = root.elementsByTagName("Song");

	tableWidget_->setRowCount(node.count() + 1);
	tableWidget_->setColumnCount(4);

	AddTitle();

	for (int i = 0; i < node.count(); i++)
	{
		QVector<QString> msg;

		QDomElement temp = node.at(i).toElement();

		QString musicTitle = temp.elementsByTagName("MusicTitle").at(0).toElement().text();
		QString tagName = temp.elementsByTagName("TagName").at(0).toElement().text();
		QString singer = temp.elementsByTagName("Singer").at(0).toElement().text();
		QString playTime = temp.elementsByTagName("PlayTime").at(0).toElement().text();

		msg.push_back(musicTitle);
		msg.push_back(tagName);
		msg.push_back(singer);
		msg.push_back(playTime);

		UpdateRow(i + 1, msg);
	}
}

void SongsTableWidget::AddTitle()
{
	tableWidget_->setItem(0, 0, new QTableWidgetItem(""));
	tableWidget_->setItem(0, 1, new QTableWidgetItem(StdString2QString("音乐标题")));
	tableWidget_->setItem(0, 2, new QTableWidgetItem(StdString2QString("歌手")));
	tableWidget_->setItem(0, 3, new QTableWidgetItem(StdString2QString("播放时间")));

	tableWidget_->item(0, 0)->setTextColor(QColor("#888888"));
	tableWidget_->item(0, 1)->setTextColor(QColor("#888888"));
	tableWidget_->item(0, 2)->setTextColor(QColor("#888888"));
	tableWidget_->item(0, 3)->setTextColor(QColor("#888888"));

	tableWidget_->setColumnWidth(0, 77);
	tableWidget_->setColumnWidth(1, 484);
	tableWidget_->setColumnWidth(2, 292);
	tableWidget_->setColumnWidth(3, 159);

	tableWidget_->setRowHeight(0, 44);
}
