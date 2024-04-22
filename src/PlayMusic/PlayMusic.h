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

#define		SingerFile    "/../res/播放音乐/"

#define     AudioMusicFile	"/../res/音频资源/"

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

	// 播放器对象
	QMediaPlayer* player_ = new QMediaPlayer;

	// 播放音频路径
	QString		audioFilePath;

	// 播放音频时长 单位：s
	int			time_ = 0;

	// 定时器
	QTimer*		timer_ = new QTimer;

	// 进度条当前进度
	int        progress_ = 0;

};
