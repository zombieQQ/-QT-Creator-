#pragma once

#include "hn_gui_global.h"

class HnGuiPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

	Q_PLUGIN_METADATA(IID AbstractInterface_lid)

	Q_INTERFACES(AbstractPlugin)

public:
	HnGuiPlugin(QObject* parent = Q_NULLPTR);
	~HnGuiPlugin();

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// 获取服务
	virtual void StartPlugin() override;

private:

};
