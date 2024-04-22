#pragma once

#include <QObject>

#include "interface/IGuiFactory.h"
#include "HeaderLessTableWidget.h"

class GuiFactory
	: public QObject
	, public IGuiFactory
{
	Q_OBJECT

public:
	GuiFactory(QObject *parent = nullptr);
	~GuiFactory();

	virtual IHeaderLessTableWidgetSPtr	CreateHeaderLessTableWidget() override;
};
