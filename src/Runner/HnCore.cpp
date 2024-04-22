#include "HnCore.h"

#include <qdebug.h>

HnCore* HnCore::instance_ = nullptr;

HnCore::HnCore()
{
	module_linker_temp_ = nullptr;

	global_log_factory_ = std::make_shared<LoggerFactory>();
}

HnCore::~HnCore()
{

}

HnCore* HnCore::GetInstance()
{
	if (nullptr == instance_)
		instance_ = new HnCore();

	return instance_;
}

// 加载动态库
void HnCore::LoadLibraryByPath(std::string _path, std::string _function_name)
{
	QLibrary plugin(_path.c_str());

	if (!plugin.load())
	{
		std::string source = "HnCore.cpp: " + std::to_string(__LINE__);
		global_log_factory_->LogCriticalMsg(source, "动态库加载失败");
		return;
	}

	// 解析 createPlugin 符号
	CreatePlugin obj = reinterpret_cast<CreatePlugin>(plugin.resolve(_function_name.c_str()));
	if (!obj)
	{
		std::string source = "HnCore.cpp: " + __LINE__;
		global_log_factory_->LogCriticalMsg(source, "符号加载失败");
		return;
	}
	module_linker_temp_ = obj();

	module_linker_ = std::shared_ptr<IModuleLinker>(module_linker_temp_);

	RegisterHnCoreServices();
}

// 加载组件库
void HnCore::LoadPluginByPath(std::string _path)
{
	QPluginLoader loader(_path.c_str());
	if (!loader.load())
	{
		qDebug() << "组件库加载失败";
	}

	QObject* plugin = loader.instance();
	AbstractPlugin* pinterface = qobject_cast<AbstractPlugin*>(plugin);

	plugin_ptrs_.push_back(pinterface);
}

// 注册所有组件库的服务
void HnCore::RegisterAllServices()
{
	for (int i = 0; i < plugin_ptrs_.size(); i++)
		plugin_ptrs_[i]->InitPlugin(module_linker_);
}

// 注册HnCore的服务
void HnCore::RegisterHnCoreServices()
{
	module_linker_->SetServicePtrById(LOGGERFACTORYSERVICEID, global_log_factory_);
}

// 获取组件库需要的服务
void HnCore::GetAllRequiredServices()
{
	for (int i = 0; i < plugin_ptrs_.size(); i++)
		plugin_ptrs_[i]->StartPlugin();
}