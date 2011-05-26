#ifndef X360CEFILES_H
#define X360CEFILES_H

#include "winapi.h"

class X360CEFiles {
public:
	X360CEFiles(LPTSTR pszPath, size_t cchPath);
	~X360CEFiles();

	LPCTSTR dllPath() const
	{ return this->m_pszDllPath; }
	bool exist() const;
	LPCTSTR iniPath() const
	{ return this->m_pszIniPath; }

private:
	X360CEFiles();
	X360CEFiles(const X360CEFiles &other);
	X360CEFiles& operator=(const X360CEFiles &other);

	static const TCHAR m_pszDll[];
	static const TCHAR m_pszIni[];
	LPTSTR m_pszDllPath;
	LPTSTR m_pszIniPath;
};

#endif // X360CEFILES_H
