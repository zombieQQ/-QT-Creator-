// 播放音乐组件的接口文件

#pragma once

#include <iostream>
#include <memory>
#include <QWidget>
#include <vector>

#include	"public/IService.h"

#define		IPLAYMUSICSERVICEID		"com.IPlayMusic.Plugin"

#define		IPlayMusicSPtr			std::shared_ptr<IPlayMusic>
#define		IPlayMusicWPtr			std::weak_ptr<IPlayMusic>

class IPlayMusic
	: public IService
{
public:

	virtual ~IPlayMusic() {};

	// 获取组件的Widget指针
	virtual QWidget* GetWidget() = 0;

	// 设置播放音乐的信息
	// [0] 歌名
	// [1] 歌手
	// [2] 时长
	virtual void SetPlayMusic(const std::vector<QString>& _musicInfo) = 0;
};