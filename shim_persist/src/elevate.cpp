#include <windows.h>
#include <stdio.h>

bool RunElevated(char *app_path)
{
    char operation[] = "runas";
    char run_path[MAX_PATH] = {0};
    ExpandEnvironmentStrings("%SystemRoot%\\system32\\rundll32.exe", (LPSTR)run_path, MAX_PATH);

    char cmd[MAX_PATH * 2] = {0};
    sprintf(cmd, "SHELL32.DLL,ShellExec_RunDLL \"%s\"", app_path);

    HINSTANCE hndl = ShellExecuteA(NULL, operation, run_path, cmd, NULL, SW_SHOWDEFAULT);
    if (hndl != NULL) {
        return true;
    }
    return false;
}

BOOL IsUserAdminMember()
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID SecurityIdentifier;
    if (!AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &SecurityIdentifier)) {
        return 0;
    }
    BOOL IsAdminMember;
    if (!CheckTokenMembership(NULL, SecurityIdentifier, &IsAdminMember)) {
        IsAdminMember = FALSE;
    }
    FreeSid(SecurityIdentifier);
    return IsAdminMember;
}
