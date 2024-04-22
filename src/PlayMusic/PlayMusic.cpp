#include "PlayMusic.h"

PlayMusic::PlayMusic(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 定时器步长为1s
	timer_->setInterval(1000);

	InitGui();

	InitConnect();
}

PlayMusic::~PlayMusic()
{}

QWidget* PlayMusic::GetWidget()
{
	return this;
}

void PlayMusic::SetPlayMusic(const std::vector<QString>& _musicInfo)
{
	QPixmap pixmap(AppPath + StdString2QString(SingerFile) + _musicInfo[0] + ".png");
	ui.headLabel->setPixmap(pixmap);

	ui.songName->setText(_musicInfo[0]);
	ui.singerName->setText(_musicInfo[1]);
	ui.endTime->setText(_musicInfo[2]);

	SetPlayInterface();
	ui.playMusicBtn->setChecked(true);

	audioFilePath = AppPath + StdString2QString(AudioMusicFile) + _musicInfo[0] + ".mp3";

	// 加载音频文件
	player_->setMedia(QUrl::fromLocalFile(audioFilePath));

	progress_ = 0;

	timer_->start();
	player_->play();
}

void PlayMusic::InitGui()
{
	ui.headLabel->setVisible(false);
	ui.songName->setVisible(false);
	ui.singerName->setVisible(false);

	ui.endTime->setVisible(false);
	ui.startTime->setVisible(false);
	ui.likeBtn->setVisible(false);

	ui.playMusicBtn->setEnabled(false);
	ui.lastMusicBtn->setEnabled(false);
	ui.nextMusicBtn->setEnabled(false);
}

void PlayMusic::InitConnect()
{
	connect(ui.playMusicBtn, &QPushButton::clicked, this, [=]() 
	{
		if (ui.playMusicBtn->isChecked())
		{
			global_main_control_->SetPlayMusicPng(true);

			timer_->start();
			player_->play();
		}
		else
		{
			global_main_control_->SetPlayMusicPng(false);

			player_->pause();
			timer_->stop();
		}
	
	});

	connect(timer_, &QTimer::timeout, this, [=]() {
		progress_ += 1;

		ui.progressBar->setValue(progress_);

		// 转换时间
		int second = progress_ % 60;
		int minute = progress_ / 60;

		QString minuteStr, secondStr;

		if (QString::number(minute).size() == 1)
			minuteStr = "0";

		if (QString::number(second).size() == 1)
			secondStr = "0";

		QString currentTime = minuteStr + QString::number(minute) + ":" + secondStr + QString::number(second);
		ui.startTime->setText(currentTime);

		if (progress_ >= time_)
		{
			progress_ = 0;
			timer_->stop();
		}
	});

	connect(player_, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
		if (status == QMediaPlayer::BufferedMedia) 
		{
			// 获取音频总时长
			time_ = player_->duration() / 1000;

			// 设置进度条范围
			ui.progressBar->setRange(0, time_);
			ui.progressBar->setValue(0);

			return;
		}
	});
}

void PlayMusic::SetPlayInterface()
{
	ui.headLabel->setVisible(true);
	ui.songName->setVisible(true);
	ui.singerName->setVisible(true);

	ui.endTime->setVisible(true);
	ui.startTime->setVisible(true);
	ui.likeBtn->setVisible(true);

	ui.playMusicBtn->setEnabled(true);
	ui.lastMusicBtn->setEnabled(true);
	ui.nextMusicBtn->setEnabled(true);
}
