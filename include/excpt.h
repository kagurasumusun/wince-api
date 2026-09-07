/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: excpt.h
 *
 * Exception handling constants and types.
 */

#ifndef _EXCPT_H_
#define _EXCPT_H_

typedef enum _EXCEPTION_DISPOSITION {
    ExceptionContinueExecution = 0,
    ExceptionContinueSearch = 1,
    ExceptionNestedException = 2,
    ExceptionCollidedUnwind = 3
} EXCEPTION_DISPOSITION;

#define EXCEPTION_EXECUTE_HANDLER      1
#define EXCEPTION_CONTINUE_SEARCH      0
#define EXCEPTION_CONTINUE_EXECUTION (-1)

#endif /* _EXCPT_H_ */
