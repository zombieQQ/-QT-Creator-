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

// ���ض�̬��
void HnCore::LoadLibraryByPath(std::string _path, std::string _function_name)
{
	QLibrary plugin(_path.c_str());

	if (!plugin.load())
	{
		std::string source = "HnCore.cpp: " + std::to_string(__LINE__);
		global_log_factory_->LogCriticalMsg(source, "��̬�����ʧ��");
		return;
	}

	// ���� createPlugin ����
	CreatePlugin obj = reinterpret_cast<CreatePlugin>(plugin.resolve(_function_name.c_str()));
	if (!obj)
	{
		std::string source = "HnCore.cpp: " + __LINE__;
		global_log_factory_->LogCriticalMsg(source, "���ż���ʧ��");
		return;
	}
	module_linker_temp_ = obj();

	module_linker_ = std::shared_ptr<IModuleLinker>(module_linker_temp_);

	RegisterHnCoreServices();
}

// ���������
void HnCore::LoadPluginByPath(std::string _path)
{
	QPluginLoader loader(_path.c_str());
	if (!loader.load())
	{
		qDebug() << "��������ʧ��";
	}

	QObject* plugin = loader.instance();
	AbstractPlugin* pinterface = qobject_cast<AbstractPlugin*>(plugin);

	plugin_ptrs_.push_back(pinterface);
}

// ע�����������ķ���
void HnCore::RegisterAllServices()
{
	for (int i = 0; i < plugin_ptrs_.size(); i++)
		plugin_ptrs_[i]->InitPlugin(module_linker_);
}

// ע��HnCore�ķ���
void HnCore::RegisterHnCoreServices()
{
	module_linker_->SetServicePtrById(LOGGERFACTORYSERVICEID, global_log_factory_);
}

// ��ȡ�������Ҫ�ķ���
void HnCore::GetAllRequiredServices()
{
	for (int i = 0; i < plugin_ptrs_.size(); i++)
		plugin_ptrs_[i]->StartPlugin();
}