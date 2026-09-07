/* Verification test for fundamental wince-api types and definitions */
#include <sdkddkver.h>
#include <windef.h>
#include <winnt.h>
#include <winerror.h>

C_ASSERT(sizeof(BYTE) == 1);
C_ASSERT(sizeof(WORD) == 2);
C_ASSERT(sizeof(DWORD) == 4);
C_ASSERT(sizeof(HANDLE) == 4);
C_ASSERT(sizeof(LONG_PTR) == 4);
C_ASSERT(sizeof(ULONG_PTR) == 4);
C_ASSERT(sizeof(RECT) == 16);
C_ASSERT(sizeof(POINT) == 8);
C_ASSERT(sizeof(SIZE) == 8);
C_ASSERT(sizeof(CRITICAL_SECTION) == 20);

int main(void) {
    DWORD dw = 0x12345678;
    WORD wLo = LOWORD(dw);
    WORD wHi = HIWORD(dw);
    if (wLo != 0x5678 || wHi != 0x1234) return 1;
    return 0;
}
