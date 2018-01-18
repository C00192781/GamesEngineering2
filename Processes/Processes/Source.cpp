#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <cstring>

using namespace std;

#define TEXT


void Coordinator()
{
	string path = ""; // add in once Worker class is added 

	// Specifies the window station, desktop, standard handles, and appearance of the main window for a process at creation time.
	// [in] parameter
	STARTUPINFO info;

	// Fills a block of memory with zeros.
	ZeroMemory(&info, sizeof(info));
	info.cb = sizeof info; //Only compulsory field


	// PROCESS_INFORMATION structure - receives identification information about the new process.
	// what we get as an[out] parameter
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&processInfo, sizeof(processInfo));
 
	// Pass in path to Worker class
	if (CreateProcess(TEXT(path), NULL,
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
		NULL, &info, &processInfo))
	{
		
	}


	// matrices
	double a[3][3] = 
	   { 8, 7, 9,
		 5, 8, 4,
		 9, 4, 6 };


	double b[3][3] = 
	  { 4, 9, 5,
		8, 9, 5,
		5, 6, 4 };


	double c[3][3];


}


int main()
{
	system("PAUSE");
}