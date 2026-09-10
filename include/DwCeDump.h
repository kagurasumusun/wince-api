/* DwCeDump.h -- Windows CE Error Reporting dump-file structures.
 *
 * Source pages: the Error Report Generator reference rows printing
 * "Header: DwCeDump.h" (16 structure pages + the _MINIDUMP_STREAM_TYPE
 * enumeration, tools/manifests/errorrep-book.manifest; most rows print
 * no link library, _MINIDUMP_MEMORY_DESCRIPTOR prints a DwDmpTxt.lib
 * row -- a host-tool library, not a device import).
 *
 * The structures are recorded verbatim and closed opaquely: every
 * print embeds the RVA / ULONG32 member types, which no CE page
 * prints as typedefs (the Dump File Format page ms939593 describes
 * an RVA as "an offset from the beginning of a file" only).  The
 * enumeration is fully printed and is compiled below (the print's
 * C++ line comments are reproduced as C block comments; noted).
 * See docs/inventory.md M82.
 */

#ifndef AKARI_DWCEDUMP_H
#define AKARI_DWCEDUMP_H

#include "Windef.h"    /* USHORT, ULONG, WCHAR */
#include "Winnt.h"     /* EXCEPTION_MAXIMUM_PARAMETERS (ms885... print */

/* --- Held structures (RVA / ULONG32 members unpublished). ------ */
/* ms939635 "_CEDUMP_BUCKET_PARAMETERS": `typedef struct _CEDUMP_BUCKET_PARAMETERS {USHORT SizeOfHeader;USHORT__unusedAlignment;RVAEventType;ULONG32fDebug;RVAAppName;ULONG32AppStamp;ULONG32AppVerMS;ULONG32AppVerLS;RVAModName;ULONG32ModStamp;ULONG32ModVerMS;ULONG32ModVerLS;ULONG32Offset;RVAOwnerName;ULONG32OwnerStamp;ULONG32OwnerVerMS;ULONG32OwnerVerLS;} CEDUMP_BUCKET_PARAMETERS, *PCEDUMP_BUCKET_PARAMETERS;` */
/* ms939636 "_CEDUMP_ELEMENT_LIST": `typedef struct _CEDUMP_ELEMENT_LIST {USHORTSizeOfHeader;USHORT SizeOfFieldInfo;ULONG32 NumberOfFieldInfo;ULONG32 NumberOfElements;RVA Elements;} CEDUMP_ELEMENT_LIST, *PCEDUMP_ELEMENT_LIST;` */
/* ms939637 "_CEDUMP_EXCEPTION": `typedef struct _CEDUMP_EXCEPTION {ULONG32 ExceptionCode;ULONG32ExceptionFlags;ULONG32 ExceptionRecord;ULONG32ExceptionAddress;ULONG32NumberParameters;ULONG32ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS ];} CEDUMP_EXCEPTION, *PCEDUMP_EXCEPTION;` */
/* ms939638 "_CEDUMP_EXCEPTION_STREAM": `typedef struct _CEDUMP_EXCEPTION_STREAM { USHORT SizeOfHeader; USHORTSizeOfException; USHORTSizeOfThreadContext; USHORTFlags; ULONG32CurrentProcessId; ULONG32ThreadId;ULONG32OwnerProcessId;ULONG32 CaptureAPICurrentProcessId;ULONG32 CaptureAPIThreadId;ULONG32 CaptureAPIOwnerProcessId;} CEDUMP_EXCEPTION_STREAM, *PCEDUMP_EXCEPTION_STREAM;` */
/* ms939639 "_CEDUMP_FIELD_INFO": `typedef struct _CEDUMP_FIELD_INFO {ULONG32FieldId;ULONG32 FieldSize;RVA FieldLabel;RVA FieldFormat;} CEDUMP_FIELD_INFO, *PCEDUMP_FIELD_INFO;` */
/* ms939640 "_CEDUMP_MEMORY_LIST": `typedef struct _CEDUMP_MEMORY_LIST {USHORTSizeOfHeader;USHORTSizeOfEntry;ULONG32NumberOfEntries;} CEDUMP_MEMORY_LIST, *PCEDUMP_MEMORY_LIST;` */
/* ms939641 "_CEDUMP_SYSTEM_INFO": `typedef struct _CEDUMP_SYSTEM_INFO {USHORT SizeOfHeader;USHORT ProcessorArchitecture;ULONG32 NumberOfProcessors;ULONG32 ProcessorType;USHORT ProcessorLevel;USHORT ProcessorRevision;ULONG32 ProcessorFamily;ULONG32 MajorVersion;ULONG32 MinorVersion;ULONG32 BuildNumber;ULONG32 PlatformId;ULONG32 LCID;RVA OEMStringRva;ULONG32SupportFlags;USHORT Machine;USHORT __unusedAlignment;RVA PlatformTypeRva;DWORD Platforms;RVA PlatformVersion; DWORD InstructionSet;DWORD __unusedAlignment2} CEDUMP_SYSTEM_INFO, *PCEDUMP_SYSTEM_INFO;` */
/* ms939642 "_CEDUMP_THREAD_CALL_STACK": `typedef struct _CEDUMP_THREAD_CALL_STACK {ULONG32 ProcessId;ULONG32 ThreadId;USHORT SizeOfFrame;USHORT NumberOfFrames;RVAStackFramess;} CEDUMP_THREAD_CALL_STACK, *PCEDUMP_THREAD_CALL_STACK;` */
/* ms939643 "_CEDUMP_THREAD_CALL_STACK_FRAME": `typedef struct _CEDUMP_THREAD_CALL_STACK_FRAME {ULONG32ReturnAddr;ULONG32 FramePtr;ULONG32 ProcessId;ULONG32 __unusedAlignment;ULONG32 Params[4];} CEDUMP_THREAD_CALL_STACK_FRAME, *PCEDUMP_THREAD_CALL_STACK_FRAME;` */
/* ms939644 "_CEDUMP_THREAD_CALL_STACK_LIST": `typedef struct _CEDUMP_THREAD_CALL_STACK_LIST {USHORTSizeOfHeader;USHORT SizeOfEntry;ULONG32 NumberOfEntries;} CEDUMP_THREAD_CALL_STACK_LIST, *PCEDUMP_THREAD_CALL_STACK_LIST;` */
/* ms939645 "_MINIDUMP_DIRECTORY": `typedef struct _MINIDUMP_DIRECTORY {ULONG32 StreamType;MINIDUMP_LOCATION_DESCRIPTOR Location;} MINIDUMP_DIRECTORY, *PMINIDUMP_DIRECTORY;` */
/* ms939646 "_MINIDUMP_HEADER": `typedef struct _MINIDUMP_HEADER {ULONG32 Signature;ULONG32 Version;ULONG32 NumberOfStreams;RVA StreamDirectoryRva;ULONG32CheckSum;union{ULONG32 Reserved;ULONG32 TimeDateStamp;};ULONG64 Flags;} MINIDUMP_HEADER, *PMINIDUMP_HEADER;` */
/* ms939647 "_MINIDUMP_LOCATION_DESCRIPTOR": `typedef struct _MINIDUMP_LOCATION_DESCRIPTOR { ULONG32 DataSize; RVARva;} MINIDUMP_LOCATION_DESCRIPTOR;` */
/* ms939648 "_MINIDUMP_MEMORY_DESCRIPTOR": `typedef struct _MINIDUMP_MEMORY_DESCRIPTOR {ULONG64StartOfMemoryRange;MINIDUMP_LOCATION_DESCRIPTORMemory;} MINIDUMP_MEMORY_DESCRIPTOR, *PMINIDUMP_MEMORY_DESCRIPTOR;` */
/* ms939650 "_MINIDUMP_STRING": `typedef struct _MINIDUMP_STRING {ULONG32Length;WCHAR Buffer [0];} MINIDUMP_STRING, *PMINIDUMP_STRING;` */
typedef struct _CEDUMP_BUCKET_PARAMETERS CEDUMP_BUCKET_PARAMETERS, *PCEDUMP_BUCKET_PARAMETERS;
typedef struct _CEDUMP_ELEMENT_LIST CEDUMP_ELEMENT_LIST, *PCEDUMP_ELEMENT_LIST;
typedef struct _CEDUMP_EXCEPTION CEDUMP_EXCEPTION, *PCEDUMP_EXCEPTION;
typedef struct _CEDUMP_EXCEPTION_STREAM CEDUMP_EXCEPTION_STREAM, *PCEDUMP_EXCEPTION_STREAM;
typedef struct _CEDUMP_FIELD_INFO CEDUMP_FIELD_INFO, *PCEDUMP_FIELD_INFO;
typedef struct _CEDUMP_MEMORY_LIST CEDUMP_MEMORY_LIST, *PCEDUMP_MEMORY_LIST;
typedef struct _CEDUMP_SYSTEM_INFO CEDUMP_SYSTEM_INFO, *PCEDUMP_SYSTEM_INFO;
typedef struct _CEDUMP_THREAD_CALL_STACK CEDUMP_THREAD_CALL_STACK, *PCEDUMP_THREAD_CALL_STACK;
typedef struct _CEDUMP_THREAD_CALL_STACK_FRAME CEDUMP_THREAD_CALL_STACK_FRAME, *PCEDUMP_THREAD_CALL_STACK_FRAME;
typedef struct _CEDUMP_THREAD_CALL_STACK_LIST CEDUMP_THREAD_CALL_STACK_LIST, *PCEDUMP_THREAD_CALL_STACK_LIST;
typedef struct _MINIDUMP_DIRECTORY MINIDUMP_DIRECTORY, *PMINIDUMP_DIRECTORY;
typedef struct _MINIDUMP_HEADER MINIDUMP_HEADER, *PMINIDUMP_HEADER;
typedef struct _MINIDUMP_LOCATION_DESCRIPTOR
    MINIDUMP_LOCATION_DESCRIPTOR;
typedef struct _MINIDUMP_MEMORY_DESCRIPTOR MINIDUMP_MEMORY_DESCRIPTOR, *PMINIDUMP_MEMORY_DESCRIPTOR;
typedef struct _MINIDUMP_STRING MINIDUMP_STRING, *PMINIDUMP_STRING;

/* --- Enumeration (printed). -------------------------------------- */
/* ms939649 "_MINIDUMP_STREAM_TYPE": print (C++ // comments in the
 * print reproduced as a C block comment here; values as printed):
 * `typedef enum _MINIDUMP_STREAM_TYPE { UnusedStream = 0,
 * // 1 to 0x7FFF - Reserved for Desktop Windows
 * // 0x8000 to 0xFFFE - Windows CE stream types
 * ceStreamNull = 0x8000, ceStreamSystemInfo = 0x8001, ...
 * LastReservedStream = 0xffff} MINIDUMP_STREAM_TYPE;` */
typedef enum _MINIDUMP_STREAM_TYPE {
    UnusedStream = 0,
    /* 1 to 0x7FFF - Reserved for Desktop Windows */
    /* 0x8000 to 0xFFFE - Windows CE stream types */
    ceStreamNull = 0x8000,
    ceStreamSystemInfo = 0x8001,
    ceStreamException = 0x8002,
    ceStreamModuleList = 0x8003,
    ceStreamProcessList = 0x8004,
    ceStreamThreadList = 0x8005,
    ceStreamThreadContextList = 0x8006,
    ceStreamThreadCallStackList = 0x8007,
    ceStreamMemoryVirtualList = 0x8008,
    ceStreamMemoryPhysicalList = 0x8009,
    ceStreamBucketParameters = 0x800A,
    LastReservedStream = 0xffff
} MINIDUMP_STREAM_TYPE;

#endif /* AKARI_DWCEDUMP_H */
