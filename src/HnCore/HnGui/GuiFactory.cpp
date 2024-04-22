#include "GuiFactory.h"

GuiFactory::GuiFactory(QObject *parent)
	: QObject(parent)
{}

GuiFactory::~GuiFactory()
{}

IHeaderLessTableWidgetSPtr GuiFactory::CreateHeaderLessTableWidget()
{
	return std::make_shared<HeaderLessTableWidget>();
}
