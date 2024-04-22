#include "video_plugin.h"
#include "video.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

VideoPlugin::VideoPlugin(QObject* parent)
	: QObject(parent) 
{

}

VideoPlugin::~VideoPlugin() 
{

}

void VideoPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IVideoSPtr video_ptr = std::make_shared<video>();
	global_module_linker_->SetServicePtrById(VIDEOSERVICEID, video_ptr);
}

void VideoPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}