#pragma once

#include <iostream>
#include <memory>

#include "IService.h"

#define		ROTATIONCHARTSERVICEID		"com.RotationChart.Plugin"

#define		RotationChartSPtr			std::shared_ptr<IRotationChart>
#define		RotationChartWPtr			std::weak_ptr<IRotationChart>

class IRotationChart
	: public IService
{
public:

	virtual ~IRotationChart() {};

	virtual QWidget* RotationChartShow() = 0;

	// Æô¶¯ÂÖ²¥Í¼¶¨Ê±Æ÷
	virtual void StartRotationChartTimer() = 0;
};