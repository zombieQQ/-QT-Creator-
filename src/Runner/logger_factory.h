#pragma once

#include "ILoggerFactory.h"

#include <qapplication.h>
#include <ctime>
#include <fstream>

// exe文件的路径
#define AppPath QCoreApplication::applicationDirPath()

// 日志消息类型
#define     Debug       "[Debug]"          // 调试类型         用于调试和排查
#define     Info        "[Info]"           // 信息类型         用于记录运行过程中的信息
#define     Warning     "[Warning]"        // 警告类型         可能会引发潜在问题，程序仍能正常运行
#define     Error       "[Error]"          // 错误类型         可恢复的错误，程序仍能正常运行
#define     Critical    "[Critical]"       // 严重错误类型     无法恢复的错误，程序不能正常运行
#define     Exception   "[Exception]"      // 异常类型         程序捕获到了异常情况，需要进一步处理

class LoggerFactory :
    public ILoggerFactory
{

public:

    LoggerFactory();

    ~LoggerFactory();

	// 日志类型为Debug，用于调试和排查
	// params: 
	//		_source: 日志来源，格式为 [main.cpp: 56]，说明该条日志在main.cpp的56行
	//		_msg: 日志内容
	virtual void LogDebugMsg(std::string _source, std::string _msg) override;

	// 日志类型为Info，用于记录运行过程中的信息
	virtual void LogInfoMsg(std::string _source, std::string _msg) override;

	// Warning，可能会引发潜在问题，程序仍能正常运行
	virtual void LogWarningMsg(std::string _source, std::string _msg) override;

	// Error，可恢复的错误，程序仍能正常运行
	virtual void LogErrorMsg(std::string _source, std::string _msg) override;

	// Critical，无法恢复的错误，程序不能正常运行
	virtual void LogCriticalMsg(std::string _source, std::string _msg) override;

	// Exception，程序捕获到了异常情况，需要进一步处理
	virtual void LogExceptionMsg(std::string _source, std::string _msg) override;

private:

	// 获取当前时间
	std::string GetCurrentTime();

private:

    std::string logFilePath_;           // 日志文件路径

	std::ofstream outputFile_;
};

