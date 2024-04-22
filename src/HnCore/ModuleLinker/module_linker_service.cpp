#include "module_linker_service.h"

extern "C" MODULELINKER_EXPORT IModuleLinker * CreateModuleLinkerObj()
{
	return new ModuleLinkerService;
}

ModuleLinkerService::ModuleLinkerService()
{

}

ModuleLinkerService::~ModuleLinkerService()
{

}

void ModuleLinkerService::SetServicePtrById(std::string _ID, IServiceBaseSPtr _Ptr)
{
	module_ptr_[_ID] = _Ptr;
}

IServiceBaseSPtr ModuleLinkerService::GetServicePtrById(std::string _ID)
{
	if (module_ptr_.find(_ID) == module_ptr_.end())
		return nullptr;

	return module_ptr_[_ID];
}

int ModuleLinkerService::Size()
{
	return module_ptr_.size();
}