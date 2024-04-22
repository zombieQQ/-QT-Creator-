#include "live_plugin.h"
#include "LiveBroadcastService.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

LivePlugin::LivePlugin(QObject* parent)
	: QObject(parent) 
{

}

LivePlugin::~LivePlugin()
{

}

void LivePlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	ILiveBroadcastSPtr liveBroadcastPtr = std::make_shared<LiveBroadcastService>();
	global_module_linker_->SetServicePtrById(ILIVEBROADCASTSERVICEID, liveBroadcastPtr);
}

void LivePlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}