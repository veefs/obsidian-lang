#pragma once
#include "Tokens.h"
#include <fstream>

void Interpret(const std::vector<Tokens>& tokens, std::ofstream& outputFile);