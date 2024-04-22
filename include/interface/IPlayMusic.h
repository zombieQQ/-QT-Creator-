// ������������Ľӿ��ļ�

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

	// ��ȡ�����Widgetָ��
	virtual QWidget* GetWidget() = 0;

	// ���ò������ֵ���Ϣ
	// [0] ����
	// [1] ����
	// [2] ʱ��
	virtual void SetPlayMusic(const std::vector<QString>& _musicInfo) = 0;
};