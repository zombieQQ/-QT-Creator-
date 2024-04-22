#pragma once

#include "IModuleLinker.h"

#include <unordered_map>
#include <iostream>

class ModuleLinkerService
	: public IModuleLinker
{
public:
	ModuleLinkerService();

	~ModuleLinkerService();

	// 通过id存放服务指针
	virtual void SetServicePtrById(std::string, IServiceBaseSPtr) override;

	// 通过id获取服务指针
	virtual IServiceBaseSPtr GetServicePtrById(std::string) override;

	virtual int Size() override;

private:
	std::unordered_map<std::string, IServiceBaseSPtr> module_ptr_;
};
