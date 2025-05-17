#pragma once
#include <iostream>
#include <limits>
#include <string>
void intInput(int& data,const std::string message, int start, int end);
void safeStringInput(std::string& input, const std::string& message);
void withoutSpacesInput(std::string& password, std::string message);