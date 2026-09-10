/*
 * Ntlmssp.h -- NTLM Security Support Provider user/group management
 * (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Ntlmssp.h." row set of
 * the Security book harvest (M95): 10 management functions, every
 * page printing "Link Library: Ntlmssp.lib" (def/ntlmspp-doc.def).
 *
 * Transcription notes:
 *   - The pages mix WCHAR* and LPTSTR parameter spellings
 *     (NTLMDeleteUser / NTLMEnumUser / NTLMSetUserInfo print
 *     LPTSTR glued onto the parameter name); both spellings are
 *     kept as printed.  On CE (TCHAR = WCHAR) they are the same
 *     type.
 *   - No structures or constants are published on these pages.
 */

#ifndef AKARI_NTLMSSP_H
#define AKARI_NTLMSSP_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ms926159 "NTLMAddGroup". */
AKARI_CE_IMPORT BOOL NTLMAddGroup(WCHAR *groupName)
    AKARI_CE_NAME(NTLMAddGroup);

/* ms926164 "NTLMAddUserToGroup". */
AKARI_CE_IMPORT BOOL NTLMAddUserToGroup(WCHAR *groupName,
    WCHAR *userName) AKARI_CE_NAME(NTLMAddUserToGroup);

/* ms926171 "NTLMDeleteUser" (LPTSTR spelling as printed). */
AKARI_CE_IMPORT BOOL NTLMDeleteUser(LPTSTR pszUser)
    AKARI_CE_NAME(NTLMDeleteUser);

/* ms926178 "NTLMEnumGroups". */
AKARI_CE_IMPORT BOOL NTLMEnumGroups(DWORD index, WCHAR *groupName,
    DWORD *dwSizeInChars) AKARI_CE_NAME(NTLMEnumGroups);

/* ms926183 "NTLMEnumUser" (glued print split). */
AKARI_CE_IMPORT BOOL NTLMEnumUser(DWORD index, LPTSTR pszUser,
    LPDWORD pcchUser) AKARI_CE_NAME(NTLMEnumUser);

/* ms926187 "NTLMGetGroupList". */
AKARI_CE_IMPORT BOOL NTLMGetGroupList(WCHAR *userName, WCHAR *groupList,
    DWORD *pdwccLen) AKARI_CE_NAME(NTLMGetGroupList);

/* ms926195 "NTLMGetUserList". */
AKARI_CE_IMPORT BOOL NTLMGetUserList(WCHAR *groupName, WCHAR *userList,
    DWORD *pdwccLen) AKARI_CE_NAME(NTLMGetUserList);

/* ms926201 "NTLMRemoveGroup". */
AKARI_CE_IMPORT BOOL NTLMRemoveGroup(WCHAR *groupName)
    AKARI_CE_NAME(NTLMRemoveGroup);

/* ms926207 "NTLMRemoveUserFromGroup". */
AKARI_CE_IMPORT BOOL NTLMRemoveUserFromGroup(WCHAR *groupName,
    WCHAR *userName) AKARI_CE_NAME(NTLMRemoveUserFromGroup);

/* ms926215 "NTLMSetUserInfo" (glued print split). */
AKARI_CE_IMPORT BOOL NTLMSetUserInfo(LPTSTR pszUser, LPTSTR pszPassword)
    AKARI_CE_NAME(NTLMSetUserInfo);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_NTLMSSP_H */
