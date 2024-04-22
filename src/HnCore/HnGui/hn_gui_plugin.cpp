#include "hn_gui_plugin.h"
#include "GuiFactory.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

HnGuiPlugin::HnGuiPlugin(QObject* parent)
	: QObject(parent) 
{

}

HnGuiPlugin::~HnGuiPlugin() {

}

void HnGuiPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	IGuiFactorySPtr guiFactory = std::make_shared<GuiFactory>();
	global_module_linker_->SetServicePtrById(IGUIFACTORYSERVICEID, guiFactory);
}

void HnGuiPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}