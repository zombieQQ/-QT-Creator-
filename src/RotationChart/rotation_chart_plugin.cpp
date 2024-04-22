#include "rotation_chart_plugin.h"
#include "RotationChart.h"

ModuleLinkerSPtr				global_module_linker_ = nullptr;

RotationChartPlugin::RotationChartPlugin(QObject* parent) : QObject(parent) {

}

RotationChartPlugin::~RotationChartPlugin() {

}

void RotationChartPlugin::InitPlugin(ModuleLinkerSPtr _context_ptr)
{
	if (!global_module_linker_)
		global_module_linker_ = _context_ptr;

	RotationChartSPtr rotation_chart_ptr = std::make_shared<RotationChart>();
	global_module_linker_->SetServicePtrById(ROTATIONCHARTSERVICEID, rotation_chart_ptr);
}

void RotationChartPlugin::StartPlugin()
{
	if (!global_module_linker_)
		return;

	return;
}