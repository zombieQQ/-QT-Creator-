#include "MainControl.h"

MainControl::MainControl(QWidget *parent)
    : QMainWindow(parent)
    , left_bar_btn_group_(new QButtonGroup)
    , recommend_song_list_(std::make_shared<RecommendSongList>())
    , exclusive_custom_(std::make_shared<ExclusiveCustom>())
    , song_lists_(std::make_shared<SongLists>())
    , rank_list_(std::make_shared<RankList>())
    , singer_(std::make_shared<Singer>())
    , best_new_music_(std::make_shared<BestNewMusic>())
    , recommend_song_(std::make_shared<RecommendSong>())
{
    ui.setupUi(this);

    InitUi();

    InitConnect();
}

MainControl::~MainControl()
{}

void MainControl::MainControlWidgetShow()
{
    FindMusic();

    PodCastWidget();

    VideoWidget();

    FollowWithWidget();

    LiveWidget();

    PrivateRoamingWidget();

    MyLikeMusicWidget();

    LocalAndDownloadWidget();

    RecentlyPlayedWidget();

    MyCloudDiskWidget();

    MyFavoritesWidget();

    MyPodcastWidget();

    PlayMusicWidget();

    //global_rotation_chart_->StartRotationChartTimer();

    this->show();
}

void MainControl::SetPlayMusicPng(const bool& _flag)
{
    recommend_song_->SetPlayMusicPng(_flag);
}

// 初始化Ui
void MainControl::InitUi()
{
    // 隐藏原始标题栏
    setWindowFlags(Qt::FramelessWindowHint);

    customTitleBar_ = new CustomTitleBar(this);

    // 设置自定义标题栏
    setMenuWidget(customTitleBar_);

    // 打开默认的Qss文件
    QString qss = OpenQssFile(LeftBtnBarQss);

    SettingQss(qss);

    // ------------把左侧导航栏的按钮放到group里管理------------
    left_bar_btn_group_->addButton(ui.btn_find_music_, 0);
    left_bar_btn_group_->addButton(ui.btn_podcast_, 1);
    left_bar_btn_group_->addButton(ui.btn_video_, 2);
    left_bar_btn_group_->addButton(ui.btn_follow_, 3);
    left_bar_btn_group_->addButton(ui.btn_seeding_, 4);
    left_bar_btn_group_->addButton(ui.btn_roaming_, 5);
    left_bar_btn_group_->addButton(ui.btn_like_, 6);
    left_bar_btn_group_->addButton(ui.btn_local_, 7);
    left_bar_btn_group_->addButton(ui.btn_recently_, 8);
    left_bar_btn_group_->addButton(ui.btn_cloud_disk_, 9);
    left_bar_btn_group_->addButton(ui.btn_my_podcast_, 10);
    left_bar_btn_group_->addButton(ui.btn_collection_, 11);

    // 设置索引
    object_name_idx_[QString2StdString(ui.btn_find_music_->objectName())] = 0.;
    object_name_idx_[QString2StdString(ui.btn_podcast_->objectName())] = 1;
    object_name_idx_[QString2StdString(ui.btn_video_->objectName())] = 2;
    object_name_idx_[QString2StdString(ui.btn_follow_->objectName())] = 3;
    object_name_idx_[QString2StdString(ui.btn_seeding_->objectName())] = 4;
    object_name_idx_[QString2StdString(ui.btn_roaming_->objectName())] = 5;
    object_name_idx_[QString2StdString(ui.btn_like_->objectName())] = 6;
    object_name_idx_[QString2StdString(ui.btn_local_->objectName())] = 7;
    object_name_idx_[QString2StdString(ui.btn_recently_->objectName())] = 8;
    object_name_idx_[QString2StdString(ui.btn_cloud_disk_->objectName())] = 9;
    object_name_idx_[QString2StdString(ui.btn_my_podcast_->objectName())] = 10;
    object_name_idx_[QString2StdString(ui.btn_collection_->objectName())] = 11;

    // 设置为单选按钮，意味着每次只能有一个按钮被选中
    left_bar_btn_group_->setExclusive(true);

    connect(left_bar_btn_group_, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &MainControl::SlotLeftBarClicked);
    // ---------------------------------------------------------

    // 初始让“发现音乐”按钮选中
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(left_bar_btn_group_->button(0));
    clickedBtn->setChecked(true);

    back_.push(0);

    // 水平布局
    QHBoxLayout* herLayout = new QHBoxLayout;
    herLayout->addWidget(ui.scrollArea);
    herLayout->addWidget(ui.stackedWidget);

    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(customTitleBar_);
    mainLayout->addLayout(herLayout);

}

void MainControl::InitConnect()
{
    connect(recommend_song_list_.get(), &RecommendSongList::SignalRecommendBtnClicked, [=]() {
        ui.stackedWidget->addWidget(recommend_song_.get());

        ui.stackedWidget->setCurrentWidget(recommend_song_.get());
    });

    connect(customTitleBar_, &CustomTitleBar::SignalForwardAndBackWard, [=](const bool& _flag) {
        
        if (_flag)
        {
            if (back_.size() == 0 || back_.size() == 1)
                return;

            forward_.push(back_.top());

            back_.pop();

            ui.stackedWidget->setCurrentIndex(back_.top());

			QPushButton* clickedBtn = qobject_cast<QPushButton*>(left_bar_btn_group_->button(back_.top()));
			clickedBtn->setChecked(true);
        }
        else
        {
            if (forward_.size() == 0)
                return;

            ui.stackedWidget->setCurrentIndex(forward_.top());

			QPushButton* clickedBtn = qobject_cast<QPushButton*>(left_bar_btn_group_->button(forward_.top()));
			clickedBtn->setChecked(true);

            back_.push(forward_.top());

            forward_.pop();
        }
    });
}

// 打开Qss文件
QString MainControl::OpenQssFile(std::string _qssFile)
{
    QString filePath = AppPath + StdString2QString(_qssFile);
    QFile qssFile(filePath);
    if (!qssFile.open(QFile::ReadOnly | QFile::Text))
        return "";

    QString qss = StdString2QString(qssFile.readAll());

    qssFile.close();

    return qss;
}

// 设置qss
void MainControl::SettingQss(QString _qss)
{
    ui.btn_find_music_->setStyleSheet(_qss);
    ui.btn_podcast_->setStyleSheet(_qss);
    ui.btn_video_->setStyleSheet(_qss);
    ui.btn_follow_->setStyleSheet(_qss);
    ui.btn_seeding_->setStyleSheet(_qss);
    ui.btn_roaming_->setStyleSheet(_qss);

    ui.btn_like_->setStyleSheet(_qss);
    ui.btn_local_->setStyleSheet(_qss);
    ui.btn_recently_->setStyleSheet(_qss);
    ui.btn_cloud_disk_->setStyleSheet(_qss);
    ui.btn_my_podcast_->setStyleSheet(_qss);
    ui.btn_collection_->setStyleSheet(_qss);
}

void MainControl::FindMusic()
{
	// 个性推荐
	PersonalRecommendTabWidget();

	// 专属订制
	ExclusiveCustomWidget();

	// 歌单
	SongListsWidget();

	// 排行榜
	RankListWidget();

	// 歌手
	SingerWidget();

	// 最新音乐
	BestNewMusicWidget();
}

void MainControl::PodCastWidget()
{
    if (global_pod_cast_widget_)
        ui.stackedWidget->addWidget(global_pod_cast_widget_->GetWidget());
}

void MainControl::FollowWithWidget()
{
    if (global_follow_with_widget_)
        ui.stackedWidget->addWidget(global_follow_with_widget_->GetWidget());
}

void MainControl::VideoWidget()
{
    if (global_video_widget_)
        ui.stackedWidget->addWidget(global_video_widget_->GetVideoWidget());
}

void MainControl::LiveWidget()
{
    if (global_live_widget_)
        ui.stackedWidget->addWidget(global_live_widget_->GetLiveWidget());
}

void MainControl::PrivateRoamingWidget()
{
    if (global_private_roaming_)
        ui.stackedWidget->addWidget(global_private_roaming_->GetWidget());
}

void MainControl::MyLikeMusicWidget()
{
	if (global_like_music_)
		ui.stackedWidget->addWidget(global_like_music_->GetWidget());
}

void MainControl::LocalAndDownloadWidget()
{
    if (global_local_and_download_)
        ui.stackedWidget->addWidget(global_local_and_download_->GetWidget());
}

void MainControl::RecentlyPlayedWidget()
{
    if (global_recently_played_)
        ui.stackedWidget->addWidget(global_recently_played_->GetWidget());
}

void MainControl::PlayMusicWidget()
{
	// 播放音乐
	QVBoxLayout* playMusicLayout = new QVBoxLayout;
	ui.playMusicWidget->setLayout(playMusicLayout);
	playMusicLayout->setMargin(0);
	playMusicLayout->setContentsMargins(0, 0, 0, 0);

	playMusicLayout->addWidget(global_play_music_->GetWidget());
}

void MainControl::MyCloudDiskWidget()
{
    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLabel* label = new QLabel;
    QPixmap pixmap(AppPath + StdString2QString("/../res/私人漫游/1.png"));

    label->setPixmap(pixmap);
    layout->addWidget(label);

    layout->setAlignment(label, Qt::AlignCenter);

    ui.stackedWidget->addWidget(widget);
}

void MainControl::MyPodcastWidget()
{
	QWidget* widget = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout(widget);

	QLabel* label = new QLabel;
	QPixmap pixmap(AppPath + StdString2QString("/../res/私人漫游/1.png"));

	label->setPixmap(pixmap);
	layout->addWidget(label);

	layout->setAlignment(label, Qt::AlignCenter);

	ui.stackedWidget->addWidget(widget);
}

void MainControl::MyFavoritesWidget()
{
	QWidget* widget = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout(widget);

	QLabel* label = new QLabel;
	QPixmap pixmap(AppPath + StdString2QString("/../res/私人漫游/1.png"));

	label->setPixmap(pixmap);
	layout->addWidget(label);

	layout->setAlignment(label, Qt::AlignCenter);

	ui.stackedWidget->addWidget(widget);
}

// 左侧导航栏按钮点击事件
void MainControl::SlotLeftBarClicked(QAbstractButton* _btn)
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(_btn);

    ui.stackedWidget->setCurrentIndex(object_name_idx_[QString2StdString(clickedBtn->objectName())]);

    back_.push(object_name_idx_[QString2StdString(clickedBtn->objectName())]);
}

// 个性推荐widget
void MainControl::PersonalRecommendTabWidget()
{
    QWidget* recommendWidget = ui.tab_widget_find_music_->widget(0);

    // 垂直布局
    QVBoxLayout* recommendLayout = new QVBoxLayout(recommendWidget);
    recommendLayout->setContentsMargins(0, 0, 0, 0);
    recommendLayout->setSpacing(0);

    QScrollArea* scrollArea = new QScrollArea;
    QScrollBar* verticalScrollBar = scrollArea->verticalScrollBar();

    QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);  // 设置滚动区域自动调整大小

	// 创建一个内部的小部件，放置在滚动区域中
	QWidget* contentWidget = new QWidget(scrollArea);
	QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    // 添加轮播图
    contentLayout->addWidget(global_rotation_chart_->RotationChartShow());

    // 推荐歌单
    contentLayout->addWidget(recommend_song_list_.get());

	// 设置滚动区域的小部件
	scrollArea->setWidget(contentWidget);

    recommendLayout->addWidget(scrollArea);
}

void MainControl::ExclusiveCustomWidget()
{
    QWidget* exclCusWidget = ui.tab_widget_find_music_->widget(1);

	// 垂直布局
	QVBoxLayout* exclCusLayout = new QVBoxLayout(exclCusWidget);
    exclCusLayout->setContentsMargins(0, 0, 0, 0);
    exclCusLayout->setSpacing(0);

	QScrollArea* scrollArea = new QScrollArea;
	QScrollBar* verticalScrollBar = scrollArea->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setWidgetResizable(true);  // 设置滚动区域自动调整大小

	// 创建一个内部的小部件，放置在滚动区域中
	QWidget* contentWidget = new QWidget(scrollArea);
	QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);

    contentLayout->addWidget(exclusive_custom_.get());

	// 设置滚动区域的小部件
	scrollArea->setWidget(contentWidget);

    exclCusLayout->addWidget(scrollArea);
}

void MainControl::SongListsWidget()
{
	QWidget* songListsWidget = ui.tab_widget_find_music_->widget(2);

	// 垂直布局
	QVBoxLayout* songListLayout = new QVBoxLayout(songListsWidget);
	songListLayout->setContentsMargins(0, 0, 0, 0);
	songListLayout->setSpacing(0);

    songListLayout->addWidget(song_lists_->GetWidget());
}

void MainControl::RankListWidget()
{
	QWidget* songListsWidget = ui.tab_widget_find_music_->widget(3);

	// 垂直布局
	QVBoxLayout* songListLayout = new QVBoxLayout(songListsWidget);
	songListLayout->setContentsMargins(0, 0, 0, 0);
	songListLayout->setSpacing(0);

	songListLayout->addWidget(rank_list_->GetWidget());
}

void MainControl::SingerWidget()
{
	QWidget* singerWidget = ui.tab_widget_find_music_->widget(4);

	// 垂直布局
	QVBoxLayout* singerLayout = new QVBoxLayout(singerWidget);
    singerLayout->setContentsMargins(0, 0, 0, 0);
    singerLayout->setSpacing(0);

    singerLayout->addWidget(singer_->GetWidget());
}

void MainControl::BestNewMusicWidget()
{
	QWidget* newMusicWidget = ui.tab_widget_find_music_->widget(5);

	// 垂直布局
	QVBoxLayout* newMusicLayout = new QVBoxLayout(newMusicWidget);
    newMusicLayout->setContentsMargins(0, 0, 0, 0);
    newMusicLayout->setSpacing(0);

    newMusicLayout->addWidget(best_new_music_->GetWidget());
}
