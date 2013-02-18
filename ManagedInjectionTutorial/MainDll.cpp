#include <Windows.h>
#include <mscoree.h>
#include <metahost.h>
#include <wchar.h>
#include <fstream>

#pragma comment(lib, "mscoree.lib")

DWORD WINAPI Inject_Thread(LPVOID lpParam)
{       
    ICLRMetaHost * lpMetaHost = NULL;
    HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost,
	  (LPVOID *)&lpMetaHost);

    ICLRRuntimeInfo * lpRuntimeInfo = NULL;

    hr = lpMetaHost->GetRuntime(
        L"v4.0.30319", 		// Версия фреймворка
        IID_ICLRRuntimeInfo,
        (LPVOID *)&lpRuntimeInfo);
    
    ICLRRuntimeHost * lpRuntimeHost = NULL;
    hr = lpRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,
        (LPVOID *)&lpRuntimeHost);
    
    hr = lpRuntimeHost->Start();

    DWORD dwRetCode = 0;
    hr = lpRuntimeHost->ExecuteInDefaultAppDomain(
        L"C:\\ManagedApp.dll",  // Абсолютный путь к сборке
        L"ManagedApp.Program",	// Пространство имен и класс
        L"EntryPoint",			// Имя статического метода
        L"<Пример>",			// Параметры метода
        &dwRetCode);
	MessageBox(0, "OK", "OK", MB_OK);
    return 0;
}


DWORD APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, Inject_Thread, NULL, NULL, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	default:
		break;
	}
	return true;
}