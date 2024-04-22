#pragma once

#include <QObject>
#include <iostream>
#include <memory>

#include "IModuleLinker.h"

class AbstractPlugin
{
public:
	virtual ~AbstractPlugin() = default;

	// ע�����
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) = 0;

	// ��ȡ����
	virtual void StartPlugin() = 0;
};

#define AbstractInterface_lid "com.Plugin.AbstractPlugin"

Q_DECLARE_INTERFACE(AbstractPlugin, AbstractInterface_lid);