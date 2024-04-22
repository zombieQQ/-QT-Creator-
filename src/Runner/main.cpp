#include "HnCore.h"
#include "interface/IMainControl.h"

#include <QtWidgets/QApplication>
#include <qdebug.h>

// ���ֵ�ǰ��Debug����Release����
#ifndef NDEBUG
#define LibraryDir "../../bin_x64_Debug/"
#else
#define LibraryDir "../../bin_x64_Release/"
#endif // NDEBUG

#define PluginPath(x) (std::string(LibraryDir) + x)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ��ȡHnCore����
    HnCore* hn_core = HnCore::GetInstance();
    if (!hn_core)
        qDebug() << "[error][main.cpp]: ��ȡHnCore����ʧ��";

    // ����ģ�����̬��
    hn_core->LoadLibraryByPath(PluginPath("HnCore/ModuleLinker.dll"), "CreateModuleLinkerObj");
    // ---------------------------��ʼ�������-----------------------------
    
    // ���������
    hn_core->LoadPluginByPath(PluginPath("MainControl/MainControl.dll"));

    // �ֲ�ͼ���
    hn_core->LoadPluginByPath(PluginPath("RotationChart/RotationChart.dll"));

    // Gui���
    hn_core->LoadPluginByPath(PluginPath("HnGui/HnGui.dll"));

    // ���ͽ���
    hn_core->LoadPluginByPath(PluginPath("PodCast/PodCast.dll"));

    // ��ע����
    hn_core->LoadPluginByPath(PluginPath("FollowWith/FollowWith.dll"));

    // ��Ƶ����
    hn_core->LoadPluginByPath(PluginPath("Video/Video.dll"));

	// ֱ������
	hn_core->LoadPluginByPath(PluginPath("LiveBroadcast/LiveBroadcast.dll"));

    // ˽������
    hn_core->LoadPluginByPath(PluginPath("PrivateRoaming/PrivateRoaming.dll"));

    // ��ϲ��������
    hn_core->LoadPluginByPath(PluginPath("MyLikeMusic/MyLikeMusic.dll"));

    // ����������
    hn_core->LoadPluginByPath(PluginPath("LocalAndDownload/LocalAndDownload.dll"));

    // �������
    hn_core->LoadPluginByPath(PluginPath("RecentlyPlayed/RecentlyPlayed.dll"));

    // ��������
    hn_core->LoadPluginByPath(PluginPath("PlayMusic/PlayMusic.dll"));

    // ---------------------------����������-----------------------------
    // ע�����������ķ���
    hn_core->RegisterAllServices();
    // ��ȡ�������Ҫ�ķ���
    hn_core->GetAllRequiredServices();

    MainControlSPtr main = nullptr;

    if (hn_core)
        main = Service(IMainControl, MAINCONTROLSERVICEID, hn_core->module_linker_);

    main->MainControlWidgetShow();

    return a.exec();
}
