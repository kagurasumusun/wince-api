/*
 * winerror.h -- error-code constants for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  The names and numeric values below are the
 * system error codes published in Microsoft's official "System Errors
 * - Numerical Order (Windows CE 5.0)" reference (aa450919; rows 0
 * through 1078).  The numbers are the Win32 error-code ABI values
 * (identical across desktop Windows and Windows CE); rows that the CE
 * table itself omits are intentionally not defined here.  Constants
 * first cited by individual CE function pages carry extra page-ID
 * comments below.
 */

#ifndef AKARI_WINERROR_H
#define AKARI_WINERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Success / informational values. */
#define ERROR_SUCCESS                0L
#define NO_ERROR                     0L   /* same value as ERROR_SUCCESS; cited by the CE TlsGetValue page (aa450949: "GetLastError returns NO_ERROR") */

/* Rows 1-39: file/device/disk errors. */
#define ERROR_INVALID_FUNCTION       1L
#define ERROR_FILE_NOT_FOUND         2L
#define ERROR_PATH_NOT_FOUND         3L
#define ERROR_TOO_MANY_OPEN_FILES    4L
#define ERROR_ACCESS_DENIED          5L
#define ERROR_INVALID_HANDLE         6L
#define ERROR_ARENA_TRASHED          7L
#define ERROR_NOT_ENOUGH_MEMORY      8L
#define ERROR_INVALID_BLOCK          9L
#define ERROR_BAD_ENVIRONMENT       10L
#define ERROR_BAD_FORMAT            11L
#define ERROR_INVALID_ACCESS        12L
#define ERROR_INVALID_DATA          13L
#define ERROR_OUTOFMEMORY           14L
#define ERROR_INVALID_DRIVE         15L
#define ERROR_CURRENT_DIRECTORY     16L
#define ERROR_NOT_SAME_DEVICE       17L
#define ERROR_NO_MORE_FILES         18L   /* cited by the CE FindNextFile page (ms889873: no more matching files) */
#define ERROR_WRITE_PROTECT         19L
#define ERROR_BAD_UNIT              20L
#define ERROR_NOT_READY             21L
#define ERROR_BAD_COMMAND           22L
#define ERROR_CRC                   23L
#define ERROR_BAD_LENGTH            24L
#define ERROR_SEEK                  25L
#define ERROR_NOT_DOS_DISK          26L
#define ERROR_SECTOR_NOT_FOUND      27L
#define ERROR_OUT_OF_PAPER          28L
#define ERROR_WRITE_FAULT           29L
#define ERROR_READ_FAULT            30L
#define ERROR_GEN_FAILURE           31L
#define ERROR_SHARING_VIOLATION     32L
#define ERROR_LOCK_VIOLATION        33L
#define ERROR_WRONG_DISK            34L
#define ERROR_SHARING_BUFFER_EXCEEDED 36L
#define ERROR_HANDLE_EOF            38L
#define ERROR_HANDLE_DISK_FULL      39L

/* Rows 50-72: network errors. */
#define ERROR_NOT_SUPPORTED         50L
#define ERROR_REM_NOT_LIST          51L
#define ERROR_DUP_NAME              52L
#define ERROR_BAD_NETPATH           53L
#define ERROR_NETWORK_BUSY          54L
#define ERROR_DEV_NOT_EXIST         55L
#define ERROR_TOO_MANY_CMDS         56L
#define ERROR_ADAP_HDW_ERR          57L
#define ERROR_BAD_NET_RESP          58L
#define ERROR_UNEXP_NET_ERR         59L
#define ERROR_BAD_REM_ADAP          60L
#define ERROR_PRINTQ_FULL           61L
#define ERROR_NO_SPOOL_SPACE        62L
#define ERROR_PRINT_CANCELLED       63L
#define ERROR_NETNAME_DELETED       64L
#define ERROR_NETWORK_ACCESS_DENIED 65L
#define ERROR_BAD_DEV_TYPE          66L
#define ERROR_BAD_NET_NAME          67L
#define ERROR_TOO_MANY_NAMES        68L
#define ERROR_TOO_MANY_SESS         69L
#define ERROR_SHARING_PAUSED        70L
#define ERROR_REQ_NOT_ACCEP         71L
#define ERROR_REDIR_PAUSED          72L

/* Rows 80-89: file/password errors. */
#define ERROR_FILE_EXISTS           80L
#define ERROR_CANNOT_MAKE           82L
#define ERROR_FAIL_I24              83L
#define ERROR_OUT_OF_STRUCTURES     84L
#define ERROR_ALREADY_ASSIGNED      85L
#define ERROR_INVALID_PASSWORD      86L
#define ERROR_INVALID_PARAMETER     87L   /* cited by the CE CreateThread page (ms885186: NULL start address returns ERROR_INVALID_PARAMETER) */
#define ERROR_NET_WRITE_FAULT       88L
#define ERROR_NO_PROC_SLOTS         89L

/* Rows 100-121: semaphore/system errors. */
#define ERROR_TOO_MANY_SEMAPHORES        100L
#define ERROR_EXCL_SEM_ALREADY_OWNED     101L
#define ERROR_SEM_IS_SET                 102L
#define ERROR_TOO_MANY_SEM_REQUESTS      103L
#define ERROR_INVALID_AT_INTERRUPT_TIME  104L
#define ERROR_SEM_OWNER_DIED             105L
#define ERROR_SEM_USER_LIMIT             106L
#define ERROR_DISK_CHANGE                107L
#define ERROR_DRIVE_LOCKED               108L
#define ERROR_BROKEN_PIPE                109L
#define ERROR_OPEN_FAILED                110L
#define ERROR_BUFFER_OVERFLOW            111L
#define ERROR_DISK_FULL                  112L
#define ERROR_NO_MORE_SEARCH_HANDLES     113L
#define ERROR_INVALID_TARGET_HANDLE      114L
#define ERROR_INVALID_CATEGORY           117L
#define ERROR_INVALID_VERIFY_SWITCH      118L
#define ERROR_BAD_DRIVER_LEVEL           119L
#define ERROR_CALL_NOT_IMPLEMENTED       120L
#define ERROR_SEM_TIMEOUT                121L

/* Rows 122-162: name/buffer/module errors. */
#define ERROR_INSUFFICIENT_BUFFER    122L  /* cited by the CE conversion-function pages (ms915519 / ms961248) */
#define ERROR_INVALID_NAME          123L
#define ERROR_INVALID_LEVEL         124L
#define ERROR_NO_VOLUME_LABEL       125L
#define ERROR_MOD_NOT_FOUND         126L
#define ERROR_PROC_NOT_FOUND        127L
#define ERROR_WAIT_NO_CHILDREN      128L
#define ERROR_CHILD_NOT_COMPLETE    129L
#define ERROR_DIRECT_ACCESS_HANDLE  130L
#define ERROR_NEGATIVE_SEEK         131L
#define ERROR_SEEK_ON_DEVICE        132L
#define ERROR_IS_JOIN_TARGET        133L
#define ERROR_IS_JOINED             134L
#define ERROR_IS_SUBSTED            135L
#define ERROR_NOT_JOINED            136L
#define ERROR_NOT_SUBSTED           137L
#define ERROR_JOIN_TO_JOIN          138L
#define ERROR_SUBST_TO_SUBST        139L
#define ERROR_JOIN_TO_SUBST         140L
#define ERROR_SUBST_TO_JOIN         141L
#define ERROR_BUSY_DRIVE            142L
#define ERROR_SAME_DRIVE            143L
#define ERROR_DIR_NOT_ROOT          144L
#define ERROR_DIR_NOT_EMPTY         145L
#define ERROR_IS_SUBST_PATH         146L
#define ERROR_IS_JOIN_PATH          147L
#define ERROR_PATH_BUSY             148L
#define ERROR_IS_SUBST_TARGET       149L
#define ERROR_SYSTEM_TRACE          150L
#define ERROR_INVALID_EVENT_COUNT   151L
#define ERROR_TOO_MANY_MUXWAITERS   152L
#define ERROR_INVALID_LIST_FORMAT   153L
#define ERROR_LABEL_TOO_LONG        154L
#define ERROR_TOO_MANY_TCBS         155L
#define ERROR_SIGNAL_REFUSED        156L
#define ERROR_DISCARDED             157L
#define ERROR_NOT_LOCKED            158L
#define ERROR_BAD_THREADID_ADDR     159L
#define ERROR_BAD_ARGUMENTS         160L
#define ERROR_BAD_PATHNAME          161L
#define ERROR_SIGNAL_PENDING        162L

/* Rows 164-216: thread/lock/exec format errors. */
#define ERROR_MAX_THRDS_REACHED         164L
#define ERROR_LOCK_FAILED               167L
#define ERROR_BUSY                      170L
#define ERROR_CANCEL_VIOLATION          173L
#define ERROR_ATOMIC_LOCKS_NOT_SUPPORTED 174L
#define ERROR_INVALID_SEGMENT_NUMBER    180L
#define ERROR_INVALID_ORDINAL           182L
#define ERROR_ALREADY_EXISTS            183L  /* cited by the CE WinMain page (ms914104: a uniquely named mutex fails with ERROR_ALREADY_EXISTS when a prior instance exists) */
#define ERROR_INVALID_FLAG_NUMBER       186L
#define ERROR_SEM_NOT_FOUND             187L
#define ERROR_INVALID_STARTING_CODESEG  188L
#define ERROR_INVALID_STACKSEG          189L
#define ERROR_INVALID_MODULETYPE        190L
#define ERROR_INVALID_EXE_SIGNATURE     191L
#define ERROR_EXE_MARKED_INVALID        192L
#define ERROR_BAD_EXE_FORMAT            193L
#define ERROR_ITERATED_DATA_EXCEEDS_64k 194L
#define ERROR_INVALID_MINALLOCSIZE      195L
#define ERROR_DYNLINK_FROM_INVALID_RING 196L
#define ERROR_IOPL_NOT_ENABLED          197L
#define ERROR_INVALID_SEGDPL            198L
#define ERROR_AUTODATASEG_EXCEEDS_64k   199L
#define ERROR_RING2SEG_MUST_BE_MOVABLE  200L
#define ERROR_RELOC_CHAIN_XEEDS_SEGLIM  201L
#define ERROR_INFLOOP_IN_RELOC_CHAIN    202L
#define ERROR_ENVVAR_NOT_FOUND          203L
#define ERROR_NO_SIGNAL_SENT            205L
#define ERROR_FILENAME_EXCED_RANGE      206L
#define ERROR_RING2_STACK_IN_USE        207L
#define ERROR_META_EXPANSION_TOO_LONG   208L
#define ERROR_INVALID_SIGNAL_NUMBER     209L
#define ERROR_THREAD_1_INACTIVE         210L
#define ERROR_LOCKED                    212L
#define ERROR_TOO_MANY_MODULES          214L
#define ERROR_NESTING_NOT_ALLOWED       215L
#define ERROR_EXE_MACHINE_TYPE_MISMATCH 216L

/* Rows 230-259: pipe errors and more-data states. */
#define ERROR_BAD_PIPE             230L
#define ERROR_PIPE_BUSY            231L
#define ERROR_NO_DATA              232L
#define ERROR_PIPE_NOT_CONNECTED   233L
#define ERROR_MORE_DATA            234L
#define ERROR_VC_DISCONNECTED      240L
#define ERROR_INVALID_EA_NAME      254L
#define ERROR_EA_LIST_INCONSISTENT 255L
#define ERROR_NO_MORE_ITEMS        259L
#define STILL_ACTIVE               259L  /* same value as ERROR_NO_MORE_ITEMS; cited by the CE GetExitCodeProcess page (ms885622) and CE CreateProcess page (ms885182) as the status of a process that has not terminated */

/* Rows 266-299: directory/EA/mutex errors. */
#define ERROR_CANNOT_COPY          266L
#define ERROR_DIRECTORY            267L
#define ERROR_EAS_DIDNT_FIT        275L
#define ERROR_EA_FILE_CORRUPT      276L
#define ERROR_EA_TABLE_FULL        277L
#define ERROR_INVALID_EA_HANDLE    278L
#define ERROR_EAS_NOT_SUPPORTED    282L
#define ERROR_NOT_OWNER            288L
#define ERROR_TOO_MANY_POSTS       298L
#define ERROR_PARTIAL_COPY         299L

/* Rows 317-536: message / address / arithmetic / pipe states. */
#define ERROR_MR_MID_NOT_FOUND     317L
#define ERROR_INVALID_ADDRESS      487L
#define ERROR_ARITHMETIC_OVERFLOW  534L
#define ERROR_PIPE_CONNECTED       535L
#define ERROR_PIPE_LISTENING       536L

/* Rows 994-1008: I/O and misc system errors. */
#define ERROR_EA_ACCESS_DENIED     994L
#define ERROR_OPERATION_ABORTED    995L
#define ERROR_IO_INCOMPLETE        996L
#define ERROR_IO_PENDING           997L
#define ERROR_NOACCESS             998L
#define ERROR_SWAPERROR            999L
#define ERROR_STACK_OVERFLOW      1001L
#define ERROR_INVALID_MESSAGE     1002L
#define ERROR_CAN_NOT_COMPLETE    1003L
#define ERROR_INVALID_FLAGS       1004L
#define ERROR_UNRECOGNIZED_VOLUME 1005L
#define ERROR_FILE_INVALID        1006L
#define ERROR_FULLSCREEN_MODE     1007L
#define ERROR_NO_TOKEN            1008L

/* Rows 1009-1022: registry errors. */
#define ERROR_BADDB               1009L
#define ERROR_BADKEY              1010L
#define ERROR_CANTOPEN            1011L
#define ERROR_CANTREAD            1012L
#define ERROR_CANTWRITE           1013L
#define ERROR_REGISTRY_RECOVERED  1014L
#define ERROR_REGISTRY_CORRUPT    1015L
#define ERROR_REGISTRY_IO_FAILED  1016L
#define ERROR_NOT_REGISTRY_FILE   1017L
#define ERROR_KEY_DELETED         1018L
#define ERROR_NO_LOG_SPACE        1019L
#define ERROR_KEY_HAS_CHILDREN    1020L
#define ERROR_CHILD_MUST_BE_VOLATILE  1021L
#define ERROR_NOTIFY_ENUM_DIR     1022L

/* Rows 1051-1078: service errors. */
#define ERROR_DEPENDENT_SERVICES_RUNNING      1051L
#define ERROR_INVALID_SERVICE_CONTROL         1052L
#define ERROR_SERVICE_REQUEST_TIMEOUT         1053L
#define ERROR_SERVICE_NO_THREAD               1054L
#define ERROR_SERVICE_DATABASE_LOCKED         1055L
#define ERROR_SERVICE_ALREADY_RUNNING         1056L
#define ERROR_INVALID_SERVICE_ACCOUNT         1057L
#define ERROR_SERVICE_DISABLED                1058L
#define ERROR_CIRCULAR_DEPENDENCY             1059L
#define ERROR_SERVICE_DOES_NOT_EXIST          1060L
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL      1061L
#define ERROR_SERVICE_NOT_ACTIVE              1062L
#define ERROR_FAILED_SERVICE_CONTROLLER_CONNECT 1063L
#define ERROR_EXCEPTION_IN_SERVICE            1064L
#define ERROR_DATABASE_DOES_NOT_EXIST         1065L
#define ERROR_SERVICE_SPECIFIC_ERROR          1066L
#define ERROR_PROCESS_ABORTED                 1067L
#define ERROR_SERVICE_DEPENDENCY_FAIL         1068L
#define ERROR_SERVICE_LOGON_FAILED            1069L
#define ERROR_SERVICE_START_HANG              1070L
#define ERROR_INVALID_SERVICE_LOCK            1071L
#define ERROR_SERVICE_MARKED_FOR_DELETE       1072L
#define ERROR_SERVICE_EXISTS                  1073L
#define ERROR_ALREADY_RUNNING_LKG             1074L
#define ERROR_SERVICE_DEPENDENCY_DELETED      1075L
#define ERROR_BOOT_ALREADY_ACCEPTED           1076L
#define ERROR_SERVICE_NEVER_STARTED           1077L
#define ERROR_DUPLICATE_SERVICE_NAME          1078L

/* ERROR_NO_UNICODE_TRANSLATION (1113): outside the rows of the CE
 * numeric table captured above; cited as the failure code of the CE
 * string-conversion functions by the official CE pages ms915519
 * (WideCharToMultiByte) and ms961248 (MultiByteToWideChar). */
#define ERROR_NO_UNICODE_TRANSLATION         1113L

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINERROR_H */
