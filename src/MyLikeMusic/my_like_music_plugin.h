#pragma once
#include "my_like_music_global.h"

class MyLikeMusicPlugin
	: public QObject
	, public AbstractPlugin
{
	Q_OBJECT

		Q_PLUGIN_METADATA(IID AbstractInterface_lid)

		Q_INTERFACES(AbstractPlugin)

public:

	MyLikeMusicPlugin(QObject* parent = Q_NULLPTR);
	~MyLikeMusicPlugin();

	// ע�����
	virtual void InitPlugin(ModuleLinkerSPtr _context_ptr) override;

	// ��ȡ����
	virtual void StartPlugin() override;

private:

};

