#include "local_and_download_plugin.h"
#include "LocalAndDownload.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

LocalAndDownloadPlugin::LocalAndDownloadPlugin(QObject* parent)
	: QObject(parent) 
{

}

LocalAndDownloadPlugin::~LocalAndDownloadPlugin()
{

}

void LocalAndDownloadPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	ILocalAndDownloadSPtr local_ptr = std::make_shared<LocalAndDownload>();
	global_module_linker_->SetServicePtrById(LOCALANDDOWNLOADSERVICEID, local_ptr);
}

void LocalAndDownloadPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}