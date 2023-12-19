#ifndef GAME_H
#define GAME_H

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
#include <functional>
#include <algorithm>
#include "fopencv.h"
#include "fadb.h"
#include "sysCommands.h"
#include "fsfml.h"
#include "macroConfig.h"
#include "paths.h"
#include "TemplatePath.h"



class game
{
public:
	game();
	void startMacro();
	void initActivities();
	void macroLoop();
	void activityLoop();
	bool macroEnd();
	void startGame();
	void launchGame();
	//Activités
	void doMissions();
	void doMail();
	void doLoot();
	void doAdventure();
	void doFriends();
	void doShop();
	void doArena();
	void doMock();
	void doTrial(); 
	void doAgency();
	void doAlliance();
	void doGuardian();
	void doSecretFloor();
	void TryAdventure();
	bool goHomeFirstBoot();
	void goHome();
	void test();




	//Outils


	bool fcA(const std::string& Templ, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fA(const std::string& Templ, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcpopupA();
	void loopPopUp(typeMat color=Gray);
	void fillPopup();
	bool fcOneTemplateMultipleTemplateA(const std::string& Templ, pos direction, int order, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fOneTemplateMultipleTemplateA(const std::string& Templ, pos direction, int order, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const pos& direction, int order, Zone Z = Zone(), unsigned int delayMilliseconds= DEFAULTDELAY, bool willInteract=false);
	bool fcOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const pos &direction, int order, Zone Z = Zone(), unsigned int delayMilliseconds= DEFAULTDELAY);
	bool fOneMultipleTemplateA(std::vector<std::vector<std::string>> allTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fMultipleTemplateA(const std::vector<std::string>alltempl, std::vector<std::string>& foundTemplates, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fMultipleCompareTemplateA(const std::vector<std::string>alltempl, const std::vector<std::string>simTempl, std::vector<std::string>& foundTemplates, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcOneTemplateA(const std::vector<std::string>&allTempl, std::string& foundTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fOneTemplateA(const std::vector<std::string> allTempl, std::string& foundTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcOneTemplateA(const std::vector<std::string>&toclick, const  std::vector<std::string>&tonotclick, std::string& foundTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fcOneTemplateA(const std::vector<std::string> &toclick, const  std::vector<std::string> &tonotclick, Zone Z=Zone(), unsigned int delayMilliseconds= DEFAULTDELAY);
	bool fCompareOneTemplateA(const std::vector<std::string>& allTempl, const std::vector<std::string> &simTempl, std::string& Tresult, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcOneTemplateA(const std::vector<std::string>&allTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fOneTemplateA(const std::vector<std::string>& allTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fOneTemplateEraseA(std::vector<std::string>& allTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcOneTemplateEraseA(std::vector<std::string>& allTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fnbTemplateA(const std::string& Templ, int& nb, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	int fnbTemplateA(const std::string& Templ, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	int fnbTemplateA(const std::vector<std::string>& allTempl, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	int fnbMultipleCompareTemplateA(const std::vector<std::string>& allTempl, const std::vector<std::string>& simTempls, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	int fnbUniqueCompareTemplateA(const std::vector<std::string>& allTempl, const std::vector<std::string>& simTempls, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	int fnbCompareTemplateA(const std::string& Templ,const std::vector<std::string>&simTempls, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);

	bool fcCompareA(const std::string& goodTemplate, const std::string& similartemplate,Zone Z=Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fCompareA(const std::string& goodTemplate, const std::string& similartemplate, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcCompareMultipleTemplateA(const std::string& goodTemplate, const std::vector<std::string>& similartemplates, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool fCompareMultipleTemplateA(const std::string& goodTemplate, const std::vector<std::string>& similartemplates, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fMultipleCompareMultipleTemplateA(const std::string& goodTemplate, const std::vector<std::string>& similartemplates, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fCompareOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const std::vector<std::string>& simTempl, pos direction, int order, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY, bool willInteract = false);
	bool fcCompareOneTemplateMultipleTemplateA(const std::vector<std::string>& alltempl, const std::vector<std::string>& simTempl, pos direction, int order, Zone Z = Zone(), unsigned int delayMilliseconds = DEFAULTDELAY);
	bool templateFound(bool found,const Template& templ, bool willInteract = false, unsigned int delayMilliseconds = DEFAULTDELAY);
	bool templateFound(bool found, const Template& templ, bool willInteract = false, Action act = Action::Click, Coords coord = Coords(), unsigned int delayMilliseconds = DEFAULTDELAY);
	void resetCount();
	bool fSwipeA(std::string imgtemplate, Coords Cresult, Zone Z = Zone(), bool willInteract = true);
	bool fSwipeA(std::string imgtemplate, poswipe endx, poswipe endy, Zone Z = Zone(), bool willInteract = true);
	bool fMultipleDigitsA(int nb, std::vector<std::string>Nb, std::vector<Template>& Tresult, Zone Z);
	Number fNumberIntegerA(std::vector<std::string>digits, std::vector<Unit>Units, Zone Z);
	Number fNumberIntegerA(std::vector<std::string>digits, Zone Z);
	Number fNumberDecimalA(std::vector<std::string>digits, std::vector<Unit>Units, std::string dot, Zone Z);
	Number fNumberDecimalA(std::vector<std::string>digits, std::string dot, Zone Z);


	int getMatWidth(const std::string& name);
	int getMatHeight(const std::string& name);
	void swipeX(int x1, int x2, int millitime=1000);
	void swipeY(int y1, int y2, int millitime=1000);
	void swipe(int x1, int y1, int x2, int y2, int millitime);
	void click(Coords Coord);
	void click(int x, int y);
	void wait(int milliSeconds);
	void orderDigits(std::vector<Digit>& digit);
	bool eraseString(std::vector<std::string>&allTempl,std::string templ);
	bool fStr(const std::vector<std::string>& allTempl, std::string templ);
	bool fStr(const std::vector<std::string>& allTempl, const std::vector<std::string> allkeys);
	bool fOneStr(const std::vector<std::string>& allTempl, const std::vector<std::string> allkeys);
	std::vector<Coords>orderCoords(const std::vector<Coords>& coords, pos dir);
	std::vector<Template>orderTemplates(const std::vector<Template>& allTempl, pos dir);
	std::vector<Coords> orderPoint(const std::vector<Coords>& coord, const Coords& Cf);
	int distancePoint(const Coords& fixpt, const Coords& pt);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSecond();
	day getUTCDay();
	int getUTCHour();
	std::tuple<bool*, std::string> getActivity(char key, bool& present);
	void setActivity(char key, bool activate);
	void setActivity(std::tuple<bool*, std::string> tuple, bool activate);
	void loadTemplate(std::string image);
	void loadAllTemplates();
	void getFilesPath(std::vector<std::string>& tab, std::filesystem::directory_iterator path);
	void showVector(std::vector<std::string>vect);
	Template getTemplate(std::string image, typeMat type = Gray);
	std::vector<Template> getTemplate(std::vector<std::string> images, typeMat type = Gray);
	int getCx()const;
	int getCy()const;
	void setDimX(int dimx);
	void setDimY(int dimY);
	int getRebootCount();
	void setRebootCount(int nb);
	void setPort(int port);
	void selectActivity();
	int getDimX();
	int getDimY();
	void setAdb(fadb adb);
	void setSys(sysCommands sys);
	const static int waitnotfound = 1000;
	const static int waitfound = 2000;
	const static int DEFAULTDELAY = waitfound;
	const static int MAXREBOOT = 20;
	bool MISSIONS, TRYADVENTURE, MAIL, LOOT, ADVENTURE, FRIENDS, SHOP, ARENA, MOCK, TRIAL, AGENCY, ALLIANCE,GUARDIAN,SECRETFLOOR;
	int rebootCount;
	bool restartMacro;
	bool firstboot;
	bool endmacro;
	Template background;
	std::map<std::string, Template> allTemplates;
	std::map<char, std::tuple<bool*, std::string>> allActivities;
	std::string package;
	std::string activity;
	std::vector<Popup>listPopup;
	std::vector<Coords>listcoords;
	int dimX, dimY;
	Coords C;
	fopencv op;
	fadb adb;
	fsfml ml;
	sysCommands sys;
	macroConfig mac;
};
#endif
