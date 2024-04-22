#pragma once
#include "follow_global.h"

class FollowPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

		Q_PLUGIN_METADATA(IID AbstractInterface_lid)

		Q_INTERFACES(AbstractPlugin)

public:

	FollowPlugin(QObject* parent = Q_NULLPTR);
	~FollowPlugin();

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// 获取服务
	virtual void StartPlugin() override;

private:

};

