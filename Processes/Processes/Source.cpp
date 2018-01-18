#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

using namespace std;


void Coordinator(int argc, TCHAR *argv[])
{
	//string path = "";
	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	// Pass in path to Worker class
	if (CreateProcess(path, command, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}



}


int main()
{

}