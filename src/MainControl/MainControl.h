#pragma once

/*!
 * \file        MainControl.h
 * \date        2023/10/29 14:38
 * \author      张惠楠
 * \brief       主界面
 * \note        😁
*/

#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <unordered_map>
#include <qstring.h>
#include <qscrollarea.h>
#include <QScrollBar>
#include <stack>

#include "ui_MainControl.h"
#include "main_control_global.h"
#include "interface/IMainControl.h"
#include "CustomTitleBar.h"
#include "recommend_song_list.h"
#include "exclusive_custom.h"
#include "SongLists.h"
#include "RankList.h"
#include "Singer.h"
#include "BestNewMusic.h"
#include "RecommendSong.h"

// 左侧导航栏按钮qss文件
#define     LeftBtnBarQss   "/../src/MainControl/left_bar_btn.qss"

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/MainControl/scroll_area.qss"

class MainControl 
    : public QMainWindow
    , public IMainControl
{
    Q_OBJECT

public:
    MainControl(QWidget *parent = nullptr);
    ~MainControl();

    virtual void MainControlWidgetShow() override;

    virtual void SetPlayMusicPng(const bool& _flag) override;

private slots:

    // 左侧导航栏按钮点击事件
    void SlotLeftBarClicked(QAbstractButton* _btn);

private:

    // 初始化Ui
    void InitUi();

    // 初始化连接
    void InitConnect();

    // 打开qss文件
    QString OpenQssFile(std::string _qssFile);

    // 设置qss
    void SettingQss(QString _qss);

    // 发现音乐
    void FindMusic();

    // 播客
    void PodCastWidget();

    // 关注
    void FollowWithWidget();

    // 视频
    void VideoWidget();

    // 直播
    void LiveWidget();

    // 私人漫游
    void PrivateRoamingWidget();

    // 个性推荐widget
    void PersonalRecommendTabWidget();

    // 专属订制widget
    void ExclusiveCustomWidget();

    // 歌单widget
    void SongListsWidget();

    // 排行榜
    void RankListWidget();

    // 歌手
    void SingerWidget();

    // 最新音乐
    void BestNewMusicWidget();

    // 我喜欢的音乐
    void MyLikeMusicWidget();

    // 本地与下载
    void LocalAndDownloadWidget();

    // 最近播放
    void RecentlyPlayedWidget();

    // 播放音乐
    void PlayMusicWidget();

    // 我的音乐云盘
    void MyCloudDiskWidget();

    // 我的播客
    void MyPodcastWidget();

    // 我的收藏
    void MyFavoritesWidget();

private:

    Ui::MainControlClass ui;

    CustomTitleBar*         customTitleBar_;                // 自定义标题栏

    QButtonGroup*           left_bar_btn_group_;             // 管理所有左侧导航栏按钮

    // <左侧导航栏按钮的objectname, stackwidget的索引>
    std::unordered_map<std::string, int>    object_name_idx_;   // 左侧导航栏按钮的objectname与stackedwidget的索引

    // 个性推荐
    std::shared_ptr<RecommendSongList>      recommend_song_list_;

    // 专属订制
    std::shared_ptr<ExclusiveCustom>        exclusive_custom_;

    // 歌单
    std::shared_ptr<SongLists>              song_lists_;

    // 排行榜
    std::shared_ptr<RankList>               rank_list_;

    // 歌手
    std::shared_ptr<Singer>                 singer_;

    // 最新音乐
    std::shared_ptr<BestNewMusic>           best_new_music_;

    std::shared_ptr<RecommendSong>          recommend_song_;

    std::stack<int> back_;

    std::stack<int> forward_;
};
