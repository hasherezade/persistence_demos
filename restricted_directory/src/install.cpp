#include "install.h"
#include <iostream>

bool join_strings(IN char* str1, IN const char* str2, IN OPTIONAL char* delimiter, OUT char outPath[MAX_PATH])
{
    if (!str1 || !str2 || !outPath) {
        return false;
    }
    if (outPath != str1) {
        memset(outPath, 0, MAX_PATH);
        strcpy(outPath, str1);
    }
    if (delimiter) {
        strcat(outPath, delimiter);
    }
    strcat(outPath, str2);
    return true;
}

bool create_new_process(PROCESS_INFORMATION& pi, LPSTR appPath, LPSTR cmdLine, LPSTR startDir)
{
    STARTUPINFO si;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    memset(&pi, 0, sizeof(PROCESS_INFORMATION));

    if (!CreateProcessA(
        appPath,
        cmdLine,
        NULL, //lpProcessAttributes
        NULL, //lpThreadAttributes
        FALSE, //bInheritHandles
        DETACHED_PROCESS, //dwCreationFlags
        NULL, //lpEnvironment 
        startDir, //lpCurrentDirectory
        &si, //lpStartupInfo
        &pi //lpProcessInformation
    ))
    {
        std::cerr << "[ERROR] CreateProcess failed, Error = " << std::hex << GetLastError() << std::endl;
        return false;
    }
    return true;
}

bool make_install_folder(IN char* rootPath, const char* installFolder, OUT char installPath[MAX_PATH])
{
    CHAR cmd[MAX_PATH * 2] = { 0 };

    ExpandEnvironmentStringsA(rootPath, installPath, MAX_PATH);
    join_strings(installPath, installFolder, "\\", installPath);

    sprintf(cmd, " /C md\\\\.\\\"%s\"", installPath);

    CHAR cmdPath[MAX_PATH] = { 0 };
    ExpandEnvironmentStringsA("%SystemRoot%\\system32\\cmd.exe", cmdPath, MAX_PATH);

    PROCESS_INFORMATION pi = { 0 };
    if (create_new_process(pi, cmdPath, cmd, NULL)) {
        return true;
    }
    return false;
}
