/* Verification test for additional WinCE headers */
#include <windows.h>
#include <sipapi.h>
#include <aygshell.h>
#include <commctrl.h>
#include <winsock2.h>
#include <ws2def.h>

int main(void) {
    SIPINFO sipInfo;
    sipInfo.cbSize = sizeof(SIPINFO);
    SipShowIM(SIPF_ON);

    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    WSADATA wsaData;
    WSAStartup(0x0202, &wsaData);
    WSACleanup();

    return 0;
}
