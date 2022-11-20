#ifndef __MINWINDEF__
#define __MINWINDEF__
#include <tchar.h>
#include <basetyps.h>
#define far
#define near
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)
#define DECLARE_HANDLE(type) typedef void* type

#ifndef __cdecl
#define __cdecl __attribute__((__cdecl__))
#endif
#define WINAPI __cdecl

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;

DECLARE_HANDLE(HANDLE);
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HFILE);
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HSPRITE);
DECLARE_HANDLE(HLSURF);
DECLARE_HANDLE(HSTR);
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HWINSTA);
DECLARE_HANDLE(HKL);
typedef int* INT_PTR;

typedef INT_PTR (WINAPI *FARPROC)(void);
typedef INT_PTR (WINAPI *NEARPROC)(void);
typedef INT_PTR (WINAPI *PROC)(void);

HDC CreateRectDC(int width, int height);
#endif