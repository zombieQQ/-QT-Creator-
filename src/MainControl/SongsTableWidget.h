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

// �����ļ�
#define		ConfigFile		"/../config/RecommendSongs.xml"

// ͼƬ·��
#define		TagFile			"/../res/�������/"

// ��ϲ����ͼƬ
#define     HeartFile		"/../res/�Ƽ��赥/broken _ heart.png"
#define		LikeHeartFile	"/../res/�Ƽ��赥/broken _ like_heart.png"

// �����ء�ͼƬ
#define		LoadFile		"/../res/�Ƽ��赥/broken _ download.png"

// �����š�ͼƬ
#define		OutLineSpeakerFile	"/../res/�Ƽ��赥/outline _ speaker.png"
#define		OutLineSpeaker1File "/../res/�Ƽ��赥/outline _ speaker-2.png"

// �Զ���ί���¼�
class RecommendCustomDelegate
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

	void SetMusicInfo(const int& _idx, const std::vector<QString>& _musicInfo)
	{
		musicInfos[_idx] = _musicInfo;
	}

protected:

	void mouseDoubleClickEvent(QMouseEvent* event) override
	{
		// �պ����壬�Խ������˫���¼�
		// �����ڴ˴�����Զ���Ĵ����߼�

		QModelIndex index = currentIndex();

		// �������ֱ���������ɫ
		QWidget* titleWidget = (QWidget*)this->cellWidget(index.row(), 3);
		QList<QLabel*> labelList = titleWidget->findChildren<QLabel*>();
		for (QLabel* temp : labelList)
		{
			if(temp->objectName() == musicInfos[index.row()][0])
				temp->setStyleSheet("color: #EE4141;");
		}

		// ���
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
