#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "IService.h"

#define		IHEADERLESSTABLEWIDGETSERVICEID		"com.IHeaderLessTableWidget.Plugin"

#define		IHeaderLessTableWidgetSPtr			std::shared_ptr<IHeaderLessTableWidget>
#define		IHeaderLessTableWidgetWPtr			std::weak_ptr<IHeaderLessTableWidget>

class IHeaderLessTableWidget
	: public IService
{
public:

	virtual ~IHeaderLessTableWidget() {};

	// 获取Widget指针
	virtual void* GetWidget() = 0;

	// 设置表格的行数和列数
	virtual void SetRowCol(int _row, int _col) = 0;

	// 更新表格
	virtual void UpdateTableWidget(const std::vector<std::vector<std::string>>& _table_data) = 0;
};