
#include <QWidget>
#include <qscrollarea.h>
#include <QScrollBar>
#include <qfile.h>
#include <qbuttongroup.h>
#include <QtXml/QDomDocument>
#include <qvector.h>

#include "video_global.h"
#include "interface/IVideo.h"
#include "ui_video.h"

#define		AppPath		QCoreApplication::applicationDirPath()
#define     BtnQss		"/../src/Video/videos_classify.qss"

// 滚动区域qss文件
#define     ScrollAreaQss   "/../src/Video/scroll_area.qss"

#define     ConfigFile		"/../config/video.xml";

class video
	: public QWidget
	, public IVideo
{
	Q_OBJECT

public:
	video(QWidget *parent = nullptr);
	~video();

	virtual QWidget* GetVideoWidget() override;

private slots:

	void SlotBtnGroupClicked(QAbstractButton* _btn);

private:

	void InitUi();

	void InitConnect();

	// 打开qss文件
	QString OpenQssFile(const std::string& _qssFile);

	void SettingQss(const QString& _qss);

	void SetBtnGroup();

	void ReadConfig(const QString& _name);

private:
	Ui::videoClass ui;

	QScrollArea* scroll_area_ = nullptr;

	QButtonGroup* btns_group_ = new QButtonGroup;

	QVector<QLabel*>	pngLabels;
	QVector<QLabel*>	desLabels;
	QVector<QLabel*>	authorLabels;
};
