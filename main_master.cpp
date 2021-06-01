#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#define SHAREMEM_NAME   "shareMemory"
#define BULID_MESSAGE   "Hello! I am burn at " __DATE__ " " __TIME__

//�إߤ@�p�϶��ìI����ܦb�o���B�~�O���骺�ɶ����
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

	//�إߦ@�ΰO����
    hFile = CreateFileMapping(
    	(HANDLE)0xFFFFFFFF,		//��ܤ��s���}�P�@�Ӱ϶�
    	NULL,
    	PAGE_READWRITE,//Ū���b�@�Ӱ϶�
    	0,
    	sizeof(writeBuffer),//�N��@�Ӥ��s�����G�i��ƾڰ϶����b�֭pŪ�J
		szFileName
	);	

    if(NULL == hFile){
        printf("Could not create file mapping object (%d)\n",GetLastError());
        return -1;     
    }
    
	//�إߤ@�Ӥj�p��1024bytes�����ɰO����
	//�o��M�g(��})���O����
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
    
	//��J�ۤv����}�Ŷ�
	//�гy�s���s�������
	strcat((char*)pBuf,BULID_MESSAGE "\n");
	
	while(1){
		printf("%s\n",pBuf);
		Sleep(1000);
	}
	
	CloseHandle(hFile);

}
