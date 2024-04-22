#pragma once

#include <QWidget>
#include "ui_Peeling.h"

class Peeling
	: public QWidget
{
	Q_OBJECT

public:
	Peeling(QWidget *parent = nullptr);
	~Peeling();

signals:

	void SignalSetCustomWidgetQss(const std::string& _qssFileName = "title_bar_red.qss");

private:

	void InitConnect();

private:
	Ui::PeelingClass ui;
};
