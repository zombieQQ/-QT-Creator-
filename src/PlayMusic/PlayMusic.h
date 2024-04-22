#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QPixmap>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>

#include "interface/IPlayMusic.h"
#include "ui_PlayMusic.h"
#include "playmusic_global.h"

#define		AppPath		QCoreApplication::applicationDirPath()

#define		SingerFile    "/../res/��������/"

#define     AudioMusicFile	"/../res/��Ƶ��Դ/"

class PlayMusic
	: public QWidget
	, public IPlayMusic
{
	Q_OBJECT

public:
	PlayMusic(QWidget *parent = nullptr);
	~PlayMusic();

	virtual QWidget* GetWidget() override;

	virtual void SetPlayMusic(const std::vector<QString>& _musicInfo) override;

private:

	void InitGui();

	void InitConnect();

	void SetPlayInterface();

private:
	Ui::PlayMusicClass ui;

	// ����������
	QMediaPlayer* player_ = new QMediaPlayer;

	// ������Ƶ·��
	QString		audioFilePath;

	// ������Ƶʱ�� ��λ��s
	int			time_ = 0;

	// ��ʱ��
	QTimer*		timer_ = new QTimer;

	// ��������ǰ����
	int        progress_ = 0;

};
