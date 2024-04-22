/*!
 * \file IMyLikeMusic.h
 * \date 2024/01/21 13:13
 *
 * \author ok
 * Contact: user@company.com
 *
 * \brief
 *
 * 最近播放 接口
 *
 * \note
*/

#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		IRECENTLYPLAYEDSERVICEID		"com.IRecentlyPlayed.Plugin"

#define		IRecentlyPlayedSPtr			std::shared_ptr<IRecentlyPlayed>
#define		IRecentlyPlayedWPtr			std::weak_ptr<IRecentlyPlayed>

class IRecentlyPlayed
	: public IService
{
public:

	virtual ~IRecentlyPlayed() {};

	virtual QWidget* GetWidget() = 0;
};