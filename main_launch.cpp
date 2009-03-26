/*----------------------------------------------------------------------------
 * Copyright 2007  Kazuo Ishii <k-ishii@wb4.so-net.ne.jp>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *--------------------------------------------------------------------------*/
#define _WIN32_WINNT 0x600
#define WIN32_LEAN_AND_MEAN 1
#define UNICODE  1
#define _UNICODE 1
#include <Windows.h>
#pragma comment(linker, "/nodefaultlib:libcmt.lib")
#pragma comment(linker, "/nodefaultlib:libcmtd.lib")
#pragma comment(linker, "/subsystem:windows")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "User32.lib")

void* operator new(size_t n){ return HeapAlloc(GetProcessHeap(), 0, n);}
void  operator delete(void* p){ HeapFree(GetProcessHeap(), 0, p);}

bool send_command(HWND hwnd){
	LPWSTR  cmdline = GetCommandLine();
	WCHAR   workdir [MAX_PATH+8];
	DWORD   len = GetCurrentDirectory(MAX_PATH, workdir);
	struct{ DWORD  u0,u1; LPCWSTR p0,p1; } lp = {
		lstrlen(cmdline),
		len,
		cmdline,
		workdir,
	};
	LRESULT lr = SendMessage(hwnd, WM_USER+77, (WPARAM)GetCurrentProcessId(), (LPARAM)&lp);
	return (lr == 0x65676F68) ? true : false;
}

HWND find_parent_ck(){
	HWND  result = 0;
	//BOOL (WINAPI *attach)(DWORD) = (BOOL(WINAPI*)(DWORD)) GetProcAddress(GetModuleHandle(L"kernel32.dll"),"AttachConsole");
	//if(attach && attach(ATTACH_PARENT_PROCESS)){
	if(AttachConsole(ATTACH_PARENT_PROCESS)){
		DWORD  i = GetConsoleProcessList(&i,1);
		DWORD* pids = new DWORD[i+256];
		if(pids){
			DWORD nb = GetConsoleProcessList(pids,i);
			if(1<=nb && nb<=i){
				HWND  hwnd=0;
				DWORD pid, idx=nb;
				while(hwnd = FindWindowEx(HWND_MESSAGE, hwnd, L"ckApplicationClass", 0)){
					pid = 0;
					GetWindowThreadProcessId(hwnd, &pid);
					for(i=0; i < nb; i++){
						if(pids[i] == pid && idx > i){
							result = hwnd;
							idx = i;
						}
					}
				}
			}
			delete [] pids;
		}
		FreeConsole();
	}
	return result;
}


HRESULT startup(){
	HWND hwnd = find_parent_ck();
	if(hwnd && send_command(hwnd))
		return S_OK;

	WCHAR  image [MAX_PATH+8];
	DWORD  n = GetModuleFileName(0, image, MAX_PATH+4);
	if(n<1) return E_FAIL;

	for(; n>0 && image[n-1] != '\\'; n--);
	lstrcpy(image+n, L"ck.con.exe");

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	si.lpReserved = 0;
	si.lpDesktop = 0;
	si.lpTitle = 0;
	si.dwX = 0;
	si.dwY = 0;
	si.dwXSize = 0;
	si.dwYSize = 0;
	si.dwXCountChars = 0;
	si.dwYCountChars = 0;
	si.dwFillAttribute = 0;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.cbReserved2 = 0;
	si.lpReserved2 = 0;
	si.hStdInput = 0;
	si.hStdOutput = 0;
	si.hStdError = 0;

	pi.hProcess = 0;
	pi.hThread = 0;
	pi.dwProcessId = 0;
	pi.dwThreadId = 0;

	if(CreateProcess(image, GetCommandLine(), 0,0,FALSE, CREATE_DEFAULT_ERROR_MODE|CREATE_NEW_CONSOLE|CREATE_NEW_PROCESS_GROUP|NORMAL_PRIORITY_CLASS, 0,0,&si,&pi)){
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return S_OK;
	}
	return E_FAIL;
}

extern "C" void WinMainCRTStartup(){
	ExitProcess((UINT)startup());
}
//EOF
