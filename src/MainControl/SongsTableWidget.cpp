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

void SongsTableWidget::SetPlayMusicPng(const bool& _flag)
{
	QModelIndex index = tableWidget_->currentIndex();

	QLabel* numLabel = (QLabel*)tableWidget_->cellWidget(index.row(), 0);

	if (_flag)
	{
		QPixmap pixmap(AppPath + StdString2QString(OutLineSpeaker1File));
		numLabel->setPixmap(pixmap);
	}
	else
	{
		QPixmap pixmap(AppPath + StdString2QString(OutLineSpeakerFile));
		numLabel->setPixmap(pixmap);
	}
}

void SongsTableWidget::InitGui()
{
	tableWidget_->setItemDelegate(new RecommendCustomDelegate());
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
	std::vector<QString> musicInfo;
	musicInfo.emplace_back(_row_data[0]);
	musicInfo.emplace_back(_row_data[2]);
	musicInfo.emplace_back(_row_data[4]);

	tableWidget_->SetMusicInfo(_row, musicInfo);

	// 序号
	QLabel* num = new QLabel("0" + QString::number(_row));
	num->setAlignment(Qt::AlignCenter);
	if (_row % 2)
		num->setStyleSheet("background-color: #FAFAFA;color: #CCCCCC");
	else
		num->setStyleSheet("background-color: #FFFFFF;color: #CCCCCC");
	tableWidget_->setCellWidget(_row, 0, num);

	// 喜欢
	QPushButton* likeBtn = new QPushButton;
	QIcon likeBtnIcon(AppPath + StdString2QString(HeartFile));
	likeBtn->setIcon(likeBtnIcon);
	likeBtn->setIconSize(QSize(40, 40));
	if (_row % 2)
		likeBtn->setStyleSheet("background-color: #FAFAFA;");
	else
		likeBtn->setStyleSheet("background-color: #FFFFFF;");

	likeBtn->setCursor(Qt::PointingHandCursor);
	likeBtn->setObjectName("nolike");

	connect(likeBtn, &QPushButton::clicked, [=]() {

		if (likeBtn->objectName() == "nolike")
		{
			QIcon likeBtnIcon(AppPath + StdString2QString(LikeHeartFile));
			likeBtn->setIcon(likeBtnIcon);
			likeBtn->setIconSize(QSize(40, 40));

			likeBtn->setObjectName("like");
		}
		else if(likeBtn->objectName() == "like")
		{
			QIcon likeBtnIcon(AppPath + StdString2QString(HeartFile));
			likeBtn->setIcon(likeBtnIcon);
			likeBtn->setIconSize(QSize(40, 40));

			likeBtn->setObjectName("nolike");
		}
	});

	tableWidget_->setCellWidget(_row, 1, likeBtn);

	// 下载
	QPushButton* loadBtn = new QPushButton;
	QIcon loadBtnIcon(AppPath + StdString2QString(LoadFile));
	loadBtn->setIcon(loadBtnIcon);
	loadBtn->setIconSize(QSize(40, 40));
	if (_row % 2)
		loadBtn->setStyleSheet("background-color: #FAFAFA;");
	else
		loadBtn->setStyleSheet("background-color: #FFFFFF;");

	loadBtn->setCursor(Qt::PointingHandCursor);

	tableWidget_->setCellWidget(_row, 2, loadBtn);

	QWidget* cellWidget = new QWidget();
	cellWidget->setMaximumSize(339, 44);

	if (_row % 2)
		cellWidget->setStyleSheet("background-color: #FAFAFA;");
	else
		cellWidget->setStyleSheet("background-color: #FFFFFF;");

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(10, 10, 10, 10);
	cellWidget->setLayout(layout);	

	// 音乐标题
	QLabel* titleLabel = new QLabel(_row_data[0]);
	titleLabel->setObjectName(_row_data[0]);
	titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	titleLabel->setStyleSheet("color: #646464");
	layout->addWidget(titleLabel);

	// 标签
	QStringList list = _row_data[1].split('|');
	for (int i = 0; i < list.count(); i++)
	{
		QLabel* tagLabel = new QLabel(list[i]);
		QString pngPath = AppPath + StdString2QString(TagFile) + list[i] + ".png";
		QPixmap pixmap(pngPath);
		tagLabel->setPixmap(pngPath);

		layout->addWidget(tagLabel);
	}
	layout->addStretch();

	tableWidget_->setCellWidget(_row, 3, cellWidget);

	tableWidget_->setItem(_row, 4, new QTableWidgetItem(_row_data[2]));
	tableWidget_->setItem(_row, 5, new QTableWidgetItem(_row_data[3]));
	tableWidget_->setItem(_row, 6, new QTableWidgetItem(_row_data[4]));

	tableWidget_->item(_row, 4)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	tableWidget_->item(_row, 5)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	tableWidget_->item(_row, 6)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void SongsTableWidget::ReadConfig()
{
	tableWidget_->setRowCount(1);
	tableWidget_->setColumnCount(7);

	AddTitle();

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
	tableWidget_->setColumnCount(7);

	for (int i = 0; i < node.count(); i++)
	{
		QVector<QString> msg;

		QDomElement temp = node.at(i).toElement();

		QString musicTitle = temp.elementsByTagName("MusicTitle").at(0).toElement().text();
		QString tagName = temp.elementsByTagName("TagName").at(0).toElement().text();
		QString singer = temp.elementsByTagName("Singer").at(0).toElement().text();
		QString special = temp.elementsByTagName("Special").at(0).toElement().text();
		QString playTime = temp.elementsByTagName("PlayTime").at(0).toElement().text();

		msg.push_back(musicTitle);
		msg.push_back(tagName);
		msg.push_back(singer);
		msg.push_back(special);
		msg.push_back(playTime);

		UpdateRow(i + 1, msg);
	}
}

void SongsTableWidget::AddTitle()
{
	tableWidget_->setItem(0, 0, new QTableWidgetItem(StdString2QString("")));
	tableWidget_->setItem(0, 1, new QTableWidgetItem(StdString2QString("")));
	tableWidget_->setItem(0, 2, new QTableWidgetItem(StdString2QString("")));
	tableWidget_->setItem(0, 3, new QTableWidgetItem(StdString2QString("音乐标题")));
	tableWidget_->setItem(0, 4, new QTableWidgetItem(StdString2QString("歌手")));
	tableWidget_->setItem(0, 5, new QTableWidgetItem(StdString2QString("专辑")));
	tableWidget_->setItem(0, 6, new QTableWidgetItem(StdString2QString("时长")));

	tableWidget_->item(0, 3)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	tableWidget_->item(0, 4)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	tableWidget_->item(0, 5)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	tableWidget_->item(0, 6)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	tableWidget_->item(0, 3)->setTextColor(QColor("#888888"));
	tableWidget_->item(0, 4)->setTextColor(QColor("#888888"));
	tableWidget_->item(0, 5)->setTextColor(QColor("#888888"));
	tableWidget_->item(0, 6)->setTextColor(QColor("#888888"));

	tableWidget_->setColumnWidth(0, 70);
	tableWidget_->setColumnWidth(1, 48);
	tableWidget_->setColumnWidth(2, 48);
	tableWidget_->setColumnWidth(3, 339);
	tableWidget_->setColumnWidth(4, 182);
	tableWidget_->setColumnWidth(5, 242);
	tableWidget_->setColumnWidth(6, 83);

	tableWidget_->setRowHeight(0, 44);
}
