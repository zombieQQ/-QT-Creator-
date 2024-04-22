#pragma once

/*!
 * \file exclusive_custom.h
 * \date 2023/10/29 16:44
 *
 * \author 张惠楠
 * Contact: user@company.com
 *
 * \brief 主界面的专属订制
 * \note  
*/

#include <QWidget>

#include "main_control_global.h"
#include "ui_exclusive_custom.h"

class ExclusiveCustom : public QWidget
{
	Q_OBJECT

public:
	ExclusiveCustom(QWidget *parent = nullptr);
	~ExclusiveCustom();

private:
	Ui::ExclusiveCustomClass ui;
};
