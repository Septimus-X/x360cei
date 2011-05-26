#include "application.h"
#include "x360cefiles.h"
#include "target.h"

INT Application()
{
	DWORD dw = GetCurrentDirectory(0, NULL);
	LPTSTR cw = (LPTSTR)HeapAlloc( GetProcessHeap(), 0, (dw+1)*sizeof(TCHAR) );
	dw = GetCurrentDirectory(dw, cw);
	X360CEFiles files(cw, dw);
	HeapFree( GetProcessHeap(), 0, cw );

	if( files.exist() ) {
		Target target;
		if( target.request() ) {
			if( target.link(files) )
				MessageBox( NULL, TEXT("x360ce links created successfully!"), TEXT("x360ce installer"), MB_OK );
			else {
				LPTSTR s;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, (LPTSTR)&s, 0, NULL);
				MessageBox( NULL, s, TEXT("x360ce installer ERROR"), MB_OK );
				LocalFree(s);
			}
		}
	} else
		MessageBox( NULL, TEXT("x360ce files missing!"), TEXT("x360ce installer"), MB_OK );

	return 0;
}
