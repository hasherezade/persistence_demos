#pragma once

#include <windows.h>

bool join_strings(IN char* str1, IN const char* str2, IN OPTIONAL char* delimiter, OUT char outPath[MAX_PATH]);
bool create_new_process(PROCESS_INFORMATION& pi, LPSTR appPath, LPSTR cmdLine, LPSTR startDir = NULL);
bool make_install_folder(IN char* rootPath, const char* installFolder, OUT char installPath[MAX_PATH]);

