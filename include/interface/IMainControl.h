#pragma once

#include <iostream>
#include <memory>

#include "IService.h"

#define		MAINCONTROLSERVICEID	"com.MainControl.Plugin"

#define		MainControlSPtr			std::shared_ptr<IMainControl>
#define		MainControlWPtr			std::weak_ptr<IMainControl>

class IMainControl
	: public IService
{
public:
	virtual ~IMainControl() {};

	virtual void MainControlWidgetShow() = 0;

	virtual void SetPlayMusicPng(const bool& _flag) = 0;
};