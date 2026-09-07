/*
 * winreg.h -- registry API for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs); per-page Requirements rows (OS Versions / Header /
 * Link Library) are transcribed in docs/inventory.md.  Header Winreg.h
 * is the Header row every CE registry page names.
 *
 * The registry on Windows CE is Unicode-only; like the rest of the CE
 * API the exported names are the wide spellings and the base names are
 * macros.  The predefined keys HKEY_CURRENT_CONFIG,
 * HKEY_PERFORMANCE_DATA and HKEY_DYN_DATA are NOT supported on CE and
 * are not defined here.
 */

#ifndef AKARI_WINREG_H
#define AKARI_WINREG_H

#include "windef.h"
#include "winbase.h"   /* FILETIME/PFILETIME, SECURITY_ATTRIBUTES tag */

#ifdef __cplusplus
extern "C" {
#endif

/* Registry key handles are opaque handles (a key object handle, like
 * every CE kernel object).  PHKEY is the output-handle pointer form
 * the function pages' signatures use.  REGSAM is the (ignored on CE)
 * requested-access mask type; CE pages say to pass 0. */
typedef HANDLE HKEY;
typedef HKEY  *PHKEY;
typedef DWORD  REGSAM;

/* Predefined reserved key-handle values (RegCreateKeyEx ms891450 and
 * the other registry pages name HKEY_CLASSES_ROOT / HKEY_CURRENT_USER
 * / HKEY_LOCAL_MACHINE / HKEY_USERS; the values are the fixed Win32
 * ABI predefined-handle values).  The same pages state Windows CE
 * does not support HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA or
 * HKEY_DYN_DATA, so those are not defined. */
#define HKEY_CLASSES_ROOT   ((HKEY) (LONG_PTR) 0x80000000)
#define HKEY_CURRENT_USER   ((HKEY) (LONG_PTR) 0x80000001)
#define HKEY_LOCAL_MACHINE  ((HKEY) (LONG_PTR) 0x80000002)
#define HKEY_USERS          ((HKEY) (LONG_PTR) 0x80000003)

/* Value-type codes returned by RegQueryValueEx's lpType (ms891462) and
 * accepted by RegSetValueEx's dwType (ms891469); values are the fixed
 * Win32 ABI value-type codes. */
#define REG_NONE               0
#define REG_SZ                 1
#define REG_EXPAND_SZ          2
#define REG_BINARY             3
#define REG_DWORD              4
#define REG_DWORD_LITTLE_ENDIAN 4
#define REG_DWORD_BIG_ENDIAN   5
#define REG_LINK               6
#define REG_MULTI_SZ           7
#define REG_RESOURCE_LIST      8

/* Key creation options (ms891450 dwOptions) and disposition results
 * (phkResult); values fixed Win32 ABI. */
#define REG_OPTION_NON_VOLATILE 0x00000000u
#define REG_OPTION_VOLATILE     0x00000001u
#define REG_CREATED_NEW_KEY     0x00000001u
#define REG_OPENED_EXISTING_KEY 0x00000002u

/* Registry change-notification filters (CeFindFirstRegChange
 * aa517116; values fixed Win32 ABI).  The CE page names only
 * REG_NOTIFY_CHANGE_NAME and REG_NOTIFY_CHANGE_LAST_SET; the other
 * desktop filter bits are not documented for CE and stay undefined. */
#define REG_NOTIFY_CHANGE_NAME     0x00000001u
#define REG_NOTIFY_CHANGE_LAST_SET 0x00000004u

/* ms891448 "RegCloseKey (Windows CE 5.0)":
 * LONG RegCloseKey(HKEY).  CE 1.0+; Winreg.h; Coredll.lib.  Releases
 * the handle of a key opened/created by the key functions above. */
LONG RegCloseKeyW(HKEY hKey);
#define RegCloseKey RegCloseKeyW

/* ms891460 "RegOpenKeyEx (Windows CE 5.0)":
 * LONG RegOpenKeyEx(HKEY, LPCWSTR, DWORD, REGSAM, PHKEY).  CE 1.0+;
 * Winreg.h; Coredll.lib.  Opens a subkey of hKey (which may be a
 * predefined key); ulOptions reserved (0); samDesired ignored (0 on
 * CE); ERROR_SUCCESS or a Winerror.h code.  Max key name 255 chars,
 * nesting 16 levels. */
LONG RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions,
                   REGSAM samDesired, PHKEY phkResult);
#define RegOpenKeyEx RegOpenKeyExW

/* ms891450 "RegCreateKeyEx (Windows CE 5.0)":
 * LONG RegCreateKeyEx(HKEY, LPCWSTR, DWORD, LPWSTR, DWORD, REGSAM,
 * LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD).  CE 1.0+; Winreg.h;
 * Coredll.lib.  Creates or opens a subkey; lpClass max 255 chars;
 * lpSecurityAttributes must be NULL on CE (default descriptor);
 * dwOptions REG_OPTION_NON_VOLATILE/VOLATILE; disposition in
 * lpdwDisposition when non-NULL. */
LONG RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved,
                     LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired,
                     LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                     PHKEY phkResult, LPDWORD lpdwDisposition);
#define RegCreateKeyEx RegCreateKeyExW

/* ms891451 "RegDeleteKey (Windows CE 5.0)":
 * LONG RegDeleteKey(HKEY, LPCWSTR).  CE 1.0+; Winreg.h; Coredll.lib.
 * Deletes a subkey (recursively on CE per page) of an open key. */
LONG RegDeleteKeyW(HKEY hKey, LPCWSTR lpSubKey);
#define RegDeleteKey RegDeleteKeyW

/* ms891452 "RegDeleteValue (Windows CE 5.0)":
 * LONG RegDeleteValue(HKEY, LPCWSTR).  CE 1.0+; Winreg.h; Coredll.lib.
 * Removes a named value. */
LONG RegDeleteValueW(HKEY hKey, LPCWSTR lpValueName);
#define RegDeleteValue RegDeleteValueW

/* ms891453 "RegEnumKeyEx (Windows CE 5.0)":
 * LONG RegEnumKeyEx(HKEY, DWORD, LPWSTR, LPDWORD, LPDWORD, LPWSTR,
 * LPDWORD, PFILETIME).  CE 1.0+; Winreg.h; Coredll.lib.  Enumerates
 * subkeys by index from 0 until ERROR_NO_MORE_ITEMS; ERROR_MORE_DATA
 * if lpName is too small. */
LONG RegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName,
                   LPDWORD lpcName, LPDWORD lpReserved, LPWSTR lpClass,
                   LPDWORD lpcbClass, PFILETIME lpftLastWriteTime);
#define RegEnumKeyEx RegEnumKeyExW

/* ms891454 "RegEnumValue (Windows CE 5.0)":
 * LONG RegEnumValue(HKEY, DWORD, LPWSTR, LPDWORD, LPDWORD, LPDWORD,
 * LPBYTE, LPDWORD).  CE 1.0+; Winreg.h; Coredll.lib.  Enumerates the
 * values of a key by index from 0 until ERROR_NO_MORE_ITEMS. */
LONG RegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName,
                   LPDWORD lpcchValueName, LPDWORD lpReserved,
                   LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
#define RegEnumValue RegEnumValueW

/* ms891461 "RegQueryInfoKey (Windows CE 5.0)":
 * LONG RegQueryInfoKey(HKEY, LPWSTR, LPDWORD, LPDWORD, LPDWORD,
 * LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, PFILETIME).
 * CE 1.0+; Winreg.h; Coredll.lib.  Class name, subkey/value counts
 * and longest-name lengths of an open key. */
LONG RegQueryInfoKeyW(HKEY hKey, LPWSTR lpClass, LPDWORD lpcbClass,
                      LPDWORD lpReserved, LPDWORD lpcSubKeys,
                      LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen,
                      LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen,
                      LPDWORD lpcbMaxValueLen,
                      LPDWORD lpcbSecurityDescriptor,
                      PFILETIME lpftLastWriteTime);
#define RegQueryInfoKey RegQueryInfoKeyW

/* ms891462 "RegQueryValueEx (Windows CE 5.0)":
 * LONG RegQueryValueEx(HKEY, LPCWSTR, LPDWORD, LPDWORD, LPBYTE,
 * LPDWORD).  CE 1.0+; Winreg.h; Coredll.lib.  Retrieves type/data of
 * a named value (NULL/empty name = the key's unnamed value).  A
 * NULL lpData with a size pointer returns the required size;
 * ERROR_MORE_DATA when the buffer is too small. */
LONG RegQueryValueExW(HKEY hKey, LPCWSTR lpValueName,
                      LPDWORD lpReserved, LPDWORD lpType,
                      LPBYTE lpData, LPDWORD lpcbData);
#define RegQueryValueEx RegQueryValueExW

/* ms891469 "RegSetValueEx (Windows CE 5.0)":
 * LONG RegSetValueEx(HKEY, LPCWSTR, DWORD, DWORD, const BYTE*, DWORD).
 * CE 1.0+; Winreg.h; Coredll.lib.  Stores data under a value name
 * (creates it when absent); cbData must include the terminator for
 * REG_SZ/REG_EXPAND_SZ/REG_MULTI_SZ; value names max 255 chars; the
 * page caps value data at 4 KB on CE. */
LONG RegSetValueExW(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved,
                    DWORD dwType, const BYTE *lpData, DWORD cbData);
#define RegSetValueEx RegSetValueExW

/* ms891455 "RegFlushKey (Windows CE 5.0)":
 * LONG RegFlushKey(HKEY).  CE 2.10+; Winreg.h; Coredll.lib.  Writes
 * the open key's attributes into the registry.  CE does no lazy
 * flush by default (OEM may add one), so important changes should be
 * flushed in groups, not per change. */
LONG RegFlushKeyW(HKEY hKey);
#define RegFlushKey RegFlushKeyW

/* Registry change notification (CE 5.0 and later; Coredll.lib). */

/* aa517116 "CeFindFirstRegChange (Windows CE 5.0)":
 * HANDLE CeFindFirstRegChange(HKEY, BOOL, DWORD).  Creates a change
 * notification handle; waiting on it succeeds when a matching change
 * occurs.  dwNotifyFilter = REG_NOTIFY_CHANGE_NAME and/or
 * REG_NOTIFY_CHANGE_LAST_SET.  INVALID_HANDLE_VALUE on failure. */
HANDLE CeFindFirstRegChange(HKEY hKey, BOOL bWatchSubtree,
                            DWORD dwNotifyFilter);

/* aa517123 "CeFindNextRegChange (Windows CE 5.0)":
 * BOOL CeFindNextRegChange(HANDLE).  Re-arms the notification handle
 * for the next matching change. */
BOOL CeFindNextRegChange(HANDLE hChangeHandle);

/* aa517103 "CeFindCloseRegChange (Windows CE 5.0)":
 * BOOL CeFindCloseRegChange(HANDLE).  Stops change monitoring; the
 * handle must not be used afterwards. */
BOOL CeFindCloseRegChange(HANDLE hChangeHandle);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINREG_H */
