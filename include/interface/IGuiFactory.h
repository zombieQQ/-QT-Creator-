#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "IService.h"
#include "IHeaderLessTableWidget.h"

#define		IGUIFACTORYSERVICEID		"com.IGuiFactory.Plugin"

#define		IGuiFactorySPtr			std::shared_ptr<IGuiFactory>
#define		IGuiFactoryWPtr			std::weak_ptr<IGuiFactory>

class IGuiFactory
	: public IService
{
public:

	virtual ~IGuiFactory() {};

	virtual IHeaderLessTableWidgetSPtr	CreateHeaderLessTableWidget() = 0;
};