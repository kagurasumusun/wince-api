/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: winerror.h
 *
 * System Error Codes.
 */

#ifndef _WINERROR_H_
#define _WINERROR_H_

#define ERROR_SUCCESS                    0L
#define NO_ERROR                         0L
#define ERROR_INVALID_FUNCTION           1L
#define ERROR_FILE_NOT_FOUND             2L
#define ERROR_PATH_NOT_FOUND             3L
#define ERROR_TOO_MANY_OPEN_FILES        4L
#define ERROR_ACCESS_DENIED              5L
#define ERROR_INVALID_HANDLE             6L
#define ERROR_ARENA_TRASHED              7L
#define ERROR_NOT_ENOUGH_MEMORY          8L
#define ERROR_INVALID_BLOCK              9L
#define ERROR_BAD_ENVIRONMENT            10L
#define ERROR_BAD_FORMAT                 11L
#define ERROR_INVALID_ACCESS             12L
#define ERROR_INVALID_DATA               13L
#define ERROR_OUTOFMEMORY                14L
#define ERROR_INVALID_DRIVE              15L
#define ERROR_CURRENT_DIRECTORY          16L
#define ERROR_NOT_SAME_DEVICE            17L
#define ERROR_NO_MORE_FILES              18L
#define ERROR_WRITE_PROTECT              19L
#define ERROR_BAD_UNIT                   20L
#define ERROR_NOT_READY                  21L
#define ERROR_BAD_COMMAND                22L
#define ERROR_CRC                        23L
#define ERROR_BAD_LENGTH                 24L
#define ERROR_SEEK                       25L
#define ERROR_NOT_DOS_DISK               26L
#define ERROR_SECTOR_NOT_FOUND           27L
#define ERROR_OUT_OF_PAPER               28L
#define ERROR_WRITE_FAULT                29L
#define ERROR_READ_FAULT                 30L
#define ERROR_GEN_FAILURE                31L
#define ERROR_SHARING_VIOLATION          32L
#define ERROR_LOCK_VIOLATION             33L
#define ERROR_WRONG_DISK                 34L
#define ERROR_SHARING_BUFFER_EXCEEDED    36L
#define ERROR_HANDLE_EOF                 38L
#define ERROR_HANDLE_DISK_FULL           39L
#define ERROR_NOT_SUPPORTED              50L
#define ERROR_REM_NOT_LIST               51L
#define ERROR_DUP_NAME                   52L
#define ERROR_BAD_NETPATH                53L
#define ERROR_NETWORK_BUSY               54L
#define ERROR_DEV_NOT_EXIST              55L
#define ERROR_TOO_MANY_CMDS              56L
#define ERROR_ADAP_HDW_ERR               57L
#define ERROR_BAD_NET_RESP               58L
#define ERROR_UNEXP_NET_ERR              59L
#define ERROR_BAD_REM_ADAP               60L
#define ERROR_PRINTQ_FULL                61L
#define ERROR_NO_SPOOL_SPACE             62L
#define ERROR_PRINT_CANCELLED            63L
#define ERROR_NETNAME_DELETED            64L
#define ERROR_NETWORK_ACCESS_DENIED      65L
#define ERROR_BAD_DEV_TYPE               66L
#define ERROR_BAD_NET_NAME               67L
#define ERROR_TOO_MANY_NAMES             68L
#define ERROR_TOO_MANY_SESS              69L
#define ERROR_SHARING_PAUSED             70L
#define ERROR_REQ_NOT_ACCEP              71L
#define ERROR_REDIR_PAUSED               72L
#define ERROR_FILE_EXISTS                80L
#define ERROR_CANNOT_MAKE                82L
#define ERROR_FAIL_I24                   83L
#define ERROR_OUT_OF_STRUCTURES          84L
#define ERROR_ALREADY_ASSIGNED           85L
#define ERROR_INVALID_PASSWORD           86L
#define ERROR_INVALID_PARAMETER          87L
#define ERROR_NET_WRITE_FAULT            88L
#define ERROR_NO_PROC_SLOTS              89L
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
#define ERROR_CALL_NOT_IMPLEMENTED       120L
#define ERROR_INSUFFICIENT_BUFFER        122L
#define ERROR_INVALID_NAME               123L
#define ERROR_MOD_NOT_FOUND              126L
#define ERROR_PROC_NOT_FOUND             127L
#define ERROR_WAIT_NO_CHILDREN           128L
#define ERROR_CHILD_NOT_COMPLETE         129L
#define ERROR_DIRECT_HISTORY_REQUIRED    130L
#define ERROR_ERROR_MODE_LOCKED          132L
#define ERROR_SEEK_ON_DEVICE             133L
#define ERROR_ALREADY_EXISTS             183L
#define ERROR_FILENAME_EXCED_RANGE       206L

#endif /* _WINERROR_H_ */
