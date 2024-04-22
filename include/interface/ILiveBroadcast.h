#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		ILIVEBROADCASTSERVICEID		"com.LiveBroadcast.Plugin"

#define		ILiveBroadcastSPtr			std::shared_ptr<ILiveBroadcast>
#define		ILiveBroadcastWPtr			std::weak_ptr<ILiveBroadcast>

class ILiveBroadcast
	: public IService
{
public:

	virtual ~ILiveBroadcast() {};

	virtual QWidget* GetLiveWidget() = 0;
};