#pragma once
#include "recently_played_global.h"

class RecentlyPlayedPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

		Q_PLUGIN_METADATA(IID AbstractInterface_lid)

		Q_INTERFACES(AbstractPlugin)

public:

	RecentlyPlayedPlugin(QObject* parent = Q_NULLPTR);
	~RecentlyPlayedPlugin();

	// ע�����
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// ��ȡ����
	virtual void StartPlugin() override;

private:

};

