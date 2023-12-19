#include "fadb.h"



fadb::fadb(int port1) {
    strport = std::to_string(port1);
    intport = port1;
}
fadb::fadb(std::string strport)
{
    this->strport = strport;
    intport = stoi(strport);
}
fadb::fadb() {
    strport.clear();
    intport = 0;
}
fadb::~fadb() {

}

void fadb::setPort(int intPort)
{
    intport = intPort;
    strport = std::to_string(intPort);
}

void fadb::setPort(std::string strPort)
{
    intport = stoi(strPort);
    strport = strPort;
}

void fadb::input(const std::string& inputcmd) {
    runAdbLocalhostShell("input " + inputcmd);
}

void fadb::touch(int x, int y) {
    std::string x_str = std::to_string(x);
    std::string y_str = std::to_string(y);
    std::string command = "tap " + x_str + " " + y_str;
    input(command);
}
void fadb::swipe(int x1, int y1, int x2, int y2, int delayMilliseconds) {
    std::string x1_str = std::to_string(x1);
    std::string y1_str = std::to_string(y1);
    std::string x2_str = std::to_string(x2);
    std::string y2_str = std::to_string(y2);
    std::string delay_str = std::to_string(delayMilliseconds);
    std::string command = "swipe " + x1_str + " " + y1_str + " " + x2_str + " " + y2_str + " " + delay_str;
    input(command);
}

int fadb::getPidLogcat() {
    return getPid("logcat");
}

std::string fadb::runAdbLocalhostShell(const std::string& command)
{
    return runAdbLocalhost("shell " + command);
}


std::string fadb::runAdbLocalhost(const std::string& command)
{
    std::string fullCommand = "-s localhost:" + strport + " " + command;
    return runAdb(fullCommand);
}

std::string fadb::runAdb(const std::string& command)
{
    std::string fullCommand = "adb " + command;
    return sys.receivePipe(fullCommand);
}

void fadb::getEmulatorDimensions(int& DIMX, int& DIMY) {
    std::string output = runAdbLocalhostShell("wm size");
    size_t xbegpos, xendpos, ybegpos, yendpos;
    std::string size = "size: ";
    xbegpos = output.find(size) + size.length();
    xendpos = output.find("x") - 1;
    ybegpos = output.find("x") + 1;
    yendpos = output.find('\n') - 1;
    if (xbegpos != std::string::npos && xendpos != std::string::npos && ybegpos != std::string::npos && yendpos != std::string::npos) {
        DIMX = stoi(output.substr(xbegpos, xendpos));
        DIMY = stoi(output.substr(ybegpos, yendpos));
    }
}

void fadb::launchPackage(std::string namepckg) {
    runAdbLocalhostShell("am start -n " + namepckg);
}
void fadb::quitPackage(std::string namepckg) {
    runAdbLocalhostShell("am force-stop " + namepckg);

}

void fadb::home() {
    input("keyevent KEYCODE_HOME");
}
void fadb::back() {
    input("keyevent KEYCODE_BACK");
}

void fadb::takeScreenshot(const std::string& filename) {
    std::string command = "exec-out screencap -p > ./assets/liveScreenshot/" + filename;
    runAdbLocalhost(command);
}

void fadb::screenshot() {
    takeScreenshot("screenshot.png");
}

void fadb::screenshotEvents() {
    takeScreenshot("screenshotEvents.png");
}

void fadb::screenshotBusy() {
    takeScreenshot("screenshotBusy.png");
}

void fadb::devices() {
    runAdb("devices");
}

void fadb::connectLocalhost(int portint)
{
    runAdb("connect localhost:" + std::to_string(portint));
}

void fadb::disconnectLocalhost(int port) {
    std::string strport = std::to_string(port);
    std::cout << "Trying to disconnect: ";
    runAdb("disconnect localhost:" + strport);
}

void fadb::setResolution(int x, int y, int dpi)
{
    std::string command1 = "wm size " + std::to_string(x) + "x" + std::to_string(y);
    std::string command2 = "wm density " + std::to_string(dpi);
    runAdbLocalhostShell(command1);
    runAdbLocalhostShell(command2);
}


void fadb::killAdb() {
    runAdb("kill-server");
}

int fadb::getPid(const std::string& process)
{
    std::string command = "pidof " + process;
    std::string result = runAdbLocalhostShell(command);
    if (result.empty())return -1;
    else return stoi(result);
}

std::vector<int> fadb::getMultPid(const std::string& process)
{
    std::string command = "pidof " + process;
    std::string result = runAdbLocalhostShell(command);
    std::vector<int>allpid;
    std::string nb;
    if (!result.empty()) {
        for (int i = 0; i < result.size(); ++i) {
            if (result.at(i) != ' ' && result.at(i) != '\n') {
                nb.push_back(result.at(i));
            }
            else if (!nb.empty()) {
                allpid.push_back(std::stoi(nb));
                nb.clear();
                if (result.at(i) == '\n')break;
            }
        }
    }
    std::cout << "stop";
    return allpid;
}

std::string fadb::currentFocus()
{
    std::string command = "\"dumpsys window windows | grep mCurrentFocus\"";
    return runAdbLocalhostShell(command);
}

void fadb::killPid(int pid)
{
    runAdbLocalhostShell("kill " + std::to_string(pid));
}

void fadb::killLogcat()
{
    std::vector<int> pids = getMultPid("logcat");
    for (int i : pids) {
        std::cout << "Pid: " << i << std::endl;
        killPid(i);
    }
}

bool fadb::StrLogTime(const std::string& searchString, int seconds) {
    std::string clearCommand = "logcat -c";  // Command to clear the logcat buffer
    std::string startlogcat = "adb -s localhost:" + strport + " logcat";
    runAdbLocalhost(clearCommand);
    FILE* pipe = nullptr;
    bool res = sys.findPipeTimeNoclose(startlogcat, searchString, seconds, pipe);
    return res;
}

bool fadb::packageRunning(std::string package)
{
    int pid = getPid(package);
    if (pid != -1)return true;
    else return false;

}

bool fadb::onPackage(std::string package)
{
    std::string focus = currentFocus();
    return (focus.find(package) != std::string::npos);
}




