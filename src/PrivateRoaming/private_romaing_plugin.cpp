#include "private_romaing_plugin.h"
#include "PrivateRoaming.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

PrivateRomaingPlugin::PrivateRomaingPlugin(QObject* parent)
	: QObject(parent) 
{

}

PrivateRomaingPlugin::~PrivateRomaingPlugin()
{

}

void PrivateRomaingPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IPrivateRoamingSPtr privateRoamingPtr = std::make_shared<PrivateRoaming>();
	global_module_linker_->SetServicePtrById(IPRIVATEROAMINGSERVICEID, privateRoamingPtr);
}

void PrivateRomaingPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}