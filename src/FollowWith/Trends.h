#pragma once

#include <QVector>
#include <QString>
#include <QWidget>
#include <QPixmap>

#include "ui_Trends.h"

class Trends : public QWidget
{
	Q_OBJECT

public:
	Trends(QWidget *parent = nullptr);
	~Trends();

	void InitUi(const QVector<QString> _msg);

private:
	Ui::TrendsClass ui;
};
