#pragma once

#include <memory>
#include <iostream>
#include <qstring.h>
#include <string>

#define		QString2StdString(x)	(QString(x).toStdString())
#define		StdString2QString(x)	(QString::fromLocal8Bit(std::string(x).c_str()))		

#define		IServiceBaseSPtr		std::shared_ptr<IService>
#define		IServiceBaseWPtr		std::weak_ptr<IService>

class IService
{
public:
	virtual ~IService() {}
};