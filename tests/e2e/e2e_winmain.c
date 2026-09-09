/*
 * e2e_winmain.c -- end-to-end link consumer: WinMain() program.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Linked by `make e2e` against the doc-derived import libraries with
 * /entry:WinMainCRTStartup.  Exercises the window/UI surface from a
 * second component DLL (MessageBoxW, msgbox.dll) plus coredll.  The
 * documented CE WinMain signature (hPrevInstance always NULL) comes
 * from the official WinMain page (ms914104).
 */

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPWSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;
    MessageBoxW(hInstance, L"Akari API e2e", L"winmain", 0);
    return (int)GetTickCount() & 0x7F;
}
