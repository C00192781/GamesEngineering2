#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <cstring>

using namespace std;


void Coordinator(char cmdLine, TCHAR *argv[])
{
	//string path = "";
	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	int nStrBuffer = cmdLine.getLength();

	// Pass in path to Worker class
	if (CreateProcess(path,  cmdLine.GetBuffer(nStrBuffer), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}



}


int main()
{

}