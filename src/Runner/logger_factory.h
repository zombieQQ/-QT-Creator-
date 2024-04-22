#pragma once

#include "ILoggerFactory.h"

#include <qapplication.h>
#include <ctime>
#include <fstream>

// exe�ļ���·��
#define AppPath QCoreApplication::applicationDirPath()

// ��־��Ϣ����
#define     Debug       "[Debug]"          // ��������         ���ڵ��Ժ��Ų�
#define     Info        "[Info]"           // ��Ϣ����         ���ڼ�¼���й����е���Ϣ
#define     Warning     "[Warning]"        // ��������         ���ܻ�����Ǳ�����⣬����������������
#define     Error       "[Error]"          // ��������         �ɻָ��Ĵ��󣬳���������������
#define     Critical    "[Critical]"       // ���ش�������     �޷��ָ��Ĵ��󣬳�������������
#define     Exception   "[Exception]"      // �쳣����         ���򲶻����쳣�������Ҫ��һ������

class LoggerFactory :
    public ILoggerFactory
{

public:

    LoggerFactory();

    ~LoggerFactory();

	// ��־����ΪDebug�����ڵ��Ժ��Ų�
	// params: 
	//		_source: ��־��Դ����ʽΪ [main.cpp: 56]��˵��������־��main.cpp��56��
	//		_msg: ��־����
	virtual void LogDebugMsg(std::string _source, std::string _msg) override;

	// ��־����ΪInfo�����ڼ�¼���й����е���Ϣ
	virtual void LogInfoMsg(std::string _source, std::string _msg) override;

	// Warning�����ܻ�����Ǳ�����⣬����������������
	virtual void LogWarningMsg(std::string _source, std::string _msg) override;

	// Error���ɻָ��Ĵ��󣬳���������������
	virtual void LogErrorMsg(std::string _source, std::string _msg) override;

	// Critical���޷��ָ��Ĵ��󣬳�������������
	virtual void LogCriticalMsg(std::string _source, std::string _msg) override;

	// Exception�����򲶻����쳣�������Ҫ��һ������
	virtual void LogExceptionMsg(std::string _source, std::string _msg) override;

private:

	// ��ȡ��ǰʱ��
	std::string GetCurrentTime();

private:

    std::string logFilePath_;           // ��־�ļ�·��

	std::ofstream outputFile_;
};

