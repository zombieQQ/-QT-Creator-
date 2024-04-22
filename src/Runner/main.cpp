#include "HnCore.h"
#include "interface/IMainControl.h"

#include <QtWidgets/QApplication>
#include <qdebug.h>

// 区分当前是Debug还是Release环境
#ifndef NDEBUG
#define LibraryDir "../../bin_x64_Debug/"
#else
#define LibraryDir "../../bin_x64_Release/"
#endif // NDEBUG

#define PluginPath(x) (std::string(LibraryDir) + x)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 获取HnCore对象
    HnCore* hn_core = HnCore::GetInstance();
    if (!hn_core)
        qDebug() << "[error][main.cpp]: 获取HnCore对象失败";

    // 加载模块管理动态库
    hn_core->LoadLibraryByPath(PluginPath("HnCore/ModuleLinker.dll"), "CreateModuleLinkerObj");
    // ---------------------------开始加载组件-----------------------------
    
    // 主界面组件
    hn_core->LoadPluginByPath(PluginPath("MainControl/MainControl.dll"));

    // 轮播图组件
    hn_core->LoadPluginByPath(PluginPath("RotationChart/RotationChart.dll"));

    // Gui组件
    hn_core->LoadPluginByPath(PluginPath("HnGui/HnGui.dll"));

    // 播客界面
    hn_core->LoadPluginByPath(PluginPath("PodCast/PodCast.dll"));

    // 关注界面
    hn_core->LoadPluginByPath(PluginPath("FollowWith/FollowWith.dll"));

    // 视频界面
    hn_core->LoadPluginByPath(PluginPath("Video/Video.dll"));

	// 直播界面
	hn_core->LoadPluginByPath(PluginPath("LiveBroadcast/LiveBroadcast.dll"));

    // 私人漫游
    hn_core->LoadPluginByPath(PluginPath("PrivateRoaming/PrivateRoaming.dll"));

    // 我喜欢的音乐
    hn_core->LoadPluginByPath(PluginPath("MyLikeMusic/MyLikeMusic.dll"));

    // 本地与下载
    hn_core->LoadPluginByPath(PluginPath("LocalAndDownload/LocalAndDownload.dll"));

    // 最近播放
    hn_core->LoadPluginByPath(PluginPath("RecentlyPlayed/RecentlyPlayed.dll"));

    // 播放音乐
    hn_core->LoadPluginByPath(PluginPath("PlayMusic/PlayMusic.dll"));

    // ---------------------------组件加载完成-----------------------------
    // 注册所有组件库的服务
    hn_core->RegisterAllServices();
    // 获取组件库需要的服务
    hn_core->GetAllRequiredServices();

    MainControlSPtr main = nullptr;

    if (hn_core)
        main = Service(IMainControl, MAINCONTROLSERVICEID, hn_core->module_linker_);

    main->MainControlWidgetShow();

    return a.exec();
}
