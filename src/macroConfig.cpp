#include "macroConfig.h"

macroConfig::macroConfig()
{
    mcfile = "macroConfig.txt";
    gamepackage.clear();
    blue = Bluestacks();
    playingInstance = Instance();
    hasGameInst.clear();
    changefavInstance = false;
}
macroConfig::macroConfig(std::string Gamepackage, std::string Gameactivity)
{
    mcfile = "macroConfig.txt";
    gamepackage = Gamepackage;
    gameactivity = Gameactivity;
    blue = Bluestacks(Gamepackage);
    playingInstance = Instance();
    hasGameInst.clear();
    favouritePreset.clear();
    favouriteInstanceid.clear();
    changefavInstance = false;
}




std::string macroConfig::copytxtContent(std::string path) {
    std::string line;
    std::string text;
    std::ifstream file(path);
    if (file) {
        while (getline(file, line)) {
            text += line + "\n";
        }
    }
    else {
        std::cout << "Cannot read File";
    }
    file.close();
    return text;
}

void macroConfig::printFileContent(std::string path)
{
    std::cout << copytxtContent(path);
}

std::string macroConfig::readString(const std::string& filename, const std::string& lineParameter, const std::string& first, const std::string& last) {
    std::string text = copytxtContent(filename);
    std::string line = returnLineParam(text, lineParameter);
    return extractContent(line, first, last);
}

int macroConfig::readInt(const std::string& filename, const std::string& lineParameter, const std::string& first, const std::string& last) {

    return stoi(readString(filename, lineParameter, first, last));

}

bool macroConfig::readBool(const std::string& filename, const std::string& lineParameter, const std::string& first, const std::string& last) {

    std::string result = readString(filename, lineParameter, first, last);
    return (result == "1" || result == "true");
}

int macroConfig::readIntMcfile(const std::string& lineParameter)
{
    return readInt(mcfile, lineParameter, "\"", "\"");
}

bool macroConfig::readBoolMcfile(const std::string& lineParameter)
{
    return readBool(mcfile, lineParameter, "\"", "\"");
}

std::string macroConfig::readStringMcfile(const std::string& lineParameter)
{
    return readString(mcfile, lineParameter, "\"", "\"");
}

void macroConfig::updateString(const std::string& filename, const std::string& lineParameter, const std::string& content, const std::string& first, const std::string& last)
{
    std::string linetochange;
    std::string text = copytxtContent(filename);
    linetochange = returnLineParam(text, lineParameter);
    std::string firstpart, secondpart;
    firstpart = returnPartBeforeLine(text, linetochange);
    secondpart = returnPartAfterLine(text, linetochange);
    text = firstpart + updateText(linetochange, content, first, last) + secondpart;
    std::ofstream writefile(filename, std::ios::trunc);
    if (writefile.is_open()) {
        writefile << text;
        writefile.close();
    }
}


void macroConfig::updateInt(const std::string& filename, const std::string& lineParameter, const int& content, const std::string& first, const std::string& last)
{

    std::string newContent = std::to_string(content);
    std::string linetochange;
    std::string text = copytxtContent(filename);
    linetochange = returnLineParam(text, lineParameter);
    std::string firstpart, secondpart;
    firstpart = returnPartBeforeLine(text, linetochange);
    secondpart = returnPartAfterLine(text, linetochange);
    text = firstpart + updateText(linetochange, newContent, first, last) + secondpart;
    std::ofstream writefile(filename, std::ios::trunc);
    if (writefile.is_open()) {
        writefile << text;
        writefile.close();
    }
}

void macroConfig::updateBool(const std::string& filename, const std::string& lineParameter, const bool& content, const std::string& first, const std::string& last)
{
    std::string newContent;
    if (content)newContent = "1";
    else newContent = "0";
    std::string linetochange;
    std::string text = copytxtContent(filename);
    linetochange = returnLineParam(text, lineParameter);
    std::string firstpart, secondpart;
    firstpart = returnPartBeforeLine(text, linetochange);
    secondpart = returnPartAfterLine(text, linetochange);
    text = firstpart + updateText(linetochange, newContent, first, last) + secondpart;
    std::ofstream writefile(filename, std::ios::trunc);
    if (writefile.is_open()) {
        writefile << text;
        writefile.close();
    }
}

bool macroConfig::hasDataCollected()
{
    return readBoolMcfile("datacollected");
}

Instance macroConfig::returnfavouriteInstance()
{
    for (Instance inst : hasGameInst) {
        if (inst.id == favouriteInstanceid)return inst;
    }
    return Instance();
}

std::string macroConfig::copyBlueStacksConf()
{
    return copytxtContent(blue.blueStacksConfigPath);
}

std::string macroConfig::extractContent(const std::string& line, const std::string& first, const std::string& last)
{
    size_t pos, endpos;
    pos = line.find(first) + first.length();
    if (pos != std::string::npos) {
        endpos = line.find(last, pos);
        if (endpos != std::string::npos) {
            return line.substr(pos, endpos - pos);
        }
    }
    return "";
}

std::string macroConfig::updateText(std::string line, std::string content, const std::string& first, const std::string& last)
{
    size_t pos, endpos;
    std::string firstpart, secondpart;
    pos = line.find(first) + first.length();
    if (pos != std::string::npos) {
        endpos = line.find(last, pos);

        if (endpos != std::string::npos) {
            firstpart = line.substr(0, pos);
            secondpart = line.substr(endpos, std::string::npos);
            return firstpart + content + secondpart;
        }
    }
    return "";
}


std::string macroConfig::returnLineParam(const std::string& text, const std::string& lineParameter)
{
    size_t pos = text.find(lineParameter);
    if (pos != std::string::npos) {
        size_t endPos = text.find("\n", pos);
        if (endPos != std::string::npos) {
            std::string result = text.substr(pos, endPos - pos);
            return result;
        }
    }
    return "";
}

std::string macroConfig::removeText(const std::string& file, const std::string& line)
{
    std::string first = returnPartBeforeLine(file, line);
    std::string second = returnPartAfterLine(file, line);
    return first + second;
}

std::string macroConfig::removeTextParam(const std::string& file, const std::string& lineParameter)
{
    return removeText(file, returnLineParam(file, lineParameter));
}

std::string macroConfig::returnPartBeforeLine(const std::string& text, const std::string& line)
{
    size_t pos = text.find(line);
    if (pos != std::string::npos) {
        return text.substr(0, pos);
    }
    return "";
}

std::string macroConfig::returnPartBeforeIncLine(const std::string& text, const std::string& line)
{
    size_t pos = text.find(line);
    if (pos != std::string::npos) {
        return text.substr(0, pos + line.length());
    }
    return "";
}

std::string macroConfig::returnPartAfterLine(const std::string& text, const std::string& line)
{
    size_t pos = text.find(line) + line.length();
    if (pos != std::string::npos) {
        return text.substr(pos, std::string::npos - pos);
    }
    return "";
}

std::string macroConfig::readEngineLineConfigFile(const std::string& line)
{
    std::string before = "bst.instance.";
    return extractContent(line, before, ".");
}

std::string macroConfig::readBluestacksConf(const std::string& lineparameter)
{
    return readString(blue.blueStacksConfigPath, lineparameter, "\"", "\"");
}

void macroConfig::resetMacroConfig()
{
    initBasic();
}

std::vector<Instance> macroConfig::returnInstancesHasGame()
{

    for (Instance& inst : blue.BluestacksInstances) {
        if (inst.hasgame)hasGameInst.push_back(inst);
    }
    return hasGameInst;
}

void macroConfig::updateBlueStacksConfAdbPort(Instance& inst)
{
    inst.port = stoi(readBluestacksConf("bst.instance." + inst.EngineName + ".status.adb_port"));
}

std::string macroConfig::readLineMcFile(const std::string& lineparameter)
{
    return readString(mcfile, lineparameter, "\"", "\"");
}



void macroConfig::initAllBluestacksInstances()
{
    for (const std::string& engine : blue.Engines) {
        readBlueStacksConfInstanceCar(blue.blueStacksConfigPath, engine);
    }
}


void macroConfig::findAllBlueStacksEngines()
{
    std::string text = copyBlueStacksConf();
    std::vector<std::string>allocc = findAllOccurences(text, "bst.instance.");
    bool present = false;
    for (std::string& all : allocc) {
        std::string res = extractContent(all, "bst.instance.", ".");
        for (std::string& eng : blue.Engines) {
            if (res == eng) {
                present = true;
                break;
            }
            else present = false;
        }
        if (!present)blue.Engines.push_back(res);
    }
    blue.nbInstances = blue.Engines.size();
}

std::string macroConfig::cropText(const std::string& text, size_t pos)
{
    return text.substr(pos, std::string::npos - pos);
}

std::vector<std::string> macroConfig::findAllOccurences(const std::string& text, const std::string& lineParameter)
{
    std::vector<std::string> allocc;
    allocc.clear();
    size_t pos = 0;
    size_t endPos = 0;
    std::string newtext = text;
    while (pos != std::string::npos) {
        newtext = cropText(newtext, pos);
        pos = newtext.find(lineParameter);
        if (pos != std::string::npos) {
            std::string line = returnLineParam(newtext, lineParameter);
            pos += line.length();
            allocc.push_back(line);
        }

    }
    return allocc;
}







std::vector<std::string> macroConfig::readAllmcfileEngines(const std::string& filename)
{
    std::string line;
    for (int i = 1; i < blue.nbInstances + 1; ++i) {
        std::string before = "bst.engine." + std::to_string(i);
        blue.Engines.push_back(readString(filename, before, "\"", "\""));
    }
    return blue.Engines;
}


int macroConfig::readmcfileNbInstances(const std::string& filename)
{
    std::string line;
    std::string before = "bst.nbinstance";
    blue.nbInstances = readInt(filename, before, "\"", "\"");
    return blue.nbInstances;

}

void macroConfig::readMcfilefavouriteInstance()
{
    favouriteInstanceid = readStringMcfile("macro.favourite.id");
}

void macroConfig::readMcfilefavouritePreset()
{
    favouritePreset = readStringMcfile("macro.favourite.preset");
}

std::vector<std::string> macroConfig::readAllmcfileEnginesName(const std::string& filename)
{
    std::string line;
    for (int i = 1; i < blue.nbInstances + 1; ++i) {
        std::string before = "bst.engine." + std::to_string(i);
        blue.Engines.push_back(readString(filename, before, "\"", "\""));
    }
    return blue.Engines;
}

void macroConfig::readBlueStacksConfInstanceCar(const std::string& filename, std::string Enginename)
{
    Instance newInstance;
    std::string before = "bst.instance." + Enginename + ".";
    newInstance.EngineName = Enginename;
    newInstance.nbinstance = blue.BluestacksInstances.size() + 1;
    newInstance.InstanceName = readString(filename, before + "display_name", "\"", "\"");
    newInstance.width = readInt(filename, before + "fb_width", "\"", "\"");
    newInstance.height = readInt(filename, before + "fb_height", "\"", "\"");
    newInstance.boot = readInt(filename, before + "boot_duration", "\"", "\"");
    newInstance.port = readInt(filename, before + "status.adb_port", "\"", "\"");
    newInstance.id = readString(filename, before + "android_id", "\"", "\"");
    blue.BluestacksInstances.push_back(newInstance);
}

void macroConfig::showEngines()
{
    for (int i = 0; i < blue.Engines.size(); ++i)std::cout << blue.Engines.at(i) << std::endl;
}

void macroConfig::showBluestacksInstances()
{
    std::cout << std::endl << std::endl << "NbInstances: " << blue.BluestacksInstances.size() << std::endl << std::endl;
    for (int i = 0; i < blue.BluestacksInstances.size(); i++) {
        showBlueStacksIntance(blue.BluestacksInstances.at(i));
    }
}

void macroConfig::showBlueStacksIntance(Instance& Inst) {

    std::cout << "Instance number: " << Inst.nbinstance << std::endl;
    std::cout << "Name of Instance: " << Inst.InstanceName << std::endl;
    std::cout << "Name of Engine: " << Inst.EngineName << std::endl;
    std::cout << "Path: " << Inst.path << std::endl;
    std::cout << "Boot: " << Inst.boot << " ms" << std::endl;
    std::cout << "Port: " << Inst.port << std::endl;
    std::cout << "Hasgame: " << Inst.hasgame << std::endl;
    std::cout << "Width: " << Inst.width << std::endl;
    std::cout << "Height: " << Inst.height << std::endl;
    std::cout << "Id: " << Inst.id << std::endl;
    std::cout << std::endl << std::endl;
}

std::string macroConfig::copyMcfilecontent()
{
    return copytxtContent(mcfile);
}

void macroConfig::writeInitMcfile()
{
    std::string text;
    std::string datacollected = "datacollected=\"\"\n";
    std::string macropackage = "macropackage=\"\"\n";
    std::string macroactivity = "macroactivity=\"\"\n";
    std::string ldplayerinstalled = "ldplayerinstalled=\"\"\n";
    std::string bluestacksinstalled = "bluestacksinstalled=\"\"\n";
    std::string hdplayerpath = "bst.hdplayer.path=\"\"\n";
    std::string hdplayerfolder = "bst.hdplayer.folder=\"\"\n";
    std::string hdplayername = "bst.hdplayer.name=\"\"\n";
    std::string bstnbinstance = "bst.nbinstance=\"\"\n";
    std::string bstconfigpath = "bst.configfile.path=\"\"\n";
    std::string bstconfigfolder = "bst.configfile.folder=\"\"\n";
    std::string bstconfigname = "bst.configfile.name=\"\"\n";
    std::string favouriteinstance = "macro.favourite.id=\"\"\n";
    std::string favouritepreset = "macro.favourite.preset=\"\"\n";
    std::string endconfig = "EndBasicConfig\n";
    text = datacollected + macropackage + macroactivity + ldplayerinstalled + bluestacksinstalled
        + hdplayerpath + hdplayerfolder + hdplayername + bstnbinstance + bstconfigfolder + bstconfigpath + bstconfigname + favouriteinstance + favouritepreset + endconfig;
    sys.writeText(text, mcfile);
}

void macroConfig::fillInitMcfile()
{
    updateBool(mcfile, "datacollected=", 1, "\"", "\"");
    updateString(mcfile, "macropackage=", gamepackage, "\"", "\"");
    updateString(mcfile, "macroactivity=", gameactivity, "\"", "\"");
    updateBool(mcfile, "ldplayerinstalled=", 0, "\"", "\"");
    updateBool(mcfile, "bluestacksinstalled=", blue.isInstalled, "\"", "\"");
    updateString(mcfile, "bst.hdplayer.path=", blue.hdPlayerPath, "\"", "\"");
    updateString(mcfile, "bst.hdplayer.folder=", blue.hdPlayerFolder, "\"", "\"");
    updateString(mcfile, "bst.hdplayer.name=", blue.exename, "\"", "\"");
    updateInt(mcfile, "bst.nbinstance=", blue.nbInstances, "\"", "\"");
    updateString(mcfile, "bst.configfile.path=", blue.blueStacksConfigPath, "\"", "\"");
    updateString(mcfile, "bst.configfile.folder=", blue.blueStacksConfigFolder, "\"", "\"");
    updateString(mcfile, "bst.configfile.name=", blue.confname, "\"", "\"");
    updateString(mcfile, "macro.favourite.id=", "", "\"", "\"");
    updateString(mcfile, "macro.favourite.preset=", "", "\"", "\"");
}

void macroConfig::updateFavouriteInstance(Instance& inst)
{
    updateString(mcfile, "macro.favourite.id=", inst.id, "\"", "\"");
}

void macroConfig::updateFavouritePreset(const std::string& preset)
{
    updateString(mcfile, "macro.favourite.preset=", preset, "\"", "\"");
}

void macroConfig::initAllInstanceMcfile()
{
    std::string text = copyBasicConfigInfo();
    std::string allinst;
    for (Instance& inst : blue.BluestacksInstances) {
        allinst += initInstanceMcfile(inst);
    }
    sys.writeText(text + allinst, mcfile);
}

void macroConfig::updatePortMcfile(Instance& inst)
{
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateInt(mcfile, prefix + "port=", inst.port, "\"", "\"");
}
void macroConfig::updateHasGameMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateBool(mcfile, prefix + "hasgame=", inst.hasgame, "\"", "\"");
}
void macroConfig::updateIdMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateString(mcfile, prefix + "id=", inst.id, "\"", "\"");
}
void macroConfig::updateBootMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateInt(mcfile, prefix + "boot=", inst.boot, "\"", "\"");
}
void macroConfig::updatePathMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateString(mcfile, prefix + "path=", inst.path, "\"", "\"");
}
void macroConfig::updateWidthMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateInt(mcfile, prefix + "width=", inst.width, "\"", "\"");
}
void macroConfig::updateHeightMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateInt(mcfile, prefix + "height=", inst.height, "\"", "\"");
}
void macroConfig::updateEngineNameMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateString(mcfile, prefix + "enginename=", inst.EngineName, "\"", "\"");
}
void macroConfig::updateInstanceNameMcfile(Instance& inst) {
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateString(mcfile, prefix + "instancename=", inst.InstanceName, "\"", "\"");
}

void macroConfig::updateNbInstanceMcfile(Instance& inst)
{
    std::string prefix = "bst.instance." + inst.EngineName + ".";
    updateString(mcfile, prefix + "nbinstance=", inst.InstanceName, "\"", "\"");
}

void macroConfig::updateBluestacksConfInfoFromMcfile()
{
    blue.blueStacksConfigFolder = readStringMcfile("bst.configfile.folder");
    blue.blueStacksConfigPath = readStringMcfile("bst.configfile.path");
    blue.hdPlayerFolder = readStringMcfile("bst.hdplayer.folder");
    blue.hdPlayerPath = readStringMcfile("bst.hdplayer.path");
}

Instance macroConfig::choosePlayingInstance()
{
    std::cout << "Those are the instances with " << blue.gamepackage << " installed on it" << std::endl;
    for (int i = 0; i < hasGameInst.size(); ++i) {
        std::cout << "Instance " << i + 1 << ":" << std::endl;
        std::cout << "Name: " << hasGameInst.at(i).InstanceName << std::endl;
        std::cout << "Engine: " << hasGameInst.at(i).EngineName << std::endl;
        std::cout << std::endl;
    }
    if (hasGameInst.size() == 1) {
        favouriteInstanceid = hasGameInst.at(0).id;
        updateFavouriteInstance(hasGameInst.at(0));
    }
    int duration = 30;
    int timeleft;
    int nbFavInstance = 0;
    int nbRunningInstance = 0;
    std::string textseconds = "Seconds left: ";
    std::string strnb;
    bool choseFavInstance = false;
    bool choseInstance = false;
    std::cout << "Type C to enable Instance choice else favorite instance will be chosen" << std::endl;
    std::cout << "Type F to select Favorite Instance" << std::endl;
    std::cout << "Type R to reset Configuration" << std::endl;
    std::cout << "Type S to Skip" << std::endl;
    std::cout << "Validate your input with Enter" << std::endl;
    std::cout << "Type the number of the instance" << std::endl;
    std::cout << std::endl << textseconds;
    auto start = std::chrono::steady_clock::now();
    long long int elapsed = 0;
    long long int lastelapsed = elapsed;
    int maxchar = 0;
    int nbchar = 0;
    int lastnbchar = 0;
    int i = duration;
    while (i > 0) {
        i /= 10;
        maxchar++;
    }
    std::cout << duration;
    readMcfilefavouriteInstance();
    do {
        auto now = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        timeleft = duration - elapsed;
        if (lastelapsed != elapsed) {
            nbchar = 0;
            i = timeleft;
            while (i != 0) {
                i /= 10;
                nbchar++;
            }
            for (int j = 0; j < maxchar + textseconds.length(); ++j) {
                std::cout << "\b";
            }
            std::cout << textseconds;
            for (int j = 0; j < 2 * maxchar - nbchar; ++j) {
                std::cout << " ";
            }
            for (int j = 0; j < maxchar; ++j) {
                std::cout << "\b";
            }
            std::cout << timeleft;


            lastelapsed = elapsed;
        }

        if (ml.isKeyPressed(sf::Keyboard::C)) {
            while (!choseInstance) {
                std::cout << "\nNb between 1 and " << hasGameInst.size() << ": ";
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                std::cin >> strnb;
                for (int i = 0; i < strnb.size(); ++i) {
                    if (isdigit(strnb.at(i))) {
                        nbRunningInstance = strnb.at(i) - '0';
                        if ((nbRunningInstance) >= 1 && nbRunningInstance <= hasGameInst.size()) {
                            choseInstance = true;
                            std::this_thread::sleep_for(std::chrono::milliseconds(200));
                            break;
                        }
                    }
                }
            }
        }

        if (ml.isKeyPressed(sf::Keyboard::R)) {
            resetMacroConfig();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (ml.isKeyPressed(sf::Keyboard::F)) {
            while (!choseFavInstance) {
                std::cout << "\nNb between 1 and " << hasGameInst.size() << ": ";
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                std::cin >> strnb;
                for (int i = 0; i < strnb.size(); ++i) {
                    if (isdigit(strnb.at(i))) {
                        nbFavInstance = strnb.at(i) - '0';
                        if ((nbFavInstance) >= 1 && nbFavInstance <= hasGameInst.size()) {
                            choseFavInstance = true;
                            std::this_thread::sleep_for(std::chrono::milliseconds(200));
                            break;
                        }
                    }
                }
            }
            favouriteInstanceid = hasGameInst.at(nbFavInstance - 1).id;
            updateFavouriteInstance(hasGameInst.at(nbFavInstance - 1));
        }
        if (ml.isKeyPressed(sf::Keyboard::S)) {
            break;
        }

    } while (timeleft > 0 && !choseInstance);

    if (!choseInstance) {
        Instance favInstance = returnfavouriteInstance();
        if (favInstance.id == "") {
            std::cout << "\nFavorite Instance not defined launching first instance detected" << std::endl;
            return hasGameInst.at(0);
        }
        else return favInstance;
    }
    else return hasGameInst.at(nbRunningInstance - 1);

}


void macroConfig::updateInstanceMcfile(Instance& inst)
{
    updatePortMcfile(inst);
    updateInstanceNameMcfile(inst);
    updateEngineNameMcfile(inst);
    updateHeightMcfile(inst);
    updateWidthMcfile(inst);
    updatePathMcfile(inst);
    updateBootMcfile(inst);
    updateIdMcfile(inst);
    updateHasGameMcfile(inst);
    updateNbInstanceMcfile(inst);
}



void macroConfig::updateAllInstancesMcfile()
{
    for (Instance& inst : blue.BluestacksInstances) {
        updateInstanceMcfile(inst);
    }
}

std::string macroConfig::copyBasicConfigInfo()
{
    std::string text = copyMcfilecontent();
    std::string line = returnLineParam(text, "EndBasicConfig");

    return returnPartBeforeIncLine(text, line) + "\n";
}

void macroConfig::setDim(int dimx, int dimy)
{
    desiredX = dimx;
    desiredY = dimy;
}

std::string macroConfig::initInstanceMcfile(Instance& inst)
{
    std::string text;

    std::string prefix = "bst.instance." + inst.EngineName + ".";
    std::string EngineName = prefix + "enginename=\"\"\n";
    std::string InstanceName = prefix + "instancename=\"\"\n";
    std::string port = prefix + "port=\"\"\n";
    std::string boot = prefix + "boot=\"\"\n";
    std::string path = prefix + "path=\"\"\n";
    std::string width = prefix + "width=\"\"\n";
    std::string height = prefix + "height=\"\"\n";
    std::string nbinstance = prefix + "nbinstance=\"\"\n";
    std::string id = prefix + "id=\"\"\n";
    std::string hasgame = prefix + "hasgame=\"\"\n";
    return text = "\n" + EngineName + InstanceName + port + boot + path + width + height + nbinstance + id + hasgame;

}

void macroConfig::updateMcfileInstances()
{
    initAllInstanceMcfile();
    updateAllInstancesMcfile();
}



// command for ldplayer: "C:\LDPlayer\LDPlayer9\dnplayer.exe" index=1|


void macroConfig::initBlueStacksBasic()
{
    blue.findBlueStacks();

}

void macroConfig::updateBlueStacksInstances()
{
    updateBluestacksConfInfoFromMcfile();
    if (!sys.pathExists(blue.blueStacksConfigPath) || !sys.pathExists(blue.hdPlayerPath)) {
        std::cout << "Bluestacks config has changed, searching again" << std::endl;
        resetMacroConfig();
    }
    findAllBlueStacksEngines();
    initAllBluestacksInstances();
    blue.findAllInstancesPath();
    blue.findAllInstancesGame();
    updateMcfileInstances();
}

void macroConfig::initMacroConfig()
{
    if (!hasDataCollected()) {
        initBasic();
    }
    updateBlueStacksInstances();
    returnInstancesHasGame();
    playingInstance = choosePlayingInstance();
}



void macroConfig::initBasic()
{
    writeInitMcfile();
    initBlueStacksBasic();
    fillInitMcfile();
}








