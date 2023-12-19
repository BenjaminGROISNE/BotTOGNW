#include "sysCommands.h"




void sysCommands::launchEmulator(const std::string& programPath, const std::string& exeName) {
    std::string command = "cd /d \"" + programPath + "\" && start \"\" " + exeName;
    doPipe(command);
}

void sysCommands::launchBluestacksInstance(const std::string& programPath, const std::string& instanceName) {
    std::string command = "cd /d \"" + programPath + "\" && start \"\" \"HD-Player.exe\" --instance \"" + instanceName + "\"";
    doPipe(command);
}
void sysCommands::shutdownEmulator(const std::string& appname) {
    std::string command = "taskkill /IM " + appname + " /T /F > nul 2>&1";
    doPipe(command);
}
void sysCommands::shutdownInstance(const std::string& appname, const std::string& nameInstance) {
    std::string command = "taskkill /FI \"WINDOWTITLE eq " + nameInstance + "\" /IM \"" + appname + "\" /F";
    doPipe(command);
}


sysCommands::sysCommands()
{
    port.clear();
}

void sysCommands::setPort(int port)
{
    this->port = std::to_string(port);
}
void sysCommands::setPort(std::string port)
{
    this->port = port;
}

std::vector<std::string> sysCommands::returnAllDrivesLetter()
{
    int disk = GetLogicalDrives();
    std::string disks = std::bitset<8>(disk).to_string();
    reverse(disks.begin(), disks.end());
    std::vector<std::string> letters;
    for (int i = 0; i < disks.size(); ++i) {
        if (disks.at(i) != '0') {
            char let = 'A' + i;
            std::string letter = std::string(1, let);
            letters.push_back(letter);
        }
    }

    return letters;
}

bool sysCommands::IsBlueStacksRunning() {
    const std::string bluestacksProcessName = "HD-Player.exe";
    const std::string command = "tasklist /FI \"IMAGENAME eq " + bluestacksProcessName + "\"";
    std::string result = receivePipe(command);
    if (result.find(bluestacksProcessName) != std::string::npos) {
        return true;
    }
    return false;
}

bool sysCommands::IsInstanceRunning(const std::string& name) {
    const std::string bluestacksProcessName = "HD-Player.exe";
    const std::string command = "tasklist /FI \"IMAGENAME eq " + bluestacksProcessName + "\" /FI \"WINDOWTITLE eq " + name + "\"";

    std::string result = receivePipe(command);
    if (result.find(bluestacksProcessName) != std::string::npos) {
        return true;
    }
    return false;
}




bool sysCommands::findPipe(const std::string& command, const std::string& parameter)
{
    std::array<char, 4000>buffer;
    std::string result;
    result.clear();
    FILE* pipe = nullptr;
    openPipe(command, pipe);
    bool foundString = false;
    while (!foundString && fgets(buffer.data(), buffer.size(), pipe))
    {
        result += buffer.data();
        if (result.find(parameter) != std::string::npos)return true;
    }
    closePipe(pipe);
    return false;
}

bool sysCommands::findPipeTime(const std::string& command, const std::string& parameter, int seconds)
{
    std::array<char, 4000> buffer;
    std::string result;
    result.clear();
    FILE* pipe = nullptr;
    openPipe(command, pipe);
    bool foundString = false;
    std::chrono::time_point start = std::chrono::steady_clock::now();

    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - start).count();
        if (elapsedTime > seconds) {
            break;
        }
        if (fgets(buffer.data(), buffer.size(), pipe) == nullptr) break;
        result += buffer.data();
        if (result.find(parameter) != std::string::npos) {
            foundString = true;
            std::cout << "Found parameter in: " << buffer.data() << std::endl;
            break;
        }
    }
    closePipe(pipe);
    return foundString;
}


std::chrono::time_point<std::chrono::steady_clock> sysCommands::startChrono() {
    return std::chrono::steady_clock::now();
}

long int sysCommands::endChrono(const std::chrono::time_point<std::chrono::steady_clock>& startTime) {
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
    return duration.count();
}

bool sysCommands::findPipeTimeNoclose(const std::string& command, const std::string& parameter, int seconds, FILE*& pipe)
{
    std::array<char, 4000> buffer;
    std::string result;
    result.clear();
    pipe = nullptr;
    openPipe(command, pipe);
    bool foundString = false;
    std::chrono::time_point start = std::chrono::steady_clock::now();
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - start).count();
        if (elapsedTime > seconds) {
            std::cout << "String not found in " << seconds << " seconds" << std::endl;
            break;
        }

        if (fgets(buffer.data(), buffer.size(), pipe) == nullptr) {
            break;
        }

        result += buffer.data(); // Append the current buffer to the result.

        if (result.find(parameter) != std::string::npos) {
            foundString = true;
            std::cout << "Found parameter in: " << buffer.data() << std::endl;
            break;
        }
    }
    return foundString;
}

std::string sysCommands::getParentDirectory() {
    std::filesystem::path currentFilePath(__FILE__);
    return currentFilePath.parent_path().string();
}

void sysCommands::writeFilesDirectory(std::filesystem::directory_iterator path, std::ofstream& fileContent, std::ofstream& fileDeclaration) {

    std::filesystem::path currentPath = path->path().parent_path();
    std::string folderName = currentPath.filename().string();
    std::string com = "//" + folderName + "\n";
    std::string FOLDEROUTPUTCONTENT = com + "std::string " + folderName + " = " + currentPath.parent_path().filename().string() + " + \"" + folderName + "\\\\" + "\";\n";
    std::string FOLDEROUTPUTDECLARATION = com + "extern std::string " + folderName + ";\n";
    fileContent << "\n" << FOLDEROUTPUTCONTENT;
    fileDeclaration << "\n" << FOLDEROUTPUTDECLARATION;
    std::vector<std::filesystem::directory_entry> folders;
    folders.clear();
    for (const auto& entry : path) {
        if (entry.is_regular_file()) {

            std::string filenameContent = "std::string " + entry.path().stem().string() + " = " + folderName + " + " + "\"" + entry.path().filename().string() + "\";" + "\n";
            std::string filenameDeclaration = "extern std::string " + entry.path().stem().string() + ";\n";
            fileContent << filenameContent;
            fileDeclaration << filenameDeclaration;
        }
        else if (entry.is_directory()) {
            folders.push_back(entry);
        }
    }
    for (int i = 0; i < folders.size(); i++) {
        if (!std::filesystem::is_empty(folders.at(i).path())) {
            writeFilesDirectory(std::filesystem::directory_iterator(folders.at(i).path()), fileContent, fileDeclaration);
        }
        else {
            std::filesystem::path currentPath = folders.at(i).path();

            std::string folderName = currentPath.filename().string();
            std::string com = "//" + folderName + "\n";
            std::string FOLDEROUTPUTCONTENT = "\n" + com + "std::string " + folderName + " = " + currentPath.parent_path().filename().string() + " + \"" + folderName + "\\\\" + "\";" + "\n";
            std::string FOLDEROUTPUTDECLARATION = "\n" + com + "extern std::string " + folderName + ";\n";
            fileContent << FOLDEROUTPUTCONTENT;
            fileDeclaration << FOLDEROUTPUTDECLARATION;
        }
    }
}



void sysCommands::createpaths(std::string rootFolder) {
    std::ofstream pathsContent("pathsContent.txt");
    std::ofstream pathsDeclaration("pathsDeclaration.txt");
    std::string path = rootFolder;
    std::filesystem::directory_iterator dir(path);
    writeFilesDirectory(dir, pathsContent, pathsDeclaration);
    pathsContent.close();
    pathsDeclaration.close();
}


std::string sysCommands::findPathFolder(const std::string& folder, const std::string& namefile)
{
    std::string result = "";
    bool found = false;
    std::filesystem::path folderpath(folder);
    std::cout << "\nSearching for " << namefile << " from " << folder << " folder" << std::endl;
    findPathFolderRec(folderpath, namefile, result, found);
    return result;
}

bool sysCommands::findFileFolder(const std::string& folder, const std::string& namefile)
{
    std::string result = "";
    bool found = false;
    std::filesystem::path folderpath(folder);
    findPathFolderRec(folderpath, namefile, result, found);
    return !result.empty();
}

void sysCommands::writeText(const std::string& text, const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
    }
}

bool sysCommands::pathExists(const std::string& path)
{
    std::filesystem::directory_entry dir(path);
    return dir.exists();
}

bool sysCommands::openPipe(const std::string& command, FILE*& pipe)
{


    pipe = _popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Error: Failed to open pipe for command: " << command << std::endl;
        return false;;
    }
    else return true;

}

void sysCommands::closePipe(FILE*& pipe)
{
    _pclose(pipe);
}

void sysCommands::doPipe(const std::string& command)
{
    FILE* pipe;
    openPipe(command, pipe);
    closePipe(pipe);
}

std::string sysCommands::receivePipe(const std::string& command)
{
    std::array<char, 4000>buffer;
    std::string result;
    FILE* pipe;
    openPipe(command, pipe);

    while (fgets(buffer.data(), buffer.size(), pipe))
    {
        result += buffer.data();

    }
    closePipe(pipe);
    return result;
}

std::string sysCommands::doPipeNoclose(const std::string& command)
{
    std::array<char, 4000>buffer;
    std::string result;
    FILE* pipe;
    openPipe(command, pipe);
    return result;
}




std::string sysCommands::ExpandEnvironmentVariables(const std::string& inputPath) {

    DWORD bufferLength = ExpandEnvironmentStringsA(inputPath.c_str(), nullptr, 0);
    if (bufferLength == 0) {
        return "";
    }
    std::string expandedPath;
    expandedPath.resize(bufferLength);
    if (ExpandEnvironmentStringsA(inputPath.c_str(), &expandedPath[0], bufferLength) == 0) {
        return "";
    }
    size_t pos;
    pos = expandedPath.find('\0');
    while (pos != std::string::npos) {
        expandedPath.erase(pos, 1);
        pos = expandedPath.find('\0');
    }
    return expandedPath;
}

void sysCommands::GetRelativeResolution(int& width, int& height)
{
    RECT desktop;
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
}



void sysCommands::findPathFolderRec(std::filesystem::path folderpath, const std::string& namefile, std::string& correctpath, bool& found)
{
    std::vector<std::filesystem::path> paths;
    paths.clear();
    if (std::filesystem::exists(folderpath) && !folderpath.empty()) {
        try {
            std::filesystem::directory_iterator dirpath(folderpath);
            for (const auto& entry : dirpath) {
                paths.push_back(entry);
            }
        }
        catch (std::filesystem::filesystem_error const& ex)
        {
        }
        catch (const std::system_error& e) {}
    }
    for (int i = 0; i < paths.size() && found == false; ++i) {
        try {
            std::filesystem::directory_entry dirpath(paths.at(i));
            if (dirpath.is_regular_file()) {
                std::string result = paths.at(i).filename().string();
                if (result == namefile) {
                    correctpath = paths.at(i).parent_path().string();
                    found = true;
                }
                paths.erase(paths.begin() + i);
                i--;
            }
        }

        catch (std::filesystem::filesystem_error const& ex)
        {
        }
        catch (const std::system_error& e) {}

    }
    for (int i = 0; i < paths.size() && found == false; ++i) {
        try {
            std::filesystem::directory_entry dirpath(paths.at(i));
            if (dirpath.is_directory()) {
                std::cout << "Folder: " << paths.at(i).string() << std::endl;
                findPathFolderRec(paths.at(i), namefile, correctpath, found);
            }
        }
        catch (std::filesystem::filesystem_error const& ex)
        {
        }
        catch (const std::system_error& e) {}
        catch (std::exception e) {}
    }
}

std::string sysCommands::findNameFolder(const std::string& folder)
{
    std::filesystem::path name(folder);
    return name.filename().string();
}

std::string sysCommands::findNameAncestorFolder(const std::string& folder, int number)
{
    std::filesystem::path name(folder);
    for (int i = 0; i < number; ++i) {
        name = name.parent_path();
    }
    return name.filename().string();

}

void sysCommands::bringWindowToFront(HWND hwnd) {

    if (hwnd == NULL || !IsWindow(hwnd) || !IsWindowVisible(hwnd)) {
        std::cerr << "Error: Invalid or invisible window handle!" << std::endl;
        return;
    }
    if (IsIconic(hwnd)) {
        ShowWindow(hwnd, SW_RESTORE);
    }
    SetForegroundWindow(hwnd);
}



