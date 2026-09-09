/* Smbconfig.h -- SMB server share configuration (Windows CE 5.0).
 * Link Library rows print Smbconfig.lib (def/smbconfig-doc.def).
 * Prints: Add_Share / Change_ACL / Del_Share /
 * List_Connected_Users / QueryAmountTransfered.  See
 * docs/inventory.md M75e. */

#ifndef AKARI_SMBCONFIG_H
#define AKARI_SMBCONFIG_H

#include "Windef.h"    /* DWORD, UINT */
#include "Objbase.h"   /* HRESULT */
#include "Winnt.h"     /* LARGE_INTEGER */

AKARI_CE_IMPORT HRESULT Add_Share(const WCHAR *pName, DWORD dwType,
                    const WCHAR *pPath)
                    AKARI_CE_NAME(Add_Share);

AKARI_CE_IMPORT HRESULT Del_Share(const WCHAR *pName)
                    AKARI_CE_NAME(Del_Share);

AKARI_CE_IMPORT HRESULT Change_ACL(const WCHAR *pShareName,
                    const WCHAR *pACL, const WCHAR *pPath)
                    AKARI_CE_NAME(Change_ACL);

AKARI_CE_IMPORT HRESULT List_Connected_Users(WCHAR *pBuffer,
                    UINT *puiLen) AKARI_CE_NAME(List_Connected_Users);

AKARI_CE_IMPORT HRESULT QueryAmountTransfered(
                    LARGE_INTEGER *pRead, LARGE_INTEGER *pWrite)
                    AKARI_CE_NAME(QueryAmountTransfered);

#endif /* AKARI_SMBCONFIG_H */
