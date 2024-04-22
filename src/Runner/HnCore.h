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

	// ���ض�̬��
	void LoadLibraryByPath(std::string _path, std::string _function_name);

	// ���������
	void LoadPluginByPath(std::string _path);

	// ע�����������ķ���
	void RegisterAllServices();

	// ע��HnCore�ķ���
	void RegisterHnCoreServices();

	// ��ȡ�������Ҫ�ķ���
	void GetAllRequiredServices();

public:
	ModuleLinkerSPtr module_linker_;

private:
	static HnCore* instance_;

	// ˽�еĹ��캯������ֹ�ⲿʵ����
	HnCore();

	IModuleLinker* module_linker_temp_;

	std::vector<AbstractPlugin*> plugin_ptrs_;

	LoggerFactorySPtr	global_log_factory_;
};