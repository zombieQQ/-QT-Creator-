#pragma once

#include "rotation_chart_global.h"

class RotationChartPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

	Q_PLUGIN_METADATA(IID AbstractInterface_lid)

	Q_INTERFACES(AbstractPlugin)

public:
	RotationChartPlugin(QObject* parent = Q_NULLPTR);
	~RotationChartPlugin();

	// 注册服务
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// 获取服务
	virtual void StartPlugin() override;

private:

};
