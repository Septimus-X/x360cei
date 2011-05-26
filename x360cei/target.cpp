#include "target.h"

const TCHAR Target::m_pszIni[] = TEXT("x360ce.ini");
const TCHAR Target::m_pszX910[] = TEXT("xinput9_1_0.dll");
const TCHAR Target::m_pszX11[] = TEXT("xinput1_1.dll");
const TCHAR Target::m_pszX12[] = TEXT("xinput1_2.dll");
const TCHAR Target::m_pszX13[] = TEXT("xinput1_3.dll");

LPCTSTR Target::m_pszDirFilter = TEXT("Game executable (*.exe)\0*.exe\0All Files (*.*)\0*.*\0");

Target::Target()
	: m_pszIniPath(NULL)
{	

}

Target::~Target()
{
	if( this->m_pszIniPath ) {
		HeapFree( GetProcessHeap(), 0, this->m_pszIniPath );
		this->m_pszIniPath = NULL;
	}
}

bool Target::link(const X360CEFiles &files)
{
	BOOLEAN ret = TRUE;

	ret &= CreateSymbolicLink(this->m_pszIniPath, files.iniPath(), 0);
	ret &= CreateSymbolicLink(this->m_pszX910Path, files.dllPath(), 0);
	ret &= CreateSymbolicLink(this->m_pszX11Path, files.dllPath(), 0);
	ret &= CreateSymbolicLink(this->m_pszX12Path, files.dllPath(), 0);
	ret &= CreateSymbolicLink(this->m_pszX13Path, files.dllPath(), 0);

	return (ret == TRUE);
}

bool Target::request()
{
	bool ret = false;

	if( this->m_pszIniPath ) {
		HeapFree( GetProcessHeap(), 0, this->m_pszIniPath );
		this->m_pszIniPath = NULL;
	}

	OPENFILENAME ofn;
	SecureZeroMemory( &ofn, sizeof(OPENFILENAME) );

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = this->m_pszDirFilter;
	ofn.lpstrFile = static_cast<LPTSTR>( HeapAlloc( GetProcessHeap(), 0, MAX_PATH*sizeof(TCHAR) ) );
	*ofn.lpstrFile = TEXT('\0');
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	if( GetOpenFileName(&ofn) != 0 ) {
		DWORD cb = 5*ofn.nFileOffset*sizeof(TCHAR)
			+sizeof(m_pszIni)+sizeof(m_pszX910)+sizeof(m_pszX11)+sizeof(m_pszX12)+sizeof(m_pszX13);
		this->m_pszIniPath = static_cast<LPTSTR>( HeapAlloc( GetProcessHeap(), 0, cb ) );
		this->m_pszX910Path = this->m_pszIniPath + ofn.nFileOffset + sizeof(m_pszIni)/sizeof(TCHAR);
		this->m_pszX11Path = this->m_pszX910Path + ofn.nFileOffset + sizeof(m_pszX910)/sizeof(TCHAR);
		this->m_pszX12Path = this->m_pszX11Path + ofn.nFileOffset + sizeof(m_pszX11)/sizeof(TCHAR);
		this->m_pszX13Path = this->m_pszX12Path + ofn.nFileOffset + sizeof(m_pszX12)/sizeof(TCHAR);

		ofn.lpstrFile[ofn.nFileOffset] = TEXT('\0');

		DWORD cbPath = ofn.nFileOffset*sizeof(TCHAR);

		StringCbCopy(this->m_pszIniPath, cbPath+sizeof(m_pszIni), ofn.lpstrFile);
		StringCbCopy(this->m_pszX910Path, cbPath+sizeof(m_pszX910), ofn.lpstrFile);
		StringCbCopy(this->m_pszX11Path, cbPath+sizeof(m_pszX11), ofn.lpstrFile);
		StringCbCopy(this->m_pszX12Path, cbPath+sizeof(m_pszX12), ofn.lpstrFile);
		StringCbCopy(this->m_pszX13Path, cbPath+sizeof(m_pszX13), ofn.lpstrFile);

		StringCbCopy(this->m_pszIniPath+ofn.nFileOffset, sizeof(m_pszIni), this->m_pszIni);
		StringCbCopy(this->m_pszX910Path+ofn.nFileOffset, sizeof(m_pszX910), this->m_pszX910);
		StringCbCopy(this->m_pszX11Path+ofn.nFileOffset, sizeof(m_pszX11), this->m_pszX11);
		StringCbCopy(this->m_pszX12Path+ofn.nFileOffset, sizeof(m_pszX12), this->m_pszX12);
		StringCbCopy(this->m_pszX13Path+ofn.nFileOffset, sizeof(m_pszX13), this->m_pszX13);

		ret = true;
	}

	HeapFree( GetProcessHeap(), 0, ofn.lpstrFile );
	return ret;
}
