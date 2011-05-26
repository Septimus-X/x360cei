#ifndef x360ceFILES_H
#define x360ceFILES_H

#include "winapi.h"

class x360ceFiles {
public:
	x360ceFiles(LPTSTR pszPath, size_t cchPath);
	~x360ceFiles();

	LPCTSTR dllPath() const
	{ return this->m_pszDllPath; }
	bool exist() const;
	LPCTSTR iniPath() const
	{ return this->m_pszIniPath; }

private:
	x360ceFiles();
	x360ceFiles(const x360ceFiles &other);
	x360ceFiles& operator=(const x360ceFiles &other);

	static const TCHAR m_pszDll[];
	static const TCHAR m_pszIni[];
	LPTSTR m_pszDllPath;
	LPTSTR m_pszIniPath;
};

#endif // x360ceFILES_H
