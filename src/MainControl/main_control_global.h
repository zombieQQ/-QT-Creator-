#pragma once

#include <QtCore/qglobal.h>

#ifdef MAINCONTROL_LIB
# define MAINCONTROL_EXPORT Q_DECL_EXPORT
#else
# define MAINCONTROL_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <iostream>
#include <memory>

#include "public/IModuleLinker.h"

#define AbstractInterface_lid "com.Plugin.AbstractPlugin"

class AbstractPlugin
{
public:
	virtual ~AbstractPlugin() = default;

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) = 0;

	// 获取服务
	virtual void StartPlugin() = 0;
};

Q_DECLARE_INTERFACE(AbstractPlugin, AbstractInterface_lid);

#include "interface/IRotationChart.h"
#include "interface/IGuiFactory.h"
#include "interface/IVideo.h"
#include "interface/ILiveBroadcast.h"
#include "interface/IPodCast.h"
#include "interface/IFollowWith.h"
#include "interface/IMyLikeMusic.h"
#include "interface/ILocalAndDownload.h"
#include "interface/IRecentlyPlayed.h"
#include "interface/IPrivateRoaming.h"
#include "interface/IPlayMusic.h"
#include "Peeling.h"

extern	ModuleLinkerSPtr				global_module_linker_;
extern	RotationChartSPtr				global_rotation_chart_;
extern  IGuiFactorySPtr					global_gui_factory_;
extern	IVideoSPtr						global_video_widget_;
extern	ILiveBroadcastSPtr				global_live_widget_;
extern  IPodCastSPtr					global_pod_cast_widget_;
extern  IFollowWithSPtr					global_follow_with_widget_;
extern  IMyLikeMusicSPtr				global_like_music_;
extern  ILocalAndDownloadSPtr			global_local_and_download_;
extern  IRecentlyPlayedSPtr				global_recently_played_;
extern  IPrivateRoamingSPtr				global_private_roaming_;
extern  IPlayMusicSPtr					global_play_music_;
extern  std::shared_ptr<Peeling>		global_peeling_widget_;
