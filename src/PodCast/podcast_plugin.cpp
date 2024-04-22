#include "podcast_plugin.h"
#include "PodCast.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

PodCastPlugin::PodCastPlugin(QObject* parent)
	: QObject(parent) 
{

}

PodCastPlugin::~PodCastPlugin()
{

}

void PodCastPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IPodCastSPtr podCast_ptr = std::make_shared<PodCast>();
	global_module_linker_->SetServicePtrById(PODCASTSERVICEID, podCast_ptr);
}

void PodCastPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}