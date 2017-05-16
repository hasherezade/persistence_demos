#pragma once

#include <windows.h>

#include <stdio.h> 
#include <string>
#include <vector>
#include <map>
#include <set>

std::string getLocalClasses();

size_t hijackHandlers(std::string proxy_path);

std::set<std::string> getGlobalCommands();
size_t rewriteHandlers(std::string &local, std::set<std::string> &handlersSets);