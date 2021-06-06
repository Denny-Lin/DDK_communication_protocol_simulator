#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#pragma warning(disable : 4996)

#define SHAREMEM_NAME "c:shareMemory"

int main(int argc, char*argv[])
{
	LPCTSTR pBuf;
	HANDLE hFile;
	int i;
	char szFileName[] = SHAREMEM_NAME;
	char writeBuffer[128] = { 0 };

	//建立共用記憶體
	//宣告變數
	hFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		(LPCWSTR)szFileName
	);

	//開啟分享記憶體
	pBuf = (LPCTSTR)MapViewOfFile(
		hFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(writeBuffer)
	);

	//放入自己的位址空間
	while (1) {
		printf("%s\n", pBuf);
		Sleep(1000);
	}

	CloseHandle(hFile);
}
//顯示這份額外記憶的時間日期