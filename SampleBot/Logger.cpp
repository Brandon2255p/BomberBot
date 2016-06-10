#include "stdafx.h"
#include "Logger.h"
#include <ctime>
Logger::Logger() :
Logger("DefaultLog.txt")
{
}

Logger::Logger(string LogFileName):
m_strLogFileName(LogFileName)
{
	time_t  timev;
	time(&timev);
	m_ofLogFile.open(LogFileName + "_" + to_string(timev) + ".txt", ios::out | ios::app);
}


Logger::~Logger()
{
	m_ofLogFile.close();
}


void Logger::WriteToLog(string TextToAdd)
{
	time_t  timev;
	time(&timev);
	m_ofLogFile << timev << "::" << TextToAdd << endl;
}
