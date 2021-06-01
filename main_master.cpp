#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#define SHAREMEM_NAME   "shareMemory"
#define BULID_MESSAGE   "Hello! I am burn at " __DATE__ " " __TIME__

//建立一小區塊並施行顯示在這份額外記憶體的時間日期
int main(int argc, char*argv[]){
    LPCTSTR pBuf;
    HANDLE hFile;
    int i;
    char szFileName[]= SHAREMEM_NAME;
    char writeBuffer[128]={0};

    //Open it if share memory had been created
    /*hFile = OpenFileMapping(  
         FILE_MAP_ALL_ACCESS,
         FALSE,
         szFileName   
    );*/

	//建立共用記憶體
    hFile = CreateFileMapping(
    	(HANDLE)0xFFFFFFFF,		//表示內存中開闢一個區塊
    	NULL,
    	PAGE_READWRITE,//讀取在一個區塊
    	0,
    	sizeof(writeBuffer),//代表一個內存中的二進制數據區塊正在累計讀入
		szFileName
	);	

    if(NULL == hFile){
        printf("Could not create file mapping object (%d)\n",GetLastError());
        return -1;     
    }
    
	//建立一個大小為1024bytes的分享記憶體
	//得到映射(位址)的記憶體
	pBuf=(LPCTSTR)MapViewOfFile(
		hFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(writeBuffer)
	);

    if(NULL == pBuf){
      	printf("Could not map view of file (%d)",GetLastError());
      	CloseHandle(hFile);
      	return -2;
    }
    
	//放入自己的位址空間
	//創造新的連結並顯示
	strcat((char*)pBuf,BULID_MESSAGE "\n");
	
	while(1){
		printf("%s\n",pBuf);
		Sleep(1000);
	}
	
	CloseHandle(hFile);

}
