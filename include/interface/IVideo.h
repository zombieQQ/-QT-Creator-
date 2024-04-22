#pragma once

#include <iostream>
#include <memory>

#include	"public/IService.h"

#define		VIDEOSERVICEID		"com.Video.Plugin"

#define		IVideoSPtr			std::shared_ptr<IVideo>
#define		IVideoWPtr			std::weak_ptr<IVideo>

class IVideo
	: public IService
{
public:

	virtual ~IVideo() {};

	virtual QWidget* GetVideoWidget() = 0;
};