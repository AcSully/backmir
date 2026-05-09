// platform_compat.h - Linux cross-validation Windows type/func compat
// Provides Linux stubs; does not affect Windows builds.
#pragma once
#ifndef _INC_PLATFORM_COMPAT_
#define _INC_PLATFORM_COMPAT_

// MSVC compatibility: snprintf not available before VS2015
#if defined(_MSC_VER) && _MSC_VER < 1900
#include <stdio.h>
#define snprintf _snprintf
#endif

#ifdef _WIN32
#  ifndef STDCALL
#    define STDCALL __stdcall
#  endif
#endif

#ifndef _WIN32

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// ��������
typedef unsigned char      BYTE;
typedef unsigned short     WORD;
typedef unsigned int       DWORD;
typedef unsigned int       UINT;
typedef int                BOOL;
typedef long               LONG;
typedef unsigned long      ULONG;
typedef long long          LONGLONG;
typedef unsigned long long ULONGLONG;
typedef void*              HANDLE;
typedef void*              HWND;
typedef unsigned short     USHORT;
typedef unsigned int       UINT32;
typedef uint64_t           UINT64;
typedef char               CHAR;
typedef wchar_t            WCHAR;
typedef const char*        LPCSTR;
typedef char*              LPSTR;
typedef void*              LPVOID;
typedef uintptr_t          WPARAM;
typedef intptr_t           LPARAM;
typedef unsigned int       LRESULT;

#ifndef TRUE
#  define TRUE  1
#endif
#ifndef FALSE
#  define FALSE 0
#endif
#ifndef NULL
#  define NULL  0
#endif

#define MAX_PATH 260

// Windows λ������
#define LOWORD(l)       ((WORD)(((DWORD)(l)) & 0xffff))
#define HIWORD(l)       ((WORD)((((DWORD)(l)) >> 16) & 0xffff))
#define LOBYTE(w)       ((BYTE)(((DWORD)(w)) & 0xff))
#define HIBYTE(w)       ((BYTE)((((DWORD)(w)) >> 8) & 0xff))
#define MAKELONG(lo,hi) ((DWORD)(((WORD)(lo)) | (((DWORD)((WORD)(hi))) << 16)))
#define MAKEWORD(lo,hi) ((WORD)(((BYTE)(lo)) | (((WORD)((BYTE)(hi))) << 8)))

// ����Լ����Linux �Ϻ��ԣ�
#define __stdcall
#define __cdecl
#define STDCALL
#define WINAPI
#define CALLBACK

// GetTickCount ���
#include <time.h>
static inline DWORD GetTickCount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (DWORD)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

// AllocConsole / freopen �� Linux ���ǿղ���
static inline BOOL AllocConsole() { return TRUE; }

// sprintf / vsprintf ���� stdio.h ��
// ZeroMemory
#define ZeroMemory(p, n) memset((p), 0, (n))
#define CopyMemory(d, s, n) memcpy((d), (s), (n))

// RECT
struct RECT { long left, top, right, bottom; };

// MSG (�򻯰�)
struct MSG {
    HWND   hwnd;
    UINT   message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD  time;
};

// winsock2.h stubs �� real socket types from POSIX headers
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef unsigned long  u_long;
#define FAR             // empty on Linux
typedef int            SOCKET;
#define INVALID_SOCKET  ((SOCKET)-1)
#define SOCKET_ERROR    (-1)

// _snprintf �� snprintf on Linux
#define _snprintf snprintf

// process.h stubs
#include <unistd.h>
#include <pthread.h>
static inline unsigned int GetCurrentThreadId() { return (unsigned int)(uintptr_t)pthread_self(); }

// Windows API stubs
static inline DWORD GetCurrentProcessId() { return (DWORD)getpid(); }
static inline HANDLE GetCurrentProcess()  { return (HANDLE)(intptr_t)getpid(); }
static inline HANDLE GetCurrentThread()   { return (HANDLE)(intptr_t)pthread_self(); }

// DbgHelp / exception stubs
typedef void* PEXCEPTION_POINTERS;
typedef long  NTSTATUS;
#define EXCEPTION_EXECUTE_HANDLER 1

// __declspec / __attribute__ mapping
#define __declspec(x)

// PostMessage stub (no-op on Linux)
static inline BOOL PostMessage(HWND, UINT, WPARAM, LPARAM) { return FALSE; }
static inline BOOL PostThreadMessage(DWORD, UINT, WPARAM, LPARAM) { return FALSE; }

// WaitForSingleObject stub (Linux uses pthread_join)
#define INFINITE 0xFFFFFFFF
static inline DWORD WaitForSingleObject(HANDLE h, DWORD) {
    if (h) pthread_join((pthread_t)(intptr_t)h, nullptr);
    return 0;
}

// WM_ constants used by server
#define WM_USER         0x0400

// SYSTEMTIME / GetLocalTime
#include <time.h>
struct SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay;
    WORD wHour, wMinute, wSecond, wMilliseconds;
};
static inline void GetLocalTime(SYSTEMTIME* st) {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    st->wYear   = (WORD)(tm->tm_year + 1900);
    st->wMonth  = (WORD)(tm->tm_mon + 1);
    st->wDay    = (WORD)tm->tm_mday;
    st->wHour   = (WORD)tm->tm_hour;
    st->wMinute = (WORD)tm->tm_min;
    st->wSecond = (WORD)tm->tm_sec;
    st->wMilliseconds = 0;
    st->wDayOfWeek = (WORD)tm->tm_wday;
}

// _vsnprintf �� vsnprintf
#define _vsnprintf vsnprintf

// Debug macros (no-op on Linux)
#define _CrtCheckMemory() (1)
#ifndef ASSERT
#  include <assert.h>
#  define ASSERT assert
#endif

// OutputDebugString stub
static inline void OutputDebugStringA(const char*) {}
#define OutputDebugString OutputDebugStringA

// SAFE_DELETE / SAFE_DELETE_ARRAY
#ifndef SAFE_DELETE
#  define SAFE_DELETE(p) do { delete (p); (p) = nullptr; } while(0)
#endif
#ifndef SAFE_DELETE_ARRAY
#  define SAFE_DELETE_ARRAY(p) do { delete[] (p); (p) = nullptr; } while(0)
#endif

// Winsock stubs (Linux uses POSIX sockets directly)
struct WSADATA { int dummy; };
static inline int WSAStartup(WORD, WSADATA*) { return 0; }
static inline int WSACleanup() { return 0; }

// MessageBox stub
#define MB_OK           0x00000000
#define MB_ICONERROR    0x00000010
#define MB_TASKMODAL    0x00002000
static inline int MessageBox(HWND, const char* text, const char* caption, UINT) {
    fprintf(stderr, "[ALERT] %s: %s\n", caption ? caption : "", text ? text : "");
    return 0;
}
static inline int MessageBoxA(HWND h, const char* t, const char* c, UINT u) { return MessageBox(h, t, c, u); }

// File-find API stubs (_findfirst / _findnext / _findclose)
#include <dirent.h>
#include <sys/stat.h>
#define _A_SUBDIR 0x10
struct _finddata_t {
    unsigned attrib;
    char name[260];
};
struct _FindHandle {
    DIR* dir;
    char pattern[260];
};
static inline intptr_t _findfirst(const char* spec, struct _finddata_t* fd) {
    // strip trailing wildcard to get directory path
    char dir_path[260];
    strncpy(dir_path, spec, 259); dir_path[259] = '\0';
    char* last_sep = strrchr(dir_path, '/');
    if (!last_sep) last_sep = strrchr(dir_path, '\\');
    if (last_sep) *last_sep = '\0'; else strcpy(dir_path, ".");
    DIR* d = opendir(dir_path);
    if (!d) return -1;
    _FindHandle* h = new _FindHandle;
    h->dir = d;
    strncpy(h->pattern, dir_path, 259);
    // read first entry
    struct dirent* ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;
        strncpy(fd->name, ent->d_name, 259);
        char full[520]; snprintf(full, sizeof(full), "%s/%s", dir_path, ent->d_name);
        struct stat st; stat(full, &st);
        fd->attrib = S_ISDIR(st.st_mode) ? _A_SUBDIR : 0;
        return (intptr_t)h;
    }
    closedir(d); delete h; return -1;
}
static inline int _findnext(intptr_t handle, struct _finddata_t* fd) {
    _FindHandle* h = (_FindHandle*)handle;
    struct dirent* ent;
    while ((ent = readdir(h->dir)) != NULL) {
        if (ent->d_name[0] == '.') continue;
        strncpy(fd->name, ent->d_name, 259);
        char full[520]; snprintf(full, sizeof(full), "%s/%s", h->pattern, ent->d_name);
        struct stat st; stat(full, &st);
        fd->attrib = S_ISDIR(st.st_mode) ? _A_SUBDIR : 0;
        return 0;
    }
    return -1;
}
static inline int _findclose(intptr_t handle) {
    _FindHandle* h = (_FindHandle*)handle;
    closedir(h->dir); delete h; return 0;
}

// _access -> access
#define _access access

// itoa stub
static inline char* itoa(int val, char* buf, int base) {
    if (base == 10) snprintf(buf, 32, "%d", val);
    else if (base == 16) snprintf(buf, 32, "%x", val);
    return buf;
}

// GetPrivateProfileInt stub (returns 0 on Linux)
static inline int GetPrivateProfileInt(const char*, const char*, int def, const char*) { return def; }

#endif // !_WIN32
#endif // _INC_PLATFORM_COMPAT_
