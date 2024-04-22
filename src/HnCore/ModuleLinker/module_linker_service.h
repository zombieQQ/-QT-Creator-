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

	// ͨ��id��ŷ���ָ��
	virtual void SetServicePtrById(std::string, IServiceBaseSPtr) override;

	// ͨ��id��ȡ����ָ��
	virtual IServiceBaseSPtr GetServicePtrById(std::string) override;

	virtual int Size() override;

private:
	std::unordered_map<std::string, IServiceBaseSPtr> module_ptr_;
};
