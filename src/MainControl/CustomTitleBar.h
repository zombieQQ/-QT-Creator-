#pragma once

#include <QWidget>
#include "ui_CustomTitleBar.h"

#include <QMouseEvent>
#include <qpushbutton.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qfile.h>
#include <QStack>
#include <memory>
#include <QCursor>

#include "Peeling.h"

#define		AppPath		QCoreApplication::applicationDirPath()

#define		QString2StdString(x)	(QString(x).toStdString())
#define		StdString2QString(x)	(QString::fromLocal8Bit(std::string(x).c_str()))

class CustomTitleBar
	: public QWidget
{
	Q_OBJECT

public:
	explicit CustomTitleBar(QWidget *parent = nullptr);
	~CustomTitleBar();

signals:

	void SignalForwardAndBackWard(const bool& _flag);

private:
    // ��갴���¼�
	void mousePressEvent(QMouseEvent* event) override;

    // ����ƶ��¼�������ʵ���϶�Ч��
    void mouseMoveEvent(QMouseEvent* event) override;

    // �����Զ���������ı���
    void paintEvent(QPaintEvent* event) override;

	// ��ʼ��
	void InitUi();

	// ��ʼ������
	void InitConnect();

private slots:
	// ����qss
	void SettingQss(const std::string& _qssFileName);

private:
	Ui::CustomTitleBarClass ui;

	// ��갴��ʱ�ĳ�ʼλ��
	QPoint dragStartPosition_;

	Peeling*		peeling_widget_ = new Peeling;

	// ��ǰqss�ļ���
	std::string   cur_qss_file_name_;
};
