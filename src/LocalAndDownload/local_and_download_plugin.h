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

	// ע�����
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// ��ȡ����
	virtual void StartPlugin() override;

private:

};

