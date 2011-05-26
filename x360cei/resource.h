#ifndef RESOURCE_H
#define RESOURCE_H

#include <WinVer.h>

#define	IDI_MAINICON	101

#define	VER_FILEVERSION				1,0,0,0
#define	VER_FILEVERSION_STR			"1.0\0"
#define VER_PRODUCTVERSION			1,0,0,0
#define VER_PRODUCTVERSION_STR		"1.0\0"
#define VER_COMPANYNAME_STR			"Jani\0"
#define VER_FILEDESCRIPTION_STR		"x360ce installer\0"
#define VER_ORIGINALFILENAME_STR	"x360cei.exe\0"
#define VER_PRODUCTNAME_STR			"x360ce installer\0"

#ifndef DEBUG
#define VER_DEBUG 0
#else
#define VER_DEBUG VS_FF_DEBUG
#endif

#endif // RESOURCE_H
