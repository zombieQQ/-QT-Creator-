#pragma once
#include <QtCore/qglobal.h>

#ifdef PLAYMUSIC_LIB
# define PLAYMUSIC_EXPORT Q_DECL_EXPORT
#else
# define PLAYMUSIC_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <iostream>
#include <memory>

#include "public/IModuleLinker.h"

#define AbstractInterface_lid "com.Plugin.AbstractPlugin"

class AbstractPlugin
{
public:
	virtual ~AbstractPlugin() = default;

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) = 0;

	// 获取服务
	virtual void StartPlugin() = 0;
};

Q_DECLARE_INTERFACE(AbstractPlugin, AbstractInterface_lid);

#include "interface/IMainControl.h"

extern	ModuleLinkerSPtr				global_module_linker_;
extern  MainControlSPtr					global_main_control_;