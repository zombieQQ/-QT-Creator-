#include "my_like_music_plugin.h"
#include "MyLikeMusic.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

MyLikeMusicPlugin::MyLikeMusicPlugin(QObject* parent)
	: QObject(parent) 
{

}

MyLikeMusicPlugin::~MyLikeMusicPlugin()
{

}

void MyLikeMusicPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IMyLikeMusicSPtr my_like_music_ptr = std::make_shared<MyLikeMusic>();
	global_module_linker_->SetServicePtrById(MYLIKEMUSICSERVICEID, my_like_music_ptr);
}

void MyLikeMusicPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}