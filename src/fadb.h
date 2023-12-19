
#ifndef FADB_H
#define FADB_H
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <array>
#include <memory>
#include <ctime>
#include <filesystem>
#include <atomic>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <cstdio>
#include "sysCommands.h"


class fadb
{
public:
	fadb(int intport);
	fadb(std::string strport);
	fadb();
	~fadb();
	void setPort(int intPort);
	void setPort(std::string strPort);
	std::string runAdbLocalhostShell(const std::string& command);
	std::string runAdbLocalhost(const std::string& command);
	std::string runAdb(const std::string& command);
	void input(const std::string& inputcmd);
	void touch(int x, int y);
	void swipe(int x1, int y1, int x2, int y2, int delayMilliseconds);
	void getEmulatorDimensions(int& DIMX, int& DIMY);
	void launchPackage(std::string namepckg);
	int  getPidLogcat();
	void quitPackage(std::string namepckg);
	void home();
	void back();
	void devices();
	void takeScreenshot(const std::string& filename);
	void screenshotBusy();
	void screenshotEvents();
	void screenshot();
	void connectLocalhost(int port);
	void disconnectLocalhost(int port);
	void setResolution(int x, int y, int dpi);
	void killAdb();
	int getPid(const std::string& process);
	std::vector<int> getMultPid(const std::string& process);
	void killPid(int pid);
	void killLogcat();
	bool StrLogTime(const std::string& search, int seconds);
	bool packageRunning(std::string package);
	bool onPackage(std::string package);
	std::string currentFocus();
	std::string strport;
	int intport;

private:

	sysCommands sys;
};
#endif

