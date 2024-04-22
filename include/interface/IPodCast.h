#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		PODCASTSERVICEID		"com.IPodCast.Plugin"

#define		IPodCastSPtr			std::shared_ptr<IPodCast>
#define		IPodCastWPtr			std::weak_ptr<IPodCast>

class IPodCast
	: public IService
{
public:

	virtual ~IPodCast() {};

	virtual QWidget* GetWidget() = 0;
};