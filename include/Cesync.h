/*
 * Cesync.h -- documented-case alias for the CE Sync COM surface.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE Sync (COM) pages print Header: Cesync.h; their one harvested
 * symbol -- STOREINFO (COM) ms896271, tag tagStoreInfo, with the
 * SCF_SINGLE_THREAD / SCF_SIMULATE_RTS uFlags rows -- is carried by
 * Objbase.h (M73b, which owns the STOREINFO / PSTOREINFO typedef per
 * the Storemgr.h collision note).  Objidl.h alias precedent.
 */
#include "Objbase.h"/* ------------------------------------------------------------------
 * Book surface: activesync (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa513865 DEVINFO (page print, compiled) */
typedef struct tagDevInfo {
    DWORD pid;
    char szName[MAX_PATH];
    char szType[80];
    char szPath[MAX_PATH];
} DEVINFO, *PDEVINFO;
/* aa513863 CONFINFO -- HELD (page print; member types unpublished):
 *   typedef struct tagConfInfo { ... } CONFINFO, *PCONFINFO; */
/* ms879798 FINDOBJINFO -- HELD (page print; member types unpublished):
 *   typedef struct tagFindObjInfo { ... } FINDOBJINFO, *PFINDOBJINFO; */
/* aa514417 OBJNOTIFY -- HELD (page print; member types unpublished):
 *   typedef struct tagObjNotify { ... } OBJNOTIFY, *POBJNOTIFY; */
/* aa514419 OBJTYPEINFO -- HELD (page print; member types unpublished):
 *   typedef struct tagObjTypeInfo { ... } OBJTPYEINFO, *POBJTYPEINFO; */
/* aa514421 OBJUIDATA -- HELD (page print; member types unpublished):
 *   typedef struct tagObjUIData { ... } OBJUIDATA, *POBJUIDATA; */
/* aa514454 REPLSETUP -- HELD (page print; member types unpublished):
 *   typedef struct tagReplSetup { ... } REPLSETUP, * PREPLSETUP; */
/* aa514456 SDREQUEST -- HELD (page print; member types unpublished):
 *   typedef struct SDREQUEST { ... } SDREQUEST, *PSDREQUEST; */
/* aa513895 IEnumReplItem::Clone (Header: Cesync.h.) */
/* aa513896 IEnumReplItem::GetFolderHandle (Header: Cesync.h.) */
/* aa513900 IEnumReplItem::Next (Header: Cesync.h.) */
/* aa513901 IEnumReplItem::Reset (Header: Cesync.h.) */
/* aa513903 IEnumReplItem::Skip (Header: Cesync.h.) */
/* aa514343 IReplNotify::GetWindow (Header: Cesync.h.) */
/* aa514347 IReplNotify::OnItemCompleted (Header: Cesync.h.) */
/* aa514350 IReplNotify::OnItemNotify (Header: Cesync.h.) */
/* aa514352 IReplNotify::QueryDevice (Header: Cesync.h.) */
/* aa514354 IReplNotify::SetStatusText (Header: Cesync.h.) */
/* aa514356 IReplObjHandler::DeleteObj (Header: Cesync.h.) */
/* aa514357 IReplObjHandler::GetPacket (Header: Cesync.h.) */
/* aa514361 IReplObjHandler::Reset (Header: Cesync.h.) */
/* aa514363 IReplObjHandler::SetPacket (Header: Cesync.h.) */
/* aa514365 IReplObjHandler::Setup (Header: Cesync.h.) */
/* aa514367 IReplStore::ActivateDialog (Header: Cesync.h.) */
/* aa514370 IReplStore::BytesToObject (Header: Cesync.h.) */
/* aa514372 IReplStore::CompareItem (Header: Cesync.h.) */
/* aa514374 IReplStore::CompareStoreIDs (Header: Cesync.h.) */
/* aa514376 IReplStore::CopyObject (Header: Cesync.h.) */
/* aa514378 IReplStore::FindFirstItem (Header: Cesync.h.) */
/* aa514380 IReplStore::FindItemClose (Header: Cesync.h.) */
/* aa514381 IReplStore::FindNextItem (Header: Cesync.h.) */
/* aa514384 IReplStore::FreeObject (Header: Cesync.h.) */
/* aa514386 IReplStore::GetConflictInfo (Header: Cesync.h.) */
/* aa514388 IReplStore::GetFolderInfo (Header: Cesync.h.) */
/* aa514389 IReplStore::GetObjTypeUIData (Header: Cesync.h.) */
/* aa514391 IReplStore::GetStoreInfo (Header: Cesync.h.) */
/* aa514393 IReplStore::Initialize (Header: Cesync.h.) */
/* aa514395 IReplStore::IsFolderChanged (Header: Cesync.h.) */
/* aa514396 IReplStore::IsItemChanged (Header: Cesync.h.) */
/* aa514398 IReplStore::IsItemReplicated (Header: Cesync.h.) */
/* aa514400 IReplStore::IsValidObject (Header: Cesync.h.) */
/* aa514403 IReplStore::ObjectToBytes (Header: Cesync.h.) */
/* aa514406 IReplStore::RemoveDuplicates (Header: Cesync.h.) */
/* aa514407 IReplStore::ReportStatus (Header: Cesync.h.) */
/* aa514409 IReplStore::UpdateItem (Header: Cesync.h.) */

