/*
 * dvdcss.h -- DVD CSS decoder interface for Windows CE (Dvdcss.idl layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "DVD-Video Renderer" CSS interface (the
 * Dvdcss.idl leaves of tools/manifests/dvd.manifest, fetched M57 for
 * M58).  OS Versions: "Windows CE .NET 4.0 and later".
 *
 * IDVDDecoderCSS is an IDL interface (vtable methods, IUnknown-derived)
 * with no Link Library row and no published vtable order -- the M44/M53/
 * M54/M57 def-less opaque record model: the interface is an opaque type
 * and every documented method signature is recorded in the comment
 * block.  Nothing here enters a def.
 *
 * Held types (names documented, layouts not published -- see
 * docs/inventory.md M58): CSS_CHALLENGE, CSS_KEY and CSS_SDKS are named
 * as the method parameter types (ms900182/ms900183/ms900190) but no page
 * of any CE generation prints their layouts (SendScrambledDiskKeyData
 * documents only the 2048-byte size of the disk key data).  The
 * E_DVD_FAKE_ENCRYPTION return value (ms900190) is name-only.
 */

#ifndef AKARI_DVDCSS_H
#define AKARI_DVDCSS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ms900185 "IDVDDecoderCSS" (Dvdcss.idl; IUnknown-derived; obtained
 * through IUnknown::QueryInterface with the IID_IDVDDECODERCSS
 * identifier, ms892115).  Documented methods, each on its own page:
 *   ms900192  HRESULT SetSectorLength(UINT dwLength);
 *   ms900186  HRESULT NewDisk();
 *   ms900184  HRESULT InitiateAuthentication();
 *   ms900182  HRESULT GetChallenge(CSS_CHALLENGE* pChallenge);
 *   ms900189  HRESULT SendDriveResponseKey(CSS_KEY* pKey);
 *   ms900188  HRESULT SendDriveChallenge(CSS_CHALLENGE* pChallenge);
 *   ms900183  HRESULT GetResponseKey(CSS_KEY* pKey);
 *   ms900190  HRESULT SendScrambledDiskKeyData(CSS_SDKS* pSDKS);
 *             (returns E_DVD_FAKE_ENCRYPTION for fake-encrypted discs;
 *              call BypassDescrambler then -- name-only value)
 *   ms900191  HRESULT SendTitleKey(CSS_KEY* pKey);
 *   ms900187  HRESULT ResetAuthentication();
 *   ms900181  HRESULT EnableDescrambler();
 *   ms900180  HRESULT BypassDescrambler();
 */
typedef struct IDVDDecoderCSS IDVDDecoderCSS;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDCSS_H */
