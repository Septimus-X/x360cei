#ifndef TARGET_H
#define TARGET_H

#include "winapi.h"
#include "x360cefiles.h"

class Target
{
public:
	Target();
	~Target();

	bool link(const X360CEFiles &files);
	bool request();

private:
	Target(const Target &other);
	Target& operator=(const Target &other);

	static const TCHAR m_pszIni[];
	static const TCHAR m_pszX910[];
	static const TCHAR m_pszX11[];
	static const TCHAR m_pszX12[];
	static const TCHAR m_pszX13[];
	LPTSTR m_pszIniPath;
	LPTSTR m_pszX910Path;
	LPTSTR m_pszX11Path;
	LPTSTR m_pszX12Path;
	LPTSTR m_pszX13Path;
	static LPCTSTR m_pszDirFilter;

};

#endif // TARGET_H
