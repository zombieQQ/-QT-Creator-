#include "main_control_plugin.h"
#include "MainControl.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;
RotationChartSPtr				global_rotation_chart_ = nullptr;
IGuiFactorySPtr					global_gui_factory_ = nullptr;
IVideoSPtr						global_video_widget_ = nullptr;
ILiveBroadcastSPtr				global_live_widget_ = nullptr;
IPodCastSPtr					global_pod_cast_widget_ = nullptr;
IFollowWithSPtr					global_follow_with_widget_ = nullptr;
IMyLikeMusicSPtr				global_like_music_ = nullptr;
ILocalAndDownloadSPtr			global_local_and_download_ = nullptr;
IRecentlyPlayedSPtr				global_recently_played_ = nullptr;
IPrivateRoamingSPtr				global_private_roaming_ = nullptr;
IPlayMusicSPtr					global_play_music_ = nullptr;
std::shared_ptr<Peeling>		global_peeling_widget_ = nullptr;
std::shared_ptr<CustomTitleBar>	global_custom_widget_ = nullptr;

MainControlPlugin::MainControlPlugin(QObject* parent)
	: QObject(parent) {

}

MainControlPlugin::~MainControlPlugin() {

}

void MainControlPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	MainControlSPtr main_control_ptr = std::make_shared<MainControl>();
	global_module_linker_->SetServicePtrById(MAINCONTROLSERVICEID, main_control_ptr);
}

void MainControlPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	global_rotation_chart_ = Service(IRotationChart, ROTATIONCHARTSERVICEID, global_module_linker_);
	global_gui_factory_ = Service(IGuiFactory, IGUIFACTORYSERVICEID, global_module_linker_);
	global_video_widget_ = Service(IVideo, VIDEOSERVICEID, global_module_linker_);
	global_live_widget_ = Service(ILiveBroadcast, ILIVEBROADCASTSERVICEID, global_module_linker_);
	global_pod_cast_widget_ = Service(IPodCast, PODCASTSERVICEID, global_module_linker_);
	global_follow_with_widget_ = Service(IFollowWith, FOLLOWWITHSERVICEID, global_module_linker_);
	global_like_music_ = Service(IMyLikeMusic, MYLIKEMUSICSERVICEID, global_module_linker_);
	global_local_and_download_ = Service(ILocalAndDownload, LOCALANDDOWNLOADSERVICEID, global_module_linker_);
	global_recently_played_ = Service(IRecentlyPlayed, IRECENTLYPLAYEDSERVICEID, global_module_linker_);
	global_private_roaming_ = Service(IPrivateRoaming, IPRIVATEROAMINGSERVICEID, global_module_linker_);
	global_play_music_ = Service(IPlayMusic, IPLAYMUSICSERVICEID, global_module_linker_);

	global_peeling_widget_ = std::make_shared<Peeling>();
	global_custom_widget_ = std::make_shared<CustomTitleBar>();

	return;
}