#include "follow_plugin.h"
#include "follow_with.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

FollowPlugin::FollowPlugin(QObject* parent)
	: QObject(parent) 
{

}

FollowPlugin::~FollowPlugin()
{

}

void FollowPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IFollowWithSPtr followWith_ptr = std::make_shared<FollowWith>();
	global_module_linker_->SetServicePtrById(FOLLOWWITHSERVICEID, followWith_ptr);
}

void FollowPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}