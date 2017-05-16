#pragma once

#include <windows.h>
#include <stdio.h>
#include "resource.h"

BOOL writeToFile(char* res_data, DWORD res_size, char *payloadName);

BOOL dropResource(char *payloadName);