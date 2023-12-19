#ifndef MACROCONFIG_H
#define MACROCONFIG_H
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "BlueStacks.h"
#include <limits>
#include "fsfml.h"


class macroConfig
{
public:
	macroConfig();
	macroConfig(std::string Gamepackage, std::string Gameactivity);

	std::string copytxtContent(std::string path);
	void printFileContent(std::string path);
	std::string readString(const std::string& filename, const std::string& lineParameter, const std::string& first, const std::string& last);
	int readInt(const std::string& filename, const std::string& lineParameter, const std::string& first, const std::string& last);
	bool readBool(const std::string& filename, const std::string& lineParameter, const std::string& first, const std::string& last);

	int readIntMcfile(const std::string& lineParameter);
	bool readBoolMcfile(const std::string& lineParameter);
	std::string readStringMcfile(const std::string& lineParameter);

	void updateString(const std::string& filename, const std::string& lineParameter, const std::string& content, const std::string& first, const std::string& last);
	void updateInt(const std::string& filename, const std::string& lineParameter, const int& content, const std::string& first, const std::string& last);
	void updateBool(const std::string& filename, const std::string& lineParameter, const bool& content, const std::string& first, const std::string& last);

	bool hasDataCollected();
	Instance returnfavouriteInstance();

	std::string copyBlueStacksConf();
	std::string extractContent(const std::string& line, const std::string& first, const std::string& last);
	std::string updateText(std::string line, std::string content, const std::string& first, const std::string& last);
	std::string returnLineParam(const std::string& file, const std::string& lineparameter);
	std::string removeText(const std::string& file, const std::string& sometext);
	std::string removeTextParam(const std::string& file, const std::string& lineParameter);
	std::string returnPartBeforeLine(const std::string& text, const std::string& line);
	std::string returnPartBeforeIncLine(const std::string& text, const std::string& line);
	std::string returnPartAfterLine(const std::string& text, const std::string& line);

	std::string readEngineLineConfigFile(const std::string& line);

	std::string readBluestacksConf(const std::string& lineparameter);

	void resetMacroConfig();



	void updateBlueStacksConfAdbPort(Instance& inst);

	std::string readLineMcFile(const std::string& lineparameter);

	void initAllBluestacksInstances();


	void findAllBlueStacksEngines();

	std::string cropText(const std::string& text, size_t pos);

	std::vector<std::string>findAllOccurences(const std::string& filename, const std::string& lineparameter);

	std::vector<std::string>readAllmcfileEngines(const std::string& filename);

	int readmcfileNbInstances(const std::string& filename);
	void readMcfilefavouriteInstance();
	void readMcfilefavouritePreset();
	std::vector<std::string>readAllmcfileEnginesName(const std::string& filename);
	void readBlueStacksConfInstanceCar(const std::string& filename, std::string nameinstance);
	void showEngines();
	void showBluestacksInstances();
	void showBlueStacksIntance(Instance& Inst);
	std::string copyMcfilecontent();

	void writeInitMcfile();
	void fillInitMcfile();
	void updateFavouriteInstance(Instance& inst);
	void updateFavouritePreset(const std::string& preset);
	void initAllInstanceMcfile();

	void updatePortMcfile(Instance& inst);
	void updateHasGameMcfile(Instance& inst);
	void updateIdMcfile(Instance& inst);
	void updateBootMcfile(Instance& inst);
	void updatePathMcfile(Instance& inst);
	void updateWidthMcfile(Instance& inst);
	void updateHeightMcfile(Instance& inst);
	void updateEngineNameMcfile(Instance& inst);
	void updateInstanceNameMcfile(Instance& inst);
	void updateNbInstanceMcfile(Instance& inst);

	void updateBluestacksConfInfoFromMcfile();

	std::vector<Instance>returnInstancesHasGame();
	Instance choosePlayingInstance();
	void updateInstanceMcfile(Instance& inst);
	void updateAllInstancesMcfile();
	std::string initInstanceMcfile(Instance& inst);
	void updateMcfileInstances();
	void initBlueStacksBasic();
	void updateBlueStacksInstances();
	void initMacroConfig();
	std::string copyBasicConfigInfo();
	void setDim(int dimx, int dimy);
	void initBasic();

	std::string gamepackage, gameactivity;
	std::string mcfile;
	std::string favouritePreset, favouriteInstanceid;
	sysCommands sys;
	fsfml ml;
	bool changefavInstance;
	int desiredX, desiredY;
	Instance playingInstance;
	std::vector<Instance>hasGameInst;
	Bluestacks blue;
};





#endif