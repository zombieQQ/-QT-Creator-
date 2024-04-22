#include "recently_played_plugin.h"
#include "RecentlyPlayed.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

RecentlyPlayedPlugin::RecentlyPlayedPlugin(QObject* parent)
	: QObject(parent) 
{

}

RecentlyPlayedPlugin::~RecentlyPlayedPlugin()
{

}

void RecentlyPlayedPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IRecentlyPlayedSPtr recently_played_ptr = std::make_shared<RecentlyPlayed>();
	global_module_linker_->SetServicePtrById(IRECENTLYPLAYEDSERVICEID, recently_played_ptr);
}

void RecentlyPlayedPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}