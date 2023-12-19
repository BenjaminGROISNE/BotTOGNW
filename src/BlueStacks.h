
#ifndef BLUESTACKS_H
#define BLUESTACKS_H
#include <iostream>
#include <vector>
#include "fadb.h"
#include "sysCommands.h"


struct Instance {

	Instance();
	std::string EngineName;
	std::string InstanceName;
	int port;
	int boot;
	std::string path;
	int width;
	int height;
	int nbinstance;
	std::string id;
	bool hasgame;
};

class Bluestacks {
public:
	Bluestacks();
	Bluestacks(std::string gamepackage);
	void sethdPlayerPath();
	void setConfigPath();
	void findBlueStacks();
	bool findGamePackage(const std::string& path, const std::string& packagename);
	void findAllInstancesGame();
	void findInstancePath(Instance& inst);
	void findAllInstancesPath();
	void startInstance(Instance inst);
	void wait(int milliSeconds);
	bool isInstalled;
	int nbInstances;
	std::string hdPlayerPath, blueStacksConfigPath, hdPlayerFolder, blueStacksConfigFolder, gamepackage;
	std::string exename, confname;
	std::vector<std::string>Engines;
	std::vector<Instance>BluestacksInstances;
	fadb adb;
	sysCommands sys;
};
#endif

