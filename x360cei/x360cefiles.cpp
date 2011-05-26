#include "x360cefiles.h"

const TCHAR x360ceFiles::m_pszDll[] = TEXT("xinput1_3.dll");
const TCHAR x360ceFiles::m_pszIni[] = TEXT("x360ce.ini");

x360ceFiles::x360ceFiles(LPTSTR pszPath, size_t cchPath)
{
	int i = sizeof(m_pszDll);
	size_t cbPath = cchPath*sizeof(TCHAR);

	this->m_pszDllPath = static_cast<LPTSTR>( HeapAlloc( GetProcessHeap(), 0, 2*( sizeof(TCHAR)+cbPath )+sizeof(m_pszDll)+sizeof(m_pszIni) ) );
	this->m_pszIniPath = this->m_pszDllPath + cchPath + sizeof(m_pszDll)/sizeof(TCHAR) + 1;

	StringCbCopy(this->m_pszDllPath, cbPath+sizeof(m_pszDll), pszPath);
	StringCbCopy(this->m_pszIniPath, cbPath+sizeof(m_pszIni), pszPath);

	this->m_pszDllPath[cchPath] = TEXT('\\');
	this->m_pszIniPath[cchPath] = TEXT('\\');

	StringCbCopy(this->m_pszDllPath+cchPath+1, sizeof(m_pszDll), this->m_pszDll);
	StringCbCopy(this->m_pszIniPath+cchPath+1, sizeof(m_pszIni), this->m_pszIni);
}

x360ceFiles::~x360ceFiles()
{
	HeapFree( GetProcessHeap(), 0, m_pszDllPath );
}

bool x360ceFiles::exist() const
{
	HANDLE h = NULL;

	h = CreateFile(this->m_pszDllPath, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( h == INVALID_HANDLE_VALUE )
		return false;
	CloseHandle(h);

	h = CreateFile(this->m_pszIniPath, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( h == INVALID_HANDLE_VALUE )
		return false;
	CloseHandle(h);

	return true;
}
