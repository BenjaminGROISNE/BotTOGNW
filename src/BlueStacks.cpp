#include "BlueStacks.h"


Bluestacks::Bluestacks()
{
    isInstalled = false;
    nbInstances = 0;
    hdPlayerPath.clear();
    Engines.clear();
    blueStacksConfigPath.clear();
    hdPlayerFolder.clear();
    blueStacksConfigFolder.clear();
    BluestacksInstances.clear();
    gamepackage.clear();
    exename = "HD-Player.exe";
    confname = "bluestacks.conf";
}

Bluestacks::Bluestacks(std::string Gamepackage)
{
    isInstalled = false;
    nbInstances = 0;
    hdPlayerPath.clear();
    Engines.clear();
    blueStacksConfigPath.clear();
    hdPlayerFolder.clear();
    blueStacksConfigFolder.clear();
    BluestacksInstances.clear();
    gamepackage = Gamepackage;
    exename = "HD-Player.exe";
    confname = "bluestacks.conf";
}

void Bluestacks::sethdPlayerPath()
{
    hdPlayerPath = hdPlayerFolder + "\\HD-player.exe";
}

void Bluestacks::setConfigPath()
{
    blueStacksConfigPath = blueStacksConfigFolder + "\\bluestacks.conf";
}


void Bluestacks::findBlueStacks()
{
    std::vector<std::string>letters = sys.returnAllDrivesLetter();
    std::cout << "\nAll disks found:" << std::endl;
    for (std::string let : letters) {
        std::cout << let << std::endl;
    }
    std::string programDataBlue = sys.ExpandEnvironmentVariables("%ProgramData%") + "\\BlueStacks_nxt";
    std::string programData = sys.ExpandEnvironmentVariables("%ProgramData%");
    std::string programFiles = sys.ExpandEnvironmentVariables("%ProgramFiles%");
    std::string programFilesBlue = sys.ExpandEnvironmentVariables("%ProgramFiles%") + "\\BlueStacks_nxt";
    std::string programFiles86 = sys.ExpandEnvironmentVariables("%ProgramFiles(x86)%");

    hdPlayerFolder = sys.findPathFolder(programFilesBlue, "HD-Player.exe");
    if (hdPlayerFolder.empty()) {
        hdPlayerFolder = sys.findPathFolder(programFiles, "HD-Player.exe");
        if (hdPlayerFolder.empty()) {
            hdPlayerFolder = sys.findPathFolder(programFiles86, "HD-Player.exe");
            if (hdPlayerFolder.empty()) {
                for (std::string letter : letters) {
                    std::string fold = letter + ":\\";
                    hdPlayerFolder = sys.findPathFolder(fold, "HD-Player.exe");
                    if (!hdPlayerFolder.empty())break;
                }
            }
        }
    }

    blueStacksConfigFolder = sys.findPathFolder(programDataBlue, "bluestacks.conf");
    if (blueStacksConfigFolder.empty()) {
        blueStacksConfigFolder = sys.findPathFolder(programData, "bluestacks.conf");
        if (blueStacksConfigFolder.empty()) {
            for (std::string letter : letters) {
                std::string fold = letter + ":\\";
                blueStacksConfigFolder = sys.findPathFolder(fold, "bluestacks.conf");
                if (!blueStacksConfigFolder.empty())break;
            }
        }
    }
    std::cout << "============================================================================================" << std::endl;
    std::cout << "END OF SEARCH" << std::endl << std::endl;

    if (!blueStacksConfigFolder.empty() && !hdPlayerFolder.empty()) {
        setConfigPath();
        sethdPlayerPath();
        std::cout << "HD-Player Folder : " << hdPlayerFolder << std::endl;
        std::cout << "Config Folder : " << blueStacksConfigFolder << std::endl;
        isInstalled = true;
    }
    else throw 40;
}

bool Bluestacks::findGamePackage(const std::string& path, const std::string& packagename)
{
    std::string nameimg = packagename + ".png";
    std::string gamepath = path + "\\AppCache";
    if (sys.findFileFolder(gamepath, nameimg))return true;
    else return false;
}

void Bluestacks::findAllInstancesGame()
{
    for (Instance& inst : BluestacksInstances) {
        if (findGamePackage(inst.path, gamepackage)) {
            inst.hasgame = true;
        }
        else  inst.hasgame = false;
    }

}

void Bluestacks::findInstancePath(Instance& inst)
{
    std::string instancepath = blueStacksConfigFolder + "\\Engine\\" + inst.EngineName;
    if (sys.pathExists(instancepath)) {
        inst.path = instancepath;
    }
}

void Bluestacks::findAllInstancesPath()
{
    for (Instance& inst : BluestacksInstances) {
        findInstancePath(inst);
    }
}

void Bluestacks::startInstance(Instance inst)
{
    if (!sys.IsInstanceRunning(inst.InstanceName)) {
        std::cout << "PreviousBootTime: " << inst.boot << " milliseconds" << std::endl;
        sys.launchBluestacksInstance(hdPlayerFolder, inst.EngineName);
        wait(inst.boot * 2 + 5000);
    }


}

void Bluestacks::wait(int milliSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
}



Instance::Instance()
{
    EngineName = "";
    InstanceName = "";
    port = 0;
    boot = 0;
    path = "";
    width = 0;
    height = 0;
    nbinstance = 0;
    hasgame = 0;
}
