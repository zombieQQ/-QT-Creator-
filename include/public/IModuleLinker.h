#pragma once

#include <memory>
#include <iostream>

#include "../../src/HnCore/ModuleLinker/modulelinker_global.h"
#include "IService.h"

#define		ModuleLinkerSPtr	std::shared_ptr<IModuleLinker>
#define		ModuleLinkerWPtr	std::weak_ptr<IModuleLinker>

class MODULELINKER_EXPORT IModuleLinker
{
public:

	virtual ~IModuleLinker() {};

	// 通过id存放服务指针
	virtual void SetServicePtrById(std::string, IServiceBaseSPtr) = 0;

	// 通过id获取服务指针
	virtual IServiceBaseSPtr GetServicePtrById(std::string) = 0;

	virtual int Size() = 0;

private:

};

#define Service(_service_type, _service_id, _context_ptr) std::dynamic_pointer_cast<_service_type, IService>(_context_ptr->GetServicePtrById(_service_id))

extern "C" MODULELINKER_EXPORT IModuleLinker * CreateModuleLinkerObj();