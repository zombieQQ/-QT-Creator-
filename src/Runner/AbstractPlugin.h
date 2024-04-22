#pragma once

#include <QObject>
#include <iostream>
#include <memory>

#include "IModuleLinker.h"

class AbstractPlugin
{
public:
	virtual ~AbstractPlugin() = default;

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) = 0;

	// 获取服务
	virtual void StartPlugin() = 0;
};

#define AbstractInterface_lid "com.Plugin.AbstractPlugin"

Q_DECLARE_INTERFACE(AbstractPlugin, AbstractInterface_lid);