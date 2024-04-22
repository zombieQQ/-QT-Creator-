/*!
 * \file IMyLikeMusic.h
 * \date 2024/01/21 13:13
 *
 * \author ok
 * Contact: user@company.com
 *
 * \brief 
 *
 * 我喜欢的音乐 接口
 *
 * \note
*/

#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		MYLIKEMUSICSERVICEID		"com.IMyLikeMusic.Plugin"

#define		IMyLikeMusicSPtr			std::shared_ptr<IMyLikeMusic>
#define		IMyLikeMusicWPtr			std::weak_ptr<IMyLikeMusic>

class IMyLikeMusic
	: public IService
{
public:

	virtual ~IMyLikeMusic() {};

	virtual QWidget* GetWidget() = 0;
};