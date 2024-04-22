#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		FOLLOWWITHSERVICEID		"com.IFollowWith.Plugin"

#define		IFollowWithSPtr			std::shared_ptr<IFollowWith>
#define		IFollowWithWPtr			std::weak_ptr<IFollowWith>

class IFollowWith
	: public IService
{
public:

	virtual ~IFollowWith() {};

	virtual QWidget* GetWidget() = 0;
};