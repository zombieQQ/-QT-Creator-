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

	// ��־����ΪDebug�����ڵ��Ժ��Ų�
	// params: 
	//		_source: ��־��Դ����ʽΪ [main.cpp: 56]��˵��������־��main.cpp��56��
	//		_msg: ��־����
	virtual void LogDebugMsg(std::string _source, std::string _msg) = 0;

	// ��־����ΪInfo�����ڼ�¼���й����е���Ϣ
	virtual void LogInfoMsg(std::string _source, std::string _msg) = 0;

	// Warning�����ܻ�����Ǳ�����⣬����������������
	virtual void LogWarningMsg(std::string _source, std::string _msg) = 0;

	// Error���ɻָ��Ĵ��󣬳���������������
	virtual void LogErrorMsg(std::string _source, std::string _msg) = 0;

	// Critical���޷��ָ��Ĵ��󣬳�������������
	virtual void LogCriticalMsg(std::string _source, std::string _msg) = 0;

	// Exception�����򲶻����쳣�������Ҫ��һ������
	virtual void LogExceptionMsg(std::string _source, std::string _msg) = 0;
};