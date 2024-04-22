#include "logger_factory.h"

#include <iostream>
#include <string>

LoggerFactory::LoggerFactory()
{
	logFilePath_ = AppPath.toStdString() + "/../../log/TankShowDown.log";

    outputFile_ = std::ofstream(logFilePath_);
}

LoggerFactory::~LoggerFactory()
{
    outputFile_.close();
}

// 获取当前时间
std::string LoggerFactory::GetCurrentTime()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);

    std::string str(buffer);
    std::string res = "[" + str + "]";

    return res;
}

// 日志类型为Debug，用于调试和排查
// params: 
//		_source: 日志来源，格式为 [main.cpp: 56]，说明该条日志在main.cpp的56行
//		_msg: 日志内容
// eg: [2023-09-25 18:08:45][Debug][main.cpp: 56][Debug日志]
void LoggerFactory::LogDebugMsg(std::string _source, std::string _msg)
{
    _source = '[' + _source + ']';
    _msg = '[' + _msg + ']';
    if (outputFile_.is_open())
    {
        std::string content = GetCurrentTime() + Debug + _source + _msg;
        outputFile_ << content << std::endl;
    }
}

// 日志类型为Info，用于记录运行过程中的信息
void LoggerFactory::LogInfoMsg(std::string _source, std::string _msg)
{
    _source = '[' + _source + ']';
    _msg = '[' + _msg + ']';
    if (outputFile_.is_open())
    {
        std::string content = GetCurrentTime() + Info + _source + _msg;
        outputFile_ << content << std::endl;
    }
}

// Warning，可能会引发潜在问题，程序仍能正常运行
void LoggerFactory::LogWarningMsg(std::string _source, std::string _msg)
{
    _source = '[' + _source + ']';
    _msg = '[' + _msg + ']';
    if (outputFile_.is_open())
    {
        std::string content = GetCurrentTime() + Warning + _source + _msg;
        outputFile_ << content << std::endl;
    }
}

// Error，可恢复的错误，程序仍能正常运行
void LoggerFactory::LogErrorMsg(std::string _source, std::string _msg)
{
    _source = '[' + _source + ']';
    _msg = '[' + _msg + ']';
    if (outputFile_.is_open())
    {
        std::string content = GetCurrentTime() + Error + _source + _msg;
        outputFile_ << content << std::endl;
    }
}

// Critical，无法恢复的错误，程序不能正常运行
void LoggerFactory::LogCriticalMsg(std::string _source, std::string _msg)
{
    _source = '[' + _source + ']';
    _msg = '[' + _msg + ']';
    if (outputFile_.is_open())
    {
        std::string content = GetCurrentTime() + Critical + _source + _msg;
        outputFile_ << content << std::endl;
    }
}

// Exception，程序捕获到了异常情况，需要进一步处理
void LoggerFactory::LogExceptionMsg(std::string _source, std::string _msg)
{
    _source = '[' + _source + ']';
    _msg = '[' + _msg + ']';
    if (outputFile_.is_open())
    {
        std::string content = GetCurrentTime() + Exception + _source + _msg;
        outputFile_ << content << std::endl;
    }
}