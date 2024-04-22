#pragma once
#include "private_romaing_global.h"

class PrivateRomaingPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

		Q_PLUGIN_METADATA(IID AbstractInterface_lid)

		Q_INTERFACES(AbstractPlugin)

public:

	PrivateRomaingPlugin(QObject* parent = Q_NULLPTR);
	~PrivateRomaingPlugin();

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// 获取服务
	virtual void StartPlugin() override;

private:

};

