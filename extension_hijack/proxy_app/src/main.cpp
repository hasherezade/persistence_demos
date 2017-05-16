#include <stdio.h>
#include <Windows.h>
#include <psapi.h>

#include <string>

HANDLE create_new_process(IN const char* path, IN const char* cmd)
{
    STARTUPINFOA si;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = 0;

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    
    if (!CreateProcessA(
        path,
        (LPSTR) cmd,
        NULL, //lpProcessAttributes
        NULL, //lpThreadAttributes
        FALSE, //bInheritHandles
        DETACHED_PROCESS  | CREATE_NO_WINDOW,
        NULL, //lpEnvironment 
        NULL, //lpCurrentDirectory
        &si, //lpStartupInfo
        &pi //lpProcessInformation
    ))
    {
        return NULL;
    }
    return pi.hProcess;
}

void deploy_payload()
{
    char full_path[MAX_PATH] = { 0 };
    char calc_path[] = "%SystemRoot%\\system32\\calc.exe";
    ExpandEnvironmentStrings(calc_path, full_path, MAX_PATH);
    create_new_process(full_path, NULL);
}

int main(int argc, char *argv[])
{
    std::string merged_args;
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            merged_args += std::string(argv[i]) + " ";
        }
        create_new_process(NULL, merged_args.c_str());
    }

    deploy_payload();
    return 0;
}