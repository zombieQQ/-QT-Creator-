#include "playmusic_plugin.h"
#include "PlayMusic.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;
MainControlSPtr					global_main_control_ = nullptr;

PlayMusicPlugin::PlayMusicPlugin(QObject* parent)
	: QObject(parent) 
{

}

PlayMusicPlugin::~PlayMusicPlugin()
{

}

void PlayMusicPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IPlayMusicSPtr playMusicSPtr = std::make_shared<PlayMusic>();
	global_module_linker_->SetServicePtrById(IPLAYMUSICSERVICEID, playMusicSPtr);
}

void PlayMusicPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	global_main_control_ = Service(IMainControl, MAINCONTROLSERVICEID, global_module_linker_);

	return;
}