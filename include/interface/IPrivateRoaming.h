#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		IPRIVATEROAMINGSERVICEID		"com.IPrivateRoaming.Plugin"

#define		IPrivateRoamingSPtr			std::shared_ptr<IPrivateRoaming>
#define		IPrivateRoamingWPtr			std::weak_ptr<IPrivateRoaming>

class IPrivateRoaming
	: public IService
{
public:

	virtual ~IPrivateRoaming() {};

	virtual QWidget* GetWidget() = 0;
};