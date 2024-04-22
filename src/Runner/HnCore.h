#pragma once

#include "AbstractPlugin.h"

#include <iostream>
#include <vector>
#include <qlibrary.h>
#include <qpluginloader.h>
#include <memory>

#include "logger_factory.h"

typedef IModuleLinker* (*CreatePlugin)();

class HnCore
{
public:
	static HnCore* GetInstance();

	~HnCore();

	// 加载动态库
	void LoadLibraryByPath(std::string _path, std::string _function_name);

	// 加载组件库
	void LoadPluginByPath(std::string _path);

	// 注册所有组件库的服务
	void RegisterAllServices();

	// 注册HnCore的服务
	void RegisterHnCoreServices();

	// 获取组件库需要的服务
	void GetAllRequiredServices();

public:
	ModuleLinkerSPtr module_linker_;

private:
	static HnCore* instance_;

	// 私有的构造函数，防止外部实例化
	HnCore();

	IModuleLinker* module_linker_temp_;

	std::vector<AbstractPlugin*> plugin_ptrs_;

	LoggerFactorySPtr	global_log_factory_;
};