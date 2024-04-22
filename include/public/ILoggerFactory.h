#pragma once

#include <iostream>
#include <memory>

#include "IService.h"

#define			LOGGERFACTORYSERVICEID		"com.LoggerFactory.plugin"

#define			LoggerFactorySPtr			std::shared_ptr<ILoggerFactory>
#define			LoggerFactoryWPtr			std::weak_ptr<ILoggerFactory>

class ILoggerFactory
	: public IService
{
public:

	virtual ~ILoggerFactory() {};

	// 日志类型为Debug，用于调试和排查
	// params: 
	//		_source: 日志来源，格式为 [main.cpp: 56]，说明该条日志在main.cpp的56行
	//		_msg: 日志内容
	virtual void LogDebugMsg(std::string _source, std::string _msg) = 0;

	// 日志类型为Info，用于记录运行过程中的信息
	virtual void LogInfoMsg(std::string _source, std::string _msg) = 0;

	// Warning，可能会引发潜在问题，程序仍能正常运行
	virtual void LogWarningMsg(std::string _source, std::string _msg) = 0;

	// Error，可恢复的错误，程序仍能正常运行
	virtual void LogErrorMsg(std::string _source, std::string _msg) = 0;

	// Critical，无法恢复的错误，程序不能正常运行
	virtual void LogCriticalMsg(std::string _source, std::string _msg) = 0;

	// Exception，程序捕获到了异常情况，需要进一步处理
	virtual void LogExceptionMsg(std::string _source, std::string _msg) = 0;
};