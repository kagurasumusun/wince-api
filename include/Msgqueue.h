/*
 * Msgqueue.h -- point-to-point message queue API for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs).  The CE pages' Header row is Msgqueue.h and the
 * Link Library row is Coredll.lib for every function in this book
 * (Message Queue Point-to-Point Reference); the same APIs continue to
 * be documented under Windows Embedded CE 6.0 / later archives with
 * their own page IDs (e.g. CloseMsgQueue ee488787(v=winembedded.60)).
 */

#ifndef AKARI_MSGQUEUE_H
#define AKARI_MSGQUEUE_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* --- Message-queue behavior flags and message-type flag. ----------
 *
 * The CE pages name MSGQUEUE_NOPRECOMMIT ("allocate message buffers on
 * demand and free them after they are read"), MSGQUEUE_ALLOW_BROKEN
 * ("complete a read or write even if there is no corresponding writer
 * or reader present") and MSGQUEUE_MSGALERT ("this message is an alert
 * message").  No CE page publishes their numeric values, so the values
 * are recorded as *unknown* and the names are deliberately not defined
 * (no values are invented).
 */

/* ms886759 "MSGQUEUEOPTIONS (Windows CE 5.0)": creation options for a
 * user-defined message queue.  CE .NET 4.0+; Msgqueue.h.  The page's
 * syntax line prints the typedef without an internal tag, so the tag
 * is treated as unpublished and none is invented here. */
typedef struct {
    DWORD dwSize;         /* structure size, in bytes */
    DWORD dwFlags;        /* MSGQUEUE_NOPRECOMMIT / MSGQUEUE_ALLOW_BROKEN */
    DWORD dwMaxMessages;  /* max queued messages; 0 = unlimited */
    DWORD cbMaxMessage;   /* max bytes per message; must be > 0 */
    BOOL  bReadAccess;    /* TRUE = read access, FALSE = write access */
} MSGQUEUEOPTIONS, *PMSGQUEUEOPTIONS, *LPMSGQUEUEOPTIONS;

/* ms886758 "MSGQUEUEINFO (Windows CE 5.0)": run-time information about
 * a message queue, filled by GetMsgQueueInfo.  CE .NET 4.0+;
 * Msgqueue.h.  dwMaxMessages == 0 implies MSGQUEUE_NOPRECOMMIT
 * behavior (page note). */
typedef struct {
    DWORD dwSize;             /* buffer size passed by the caller */
    DWORD dwFlags;            /* creation flags (MSGQUEUEOPTIONS.dwFlags) */
    DWORD dwMaxMessages;      /* max messages allowed; 0 = unrestricted */
    DWORD cbMaxMessage;       /* message length, in bytes */
    DWORD dwCurrentMessages;  /* messages currently in the queue */
    DWORD dwMaxQueueMessages; /* all-time high-water mark */
    WORD  wNumReaders;        /* readers currently attached */
    WORD  wNumWriters;        /* writers currently attached */
} MSGQUEUEINFO, *PMSGQUEUEINFO, *LPMSGQUEUEINFO;

/* ms885168 "CloseMsgQueue (Windows CE 5.0)":
 * BOOL CloseMsgQueue(HANDLE hMsgQ).  CE .NET 4.0+; Msgqueue.h;
 * Coredll.lib.  Closes a message-queue handle returned by
 * CreateMsgQueue or OpenMsgQueue. */
AKARI_CE_IMPORT BOOL CloseMsgQueue(HANDLE hMsgQ) AKARI_CE_NAME(CloseMsgQueue);

/* ms885180 "CreateMsgQueue (Windows CE 5.0)":
 * HANDLE CreateMsgQueue(LPCWSTR lpszName, LPMSGQUEUEOPTIONS lpOptions).
 * CE .NET 4.0+; Msgqueue.h; Coredll.lib.  Creates (or opens) a
 * user-defined message queue; NULL name creates an unnamed queue.  A
 * queue is opened for read *or* write access only (MSGQUEUEOPTIONS.
 * bReadAccess); on an existing queue only dwSize and bReadAccess are
 * used.  If the queue already existed, GetLastError is
 * ERROR_ALREADY_EXISTS; on failure the return value is NULL.  Names
 * are limited to MAX_PATH characters; queue handles are signalable to
 * WaitForSingleObject/WaitForMultipleObjects (writeable handles signal
 * when not full, readable handles when not empty). */
AKARI_CE_IMPORT HANDLE CreateMsgQueue(LPCWSTR lpszName, LPMSGQUEUEOPTIONS lpOptions) AKARI_CE_NAME(CreateMsgQueue);

/* ms885632 "GetMsgQueueInfo (Windows CE 5.0)":
 * BOOL GetMsgQueueInfo(HANDLE hMsgQ, LPMSGQUEUEINFO lpInfo).
 * CE .NET 4.0+; Msgqueue.h; Coredll.lib.  Fills an MSGQUEUEINFO with
 * information about an open message queue. */
AKARI_CE_IMPORT BOOL GetMsgQueueInfo(HANDLE hMsgQ, LPMSGQUEUEINFO lpInfo) AKARI_CE_NAME(GetMsgQueueInfo);

/* ms886765 "OpenMsgQueue (Windows CE 5.0)":
 * HANDLE OpenMsgQueue(HANDLE hSrcProc, HANDLE hMsgQ,
 *                     LPMSGQUEUEOPTIONS lpOptions).
 * CE .NET 4.0+; Msgqueue.h; Coredll.lib.  Opens a new handle to an
 * existing queue, using a source-process handle and a queue handle
 * from CreateMsgQueue; only MSGQUEUEOPTIONS.dwSize and bReadAccess
 * are checked.  Returns the new handle or NULL. */
AKARI_CE_IMPORT HANDLE OpenMsgQueue(HANDLE hSrcProc, HANDLE hMsgQ,
                    LPMSGQUEUEOPTIONS lpOptions) AKARI_CE_NAME(OpenMsgQueue);

/* ms886793 "ReadMsgQueue (Windows CE 5.0)":
 * BOOL ReadMsgQueue(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbBufferSize,
 *                   LPDWORD lpNumberOfBytesRead, DWORD dwTimeout,
 *                   LPDWORD pdwFlags).
 * CE .NET 4.0+; Msgqueue.h; Coredll.lib.  Reads a single message.
 * lpBuffer/cbBufferSize must be non-NULL/nonzero; dwTimeout 0 does
 * not block, INFINITE blocks until data or a queue-status change.
 * pdwFlags receives MSGQUEUE_MSGALERT for alert messages.  Errors:
 * ERROR_INSUFFICIENT_BUFFER (short copy succeeds), ERROR_PIPE_NOT_
 * CONNECTED (no writers and MSGQUEUE_ALLOW_BROKEN not set),
 * ERROR_TIMEOUT (no data with zero timeout). */
AKARI_CE_IMPORT BOOL ReadMsgQueue(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbBufferSize,
                  LPDWORD lpNumberOfBytesRead, DWORD dwTimeout,
                  LPDWORD pdwFlags) AKARI_CE_NAME(ReadMsgQueue);

/* aa450991 "WriteMsgQueue (Windows CE 5.0)":
 * BOOL WriteMsgQueue(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbDataSize,
 *                    DWORD dwTimeout, DWORD dwFlags).
 * CE .NET 4.0+; Msgqueue.h; Coredll.lib.  Writes a single message
 * (lpBuffer/cbDataSize must be non-NULL/nonzero).  dwFlags may be
 * MSGQUEUE_MSGALERT.  Errors: ERROR_INSUFFICIENT_BUFFER (message too
 * large), ERROR_PIPE_NOT_CONNECTED (no readers and MSGQUEUE_ALLOW_
 * BROKEN not set), ERROR_TIMEOUT, ERROR_OUTOFMEMORY (MSGQUEUE_
 * NOPRECOMMIT without memory). */
AKARI_CE_IMPORT BOOL WriteMsgQueue(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbDataSize,
                   DWORD dwTimeout, DWORD dwFlags) AKARI_CE_NAME(WriteMsgQueue);

/* ------------------------------------------------------------------
 * Book surface: core-msgqueue-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450754 Message Queue Point-to-Point Functions */
/* aa450756 Message Queue Point-to-Point Structures */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MSGQUEUE_H */
