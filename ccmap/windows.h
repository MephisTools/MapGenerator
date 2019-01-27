#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <stdarg.h>


typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT;

#undef BOOL
typedef int BOOL;

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef VOID
#define VOID void
#endif

typedef void *PVOID,*LPVOID;
typedef WCHAR *LPWSTR;
typedef CHAR *LPSTR;
typedef TCHAR *LPTSTR;



#endif