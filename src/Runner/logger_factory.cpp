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

// ��ȡ��ǰʱ��
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

// ��־����ΪDebug�����ڵ��Ժ��Ų�
// params: 
//		_source: ��־��Դ����ʽΪ [main.cpp: 56]��˵��������־��main.cpp��56��
//		_msg: ��־����
// eg: [2023-09-25 18:08:45][Debug][main.cpp: 56][Debug��־]
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

// ��־����ΪInfo�����ڼ�¼���й����е���Ϣ
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

// Warning�����ܻ�����Ǳ�����⣬����������������
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

// Error���ɻָ��Ĵ��󣬳���������������
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

// Critical���޷��ָ��Ĵ��󣬳�������������
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

// Exception�����򲶻����쳣�������Ҫ��һ������
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