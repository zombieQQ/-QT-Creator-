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
#include <QPushButton>
#include <QIcon>
#include <QMouseEvent>
#include <unordered_map>
#include <qcursor.h>

#include "main_control_global.h"

#define		AppPath		QCoreApplication::applicationDirPath()

// 配置文件
#define		ConfigFile		"/../config/RecommendSongs.xml"

// 图片路径
#define		TagFile			"/../res/最近播放/"

// “喜欢”图片
#define     HeartFile		"/../res/推荐歌单/broken _ heart.png"
#define		LikeHeartFile	"/../res/推荐歌单/broken _ like_heart.png"

// “下载”图片
#define		LoadFile		"/../res/推荐歌单/broken _ download.png"

// “播放”图片
#define		OutLineSpeakerFile	"/../res/推荐歌单/outline _ speaker.png"
#define		OutLineSpeaker1File "/../res/推荐歌单/outline _ speaker-2.png"

// 自定义委托事件
class RecommendCustomDelegate
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

	void SetMusicInfo(const int& _idx, const std::vector<QString>& _musicInfo)
	{
		musicInfos[_idx] = _musicInfo;
	}

protected:

	void mouseDoubleClickEvent(QMouseEvent* event) override
	{
		// 空函数体，以禁用鼠标双击事件
		// 可以在此处添加自定义的处理逻辑

		QModelIndex index = currentIndex();

		// 设置音乐标题字体颜色
		QWidget* titleWidget = (QWidget*)this->cellWidget(index.row(), 3);
		QList<QLabel*> labelList = titleWidget->findChildren<QLabel*>();
		for (QLabel* temp : labelList)
		{
			if(temp->objectName() == musicInfos[index.row()][0])
				temp->setStyleSheet("color: #EE4141;");
		}

		// 序号
		QLabel* numLabel = (QLabel*)this->cellWidget(index.row(), 0);
		QPixmap pixmap(AppPath + StdString2QString(OutLineSpeaker1File));
		numLabel->setPixmap(pixmap);

		if (lastRow_ == index.row() || lastRow_ == -1)
		{
			lastRow_ = index.row();

			if (musicInfos.find(lastRow_) != musicInfos.end())
				global_play_music_->SetPlayMusic(musicInfos[lastRow_]);

			return;
		}

		QWidget* lastTitleWidget = (QWidget*)this->cellWidget(lastRow_, 3);
		QList<QLabel*> lastLabelList = lastTitleWidget->findChildren<QLabel*>();
		for (QLabel* temp : lastLabelList)
		{
			if (temp->objectName() == musicInfos[lastRow_][0])
				temp->setStyleSheet("color: #646464;");
		}

		QLabel* lastNumLabel = (QLabel*)this->cellWidget(lastRow_, 0);
		lastNumLabel->clear();
		lastNumLabel->setText("0" + QString::number(lastRow_));
		lastNumLabel->setAlignment(Qt::AlignCenter);
		if (lastRow_ % 2)
			lastNumLabel->setStyleSheet("background-color: #FAFAFA;color: #CCCCCC");
		else
			lastNumLabel->setStyleSheet("background-color: #FFFFFF;color: #CCCCCC");

		lastRow_ = index.row();

		if(musicInfos.find(lastRow_) != musicInfos.end())
			global_play_music_->SetPlayMusic(musicInfos[lastRow_]);
	}

private:

	int lastRow_ = -1;

	std::unordered_map<int, std::vector<QString>> musicInfos;
};

class SongsTableWidget
	: public QObject
{
	Q_OBJECT

public:
	SongsTableWidget(QWidget *parent = nullptr);
	~SongsTableWidget();

	QWidget* GetWidget();

	void SetPlayMusicPng(const bool& _flag);

private:

	void InitGui();

	void UpdateRow(int _row, const QVector<QString>& _row_data);

	void ReadConfig();

	void AddTitle();

private:

	CustomTableWidget* tableWidget_;
};
