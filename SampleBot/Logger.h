#pragma once


#include <string>
#include <fstream>

using namespace std;


class Logger
{
public:
	Logger();
	Logger(string LogFileName);
	~Logger();
private:
	string m_strLogFileName;
	ofstream m_ofLogFile;
public:
	void WriteToLog(string TextToAdd);
};

