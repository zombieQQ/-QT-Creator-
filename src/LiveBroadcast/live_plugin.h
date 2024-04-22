#pragma once

#include "live_global.h"

class LivePlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

	Q_PLUGIN_METADATA(IID AbstractInterface_lid)

	Q_INTERFACES(AbstractPlugin)

public:
	LivePlugin(QObject* parent = Q_NULLPTR);
	~LivePlugin();

	// ע�����
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// ��ȡ����
	virtual void StartPlugin() override;

private:

};

