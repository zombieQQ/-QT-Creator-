/*!
 * \file IMyLikeMusic.h
 * \date 2024/01/21 13:13
 *
 * \author ok
 * Contact: user@company.com
 *
 * \brief
 *
 * 本地与下载 接口
 *
 * \note
*/

#pragma once

#include <iostream>
#include <memory>
#include <QWidget>

#include	"public/IService.h"

#define		LOCALANDDOWNLOADSERVICEID		"com.ILocalAndDownload.Plugin"

#define		ILocalAndDownloadSPtr			std::shared_ptr<ILocalAndDownload>
#define		ILocalAndDownloadWPtr			std::weak_ptr<ILocalAndDownload>

class ILocalAndDownload
	: public IService
{
public:

	virtual ~ILocalAndDownload() {};

	virtual QWidget* GetWidget() = 0;
};