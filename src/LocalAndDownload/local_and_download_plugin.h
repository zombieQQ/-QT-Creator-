#pragma once
#include "local_and_download_global.h"

class LocalAndDownloadPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

		Q_PLUGIN_METADATA(IID AbstractInterface_lid)

		Q_INTERFACES(AbstractPlugin)

public:

	LocalAndDownloadPlugin(QObject* parent = Q_NULLPTR);
	~LocalAndDownloadPlugin();

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// 获取服务
	virtual void StartPlugin() override;

private:

};

