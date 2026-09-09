/*
 * e2e_console.c -- end-to-end link consumer: main() program.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Linked by `make e2e` with the Akari CRT (wince-crt) startup objects
 * and the doc-derived import libraries (the def directory, doc def
 * files, via llvm-dlltool -m armce) into a Windows CE PE executable; it
 * exercises the coredll import surface the headers declare
 * (GetTickCount, GetSystemInfo, the local heap, GetModuleHandleW,
 * GetLastError, and the CE 5.0+ CopyFileExW export, M38).  It must
 * compile warning-free for every *-pc-wince target and link to a PE
 * whose import directory names only the real CE DLLs (coredll.dll
 * and friends).
 */

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <tapi.h>
#include <tapicomn.h>
#include <imm.h>
#include <wincrypt.h>
#include <winscard.h>
#include <objbase.h>
#include <aygshell.h>
#include <shellsdk.h>
#include <shlobj.h>
#include <newmenu.h>
#include <sipapi.h>
#include <sip.h>
#include <keybd.h>
#include <pwinuser.h>
#include <shtypes.h>
#include <shobjidl.h>
#include <shellapi.h>
#include <cpl.h>
#include <shelwapi.h>
#include <windowsx.h>
#include <commdlg.h>
#include <commctrl.h>
#include <winldap.h>
#include <winber.h>
#include <cchannel.h>
#include <bt_api.h>
#include <bthsdpdef.h>
#include <ws2bth.h>
#include <btagpub.h>
#include <btagnetwork.h>
#include <snmp.h>
#include <snmpapi.h>
#include <snmpexts.h>
#include <pm.h>
#include <ceddk.h>
#include <ddraw.h>
#include <urlmon.h>

int main(void)
{
    SYSTEM_INFO si;
    LPVOID p;
    DWORD tick;
    HMODULE mod;
    BOOL ok;

    tick = GetTickCount();
    GetSystemInfo(&si);
    p = LocalAlloc(LPTR, 64);
    ok = (p != NULL);
    if (p != NULL)
        LocalFree(p);
    mod = GetModuleHandleW(L"coredll.dll");
    if (mod == NULL)
        ok = FALSE;
    /* M38: CopyFileExW (CE 5.0+, aa517311) -- linked, not run: the
     * image must export it per the doc-derived def. */
    (void) CopyFileExW(L"a", L"b", NULL, NULL, NULL,
                       COPY_FILE_FAIL_IF_EXISTS);
    /* M39: Winsock (Ws2.lib) import surface -- linked, not run: the
     * image must import the Ws2.lib-documented names from ws2.dll
     * per the doc-derived def. */
    (void) socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    (void) WSAStartup(WSAVersion(2, 2), (LPWSADATA)0);
    (void) getaddrinfo((const char *)0, (const char *)0,
                       (const struct addrinfo *)0, (struct addrinfo **)0);
    /* M41: Winsock name service (name spaces) -- linked, not run. */
    (void) WSAEnumNameSpaceProviders(NULL, NULL);
    (void) WSALookupServiceBegin(NULL, 0, NULL);
    (void) WSALookupServiceEnd(NULL);
    (void) WSALookupServiceNext(NULL, 0, NULL, NULL);
    (void) WSASetService(NULL, RNRSERVICE_REGISTER, 0);
    /* M42: Winsock SPI (Ws2spi.h) import surface -- linked, not run. */
    (void) WSPStartup(WSAVersion(2, 2), NULL, NULL, NULL, NULL);
    (void) WSPCleanup(NULL);
    (void) NSPSetService(NULL, NULL, NULL, RNRSERVICE_REGISTER, 0);
    (void) NSPLookupServiceNext(NULL, 0, NULL, NULL);
    /* M43: TAPI/TSPI (Tapicomn.h) import surface -- linked, not run. */
    (void) TSPI_lineOpen(0, NULL, NULL, 0, NULL);
    (void) TSPI_phoneGetDevCaps(0, 0, 0, NULL);
    /* M45: TAPI client runtime (Tapi.h) import surface + the M43
     * TSPI_lineForward hold closure -- linked, not run: the image
     * must import the documented coredll names per the doc-derived
     * def. */
    {
        HLINE hLine = (HLINE)0;
        HCALL hCall = (HCALL)0;
        HPHONE hPhone = (HPHONE)0;
        (void) lineInitializeEx(NULL, NULL, NULL, NULL, NULL, NULL,
                                NULL);
        (void) lineNegotiateAPIVersion((HLINEAPP)0, 0, 0, 0, NULL,
                                       NULL);
        (void) lineOpen((HLINEAPP)0, 0, &hLine, 0, 0, 0, 0, 0, NULL);
        (void) lineMakeCall(hLine, &hCall, NULL, 0, NULL);
        (void) lineForward(hLine, 0, 0, (LPLINEFORWARDLIST)0, 0, NULL,
                           NULL);
        (void) lineDrop(hCall, NULL, 0);
        (void) lineClose(hLine);
        (void) lineShutdown((HLINEAPP)0);
        (void) phoneOpen((HPHONEAPP)0, 0, &hPhone, 0, 0, 0, 0);
        (void) phoneGetStatus(hPhone, NULL);
        (void) phoneClose(hPhone);
        (void) TSPI_lineForward(0, (HDRVLINE)0, 0, 0,
                                (LPLINEFORWARDLIST)0, 0, (HTAPICALL)0,
                                NULL, NULL);
    }
    /* M46: IMM (Imm.h / Coreimm.lib) import surface -- linked, not
     * run: the image must import the Coreimm.lib-documented names
     * from coreimm.dll per the doc-derived def. */
    {
        HIMC hIMC = ImmGetContext((HWND)0);
        (void) ImmReleaseContext((HWND)0, hIMC);
        (void) ImmGetOpenStatus(hIMC);
        (void) ImmNotifyIME(hIMC, 0, 0, 0);
        (void) ImmSIPanelState(0, NULL);
    }
    /* M47: Cryptography base CSP unit (Wincrypt.h / Coredll.lib) --
     * linked, not run: the image must import the documented Crypt*
     * names from coredll.dll per the doc-derived def. */
    {
        HCRYPTPROV hProv = 0;
        HCRYPTHASH hHash = 0;
        HCRYPTMSG  hMsg  = 0;
        DATA_BLOB  in = {0}, out = {0};
        (void) CryptAcquireContext(&hProv, NULL, NULL, 0, 0);
        (void) CryptCreateHash(hProv, 0, 0, 0, &hHash);
        (void) CryptGenRandom(hProv, 0, NULL);
        (void) CryptDestroyHash(hHash);
        (void) CryptReleaseContext(hProv, 0);
        hMsg = CryptMsgOpenToEncode(0, 0, 0, NULL, NULL, NULL);
        (void) CryptMsgClose(hMsg);
        (void) CryptProtectData(&in, NULL, NULL, NULL, NULL, 0, &out);
    }
    /* M48: Cryptography certificate / encode / OID / PFX unit
     * (Wincrypt.h / Crypt32.lib) -- linked, not run: the image must
     * import the documented Crypt32.lib names from crypt32.dll per
     * the doc-derived def. */
    {
        HCERTSTORE hStore = 0;
        CRYPT_DATA_BLOB pfx = {0};
        PCCERT_CONTEXT pCert = 0;
        hStore = CertOpenStore(0, 0, 0, 0, 0);
        pCert = CertCreateCertificateContext(0, 0, 0);
        (void) CertFindCertificateInStore(hStore, 0, 0, 0, 0, 0);
        (void) CertCloseStore(hStore, 0);
        (void) CryptEncodeObjectEx(0, 0, 0, 0, 0, 0, 0);
        (void) PFXImportCertStore(&pfx, 0, 0);
        (void) PFXIsPFXBlob(&pfx);
        (void) pCert;
    }
    /* M49: Smart Card subsystem (Winscard.h / Winscard.lib) --
     * linked, not run: the image must import the documented
     * Winscard.lib names from winscard.dll per the doc-derived def. */
    {
        /* static: keeps the zeroing out of the AEABI memclr path the
         * CRT does not ship (linked, never run). */
        static SCARD_READERSTATE rs;
        SCARDCONTEXT hContext = 0;
        SCARDHANDLE  hCard    = 0;
        (void) SCardEstablishContext(0, 0, 0, &hContext);
        (void) SCardConnect(hContext, 0, 0, 0, &hCard, 0);
        (void) SCardGetStatusChange(hContext, 0, &rs, 0);
        (void) SCardTransmit(hCard, 0, 0, 0, 0, 0, 0);
        (void) SCardDisconnect(hCard, 0);
        (void) SCardReleaseContext(hContext);
    }
    /* M50: AYGShell unit (Aygshell.h / Shellsdk.h / Newmenu.h /
     * Shlobj.h; Aygshell.lib) -- linked, not run: the image must
     * import the documented Aygshell.lib names from aygshell.dll per
     * the doc-derived def.  Locals are left uninitialized (M44
     * style): the freestanding ARM link has no compiler-rt memclr
     * helpers, so aggregate zero-initializers are avoided. */
    {
        SHMENUBARINFO      mbi;
        SHNOTIFICATIONDATA nd;
        SHACTIVATEINFO     sai;
        SHINITDLGINFO      sidi;
        CLSID              clsid;
        mbi.cbSize    = sizeof(mbi);
        nd.cbStruct   = sizeof(nd);
        sai.cbSize    = sizeof(sai);
        sidi.dwMask   = SHIDIM_FLAGS;
        sidi.hDlg      = (HWND)0;
        clsid.Data1   = 0;
        (void) SHCreateMenuBar(&mbi);
        (void) SHFindMenuBar((HWND)0);
        (void) SHFullScreen((HWND)0, 0);
        (void) SHDoneButton((HWND)0, 0);
        (void) SHHandleWMActivate((HWND)0, 0, 0, &sai, 0);
        (void) SHHandleWMSettingChange((HWND)0, 0, 0, &sai);
        (void) SHInitDialog(&sidi);
        (void) SHInitExtraControls();
        (void) SHSipInfo(0, 0, (PVOID)0, 0);
        (void) SHNotificationAdd(&nd);
        (void) SHNotificationRemove(&clsid, 0);
        (void) SHChangeNotifyRegister((HWND)0, (SHCHANGENOTIFYENTRY *)0);
        (void) SHChangeNotifyFree((LPVOID)0);
        (void) SHRecognizeGesture((SHRGINFO *)0);
        (void) SHGetAutoRunPath((LPTSTR)0);
    }
    /* M51: Software-based Input Panel unit (Sipapi.h; Coredll.lib) --
     * linked, not run: the image must import the documented Sip*
     * names from coredll.dll per the doc-derived def.  The sip.h
     * IM/IME layer (IMINFO / LMDATA / the four interfaces) is
     * interface-record only.  Locals are left uninitialized (M44
     * style; no aggregate zero-initializers in freestanding links). */
    {
        SIPINFO    sipi;
        IMENUMINFO iei;
        CLSID      clsid2;
        RECT       rc2;
        sipi.cbSize     = sizeof(sipi);
        iei.clsid.Data1 = 0;
        clsid2.Data1    = 0;
        rc2.left        = 0;
        (void) SipEnumIM((IMENUMPROC)0);
        (void) SipGetCurrentIM(&clsid2);
        (void) SipGetInfo(&sipi);
        (void) SipRegisterNotification((HWND)0);
        (void) SipSetCurrentIM(&clsid2);
        (void) SipSetDefaultRect(&rc2);
        (void) SipSetInfo(&sipi);
        (void) SipShowIM(0);
        (void) SipStatus();
        {
            IInputMethod2 *piim2 = (IInputMethod2 *)0;
            (void) piim2;
        }
    }
    /* M52: OEM keyboard / derived-value unit -- linked, not run:
     * PostKeybdMessage + GetAsyncShiftFlags (Winuser.h / Pwinuser.h;
     * Kbdui.lib) and KeybdGetDeviceInfo (Pwinuser.h; Coredll.lib)
     * must import from kbdui.dll / coredll.dll per the doc-derived
     * defs; SHSipPreference (aygshell.lib, SIPSTATE derived) joins
     * the AYGShell import set.  M44 style: no aggregate
     * zero-initializers. */
    {
        GET_FOREGROUND_INFO gfi;
        KEY_STATE_FLAGS     ksf;
        UINT                shift = 0, chars = 0;
        gfi.hwndActive = (HWND)0;
        ksf            = (KEY_STATE_FLAGS)0;
        (void) PostKeybdMessage((HWND)0, VK_RETURN, ksf, 0, &shift, &chars);
        (void) GetAsyncShiftFlags(VK_RETURN);
        (void) KeybdGetDeviceInfo(0, (LPVOID)0);
        (void) SHSipPreference((HWND)0, SIP_UP);
        (void) gfi;
    }
    /* M53: Standard Shell Reference -- linked, not run: the image must
     * import the Ceshell.lib / Coredll.lib / Shmisc.lib-documented
     * names from ceshell.dll / coredll.dll / shmisc.dll per the
     * doc-derived defs.  Shell_NotifyIcon and SHGetFileInfo carry no
     * Link Library row on their CE 5.0 pages: they stay def-less
     * (verified by the host TU only, never linked here).
     * M44 style: no aggregate zero-initializers. */
    {
        BROWSEINFO        bi;
        NOTIFYICONDATA    nid;
        SHELLEXECUTEINFO  sei;
        SHFILEOPSTRUCT    fos;
        SHFILEINFO        sfi;
        STRRET            sr;
        LPITEMIDLIST      pidl = (LPITEMIDLIST)0;
        bi.hwndOwner = (HWND)0;
        nid.cbSize   = sizeof(nid);
        sei.cbSize   = sizeof(sei);
        fos.hwnd     = (HWND)0;
        sr.uType     = 0;
        sfi.iIcon    = 0;
        (void) SHBrowseForFolder(&bi);
        (void) SHGetSpecialFolderLocation((HWND)0, CSIDL_FAVORITES, &pidl);
        (void) SHGetPathFromIDList((LPCITEMIDLIST)pidl, (LPSTR)0);
        (void) SHGetDocumentsFolder((LPCTSTR)0, (LPTSTR)0);
        (void) SHFileOperation(&fos);
        (void) StrRetToBuf(&sr, (LPCITEMIDLIST)pidl, (LPTSTR)0, 0u);
        (void) SHGetMalloc((LPMALLOC *)0);
        (void) ShellExecuteEx(&sei);
        (void) SHGetSpecialFolderPath((HWND)0, (LPTSTR)0, CSIDL_PROGRAMS, 0);
        (void) SHAddToRecentDocs(0u, (LPCVOID)0);
        (void) SHCreateShortcut((LPTSTR)0, (LPTSTR)0);
        (void) SHGetShortcutTarget((LPTSTR)0, (LPTSTR)0, 0);
        (void) SHLoadDIBitmap((LPCTSTR)0);
        (void) SHShowOutOfMemory((HWND)0, 0u);
        (void) pidl;
        (void) nid;
        (void) sfi;
    }
    /* M44: COM (Ole32.lib / Oleaut32.lib) import surface -- linked,
     * not run: the image must import the Ole32.lib/Oleaut32.lib-
     * documented names from ole32.dll/oleaut32.dll per the doc-derived
     * defs. */
    {
        GUID g;
        BSTR b;
        VARIANTARG va;
        (void) CoCreateGuid(&g);
        (void) CoInitialize(NULL);
        (void) CoCreateInstanceEx((REFCLSID)&g, (IUnknown *)0,
                                  CLSCTX_INPROC_SERVER, (COSERVERINFO *)0,
                                  0, (MULTI_QI *)0);
        (void) CLSIDFromString((LPOLESTR)0, (LPCLSID)0);
        (void) CreateFileMoniker((LPCOLESTR)0, (LPMONIKER *)0);
        (void) StgCreateDocfile((const WCHAR *)0, STGM_READ, 0, (IStorage **)0);
        b = SysAllocString((OLECHAR *)0);
        (void) SysFreeString(b);
        (void) VariantInit(&va);
        (void) VariantClear(&va);
        (void) SafeArrayDestroy((SAFEARRAY *)0);
        (void) LoadTypeLib((OLECHAR *)0, (ITypeLib **)0);
    }
    /* M54: Common Controls batch 1 (Commctrl.lib / Commdlg.lib /
     * Fileopen.lib / Wldap32.lib import surfaces) -- linked, not run:
     * the image must import the doc-def-documented names. */
    {
        INITCOMMONCONTROLSEX icc;
        CHOOSECOLOR cc;
        OPENFILENAME ofn;
        REBARBANDINFO rbbi;
        LDAPControl lc;
        icc.dwSize = sizeof(icc);
        cc.lStructSize = sizeof(cc);
        ofn.lStructSize = sizeof(ofn);
        rbbi.cbSize = sizeof(rbbi);
        lc.ldctl_iscritical = (BOOLEAN)1;
        (void) InitCommonControls();
        (void) InitCommonControlsEx(&icc);
        (void) CommandBar_Create((HINSTANCE)0, (HWND)0, 1);
        (void) CommandBar_AddAdornments((HWND)0, 0, 0);
        (void) CommandBar_Height((HWND)0);
        (void) CommandBands_Create((HINSTANCE)0, (HWND)0, 1, 0,
                                   (HIMAGELIST)0);
        (void) CommandBands_AddBands((HWND)0, (HINSTANCE)0, 1, &rbbi);
        (void) CreateStatusWindow(0, (LPSTR)0, (HWND)0, 1);
        (void) DrawStatusText((HDC)0, (LPRECT)0, (LPCWSTR)0, 0);
        (void) ChooseColor(&cc);
        (void) CommDlgExtendedError();
        (void) GetOpenFileName(&ofn);
        (void) GetSaveFileName(&ofn);
        (void) ldap_init((PTCHAR)0, 389);
        (void) ldap_unbind((LDAP *)0);
        (void) ldap_get_option((LDAP *)0, LDAP_OPT_DESC, (void *)0);
        (void) ldap_control_free(&lc);
        (void) LdapGetLastError();
        (void) ber_alloc_t(LBER_USE_DER);
        (void) ber_free((BerElement *)0, 0);
    }
    {
        BT_ADDR ba = 0;
        BASEBAND_CONNECTION bbc;
        BthInquiryResult inq;
        SOCKADDR_BTH sabth;
        AsnAny aa;
        AsnObjectIdentifier aoi;
        SnmpVarBindList vbl;
        DMA_ADAPTER_OBJECT dao;
        PHYSICAL_ADDRESS pa;
        bbc.hConnection = 0;
        inq.cod = 0;
        sabth.port = 0;
        aa.asnType = 0;
        aoi.idLength = 0;
        vbl.len = 0;
        dao.ObjectSize = 0;
        pa.QuadPart = 0;
        (void) BthReadLocalAddr(&ba);
        (void) BthPerformInquiry(0, 0, 0, 0, (unsigned int *)0, &inq);
        (void) BthGetBasebandConnections(1, &bbc, (int *)0);
        (void) BthNsLookupServiceBegin((LPWSAQUERYSET)0, 0,
                                       (LPHANDLE)0);
        (void) BthAGPhoneExtInit();
        (void) BthAGNetworkDropCall(NETWORK_FLAGS_DROP_ALL);
        (void) BthAGOnNetworkEvent(0, (LPSTR)0);
        (void) SnmpUtilOctetsCmp((AsnOctetString *)0,
                                 (AsnOctetString *)0);
        (void) SnmpUtilOidCmp(&aoi, &aoi);
        (void) SnmpUtilAsnAnyCpy(&aa, &aa);
        (void) SnmpUtilMemAlloc(0);
        (void) SnmpExtensionQuery(0, &vbl, (AsnInteger32 *)0,
                                  (AsnInteger32 *)0);
        (void) SnmpTfxOpen(1, (SnmpMibView *)0);
        (void) HalAllocateCommonBuffer(&dao, 0,
                                       (PPHYSICAL_ADDRESS)0, 0);
        (void) HalTranslateBusAddress(PCIBus, 0, pa, (PULONG)0,
                                      (PPHYSICAL_ADDRESS)0);
        (void) READ_PORT_ULONG((PULONG)0);
        (void) MmMapIoSpace(pa, 0, 0);

        /* M59: DirectDraw (Ddraw.lib, aa451583..aa451586). */
        {
            LPDIRECTDRAW           pdd = (LPDIRECTDRAW)0;
            LPDIRECTDRAWCLIPPER    pddc = (LPDIRECTDRAWCLIPPER)0;
            DDCAPS                 dcap;
            DDSURFACEDESC2         dsd2;
            DDPIXELFORMAT          dpf;

            dcap.dwSize = sizeof(DDCAPS);
            dcap.ddsCaps.dwCaps = 0;
            dsd2.dwSize = sizeof(DDSURFACEDESC2);
            dsd2.dwTextureStage = 0;
            dpf.dwSize = sizeof(DDPIXELFORMAT);
            dpf.dwRGBBitCount = 16;
            (void) DirectDrawCreate((GUID FAR *)0, &pdd,
                                    (IUnknown FAR *)0);
            (void) DirectDrawCreateClipper(0u, &pddc,
                                           (IUnknown FAR *)0);
            (void) DirectDrawEnumerate((LPDDENUMCALLBACK)0,
                                       (LPVOID)0);
            (void) DirectDrawEnumerateEx((LPDDENUMCALLBACKEX)0,
                                         (LPVOID)0, 0u);
            (void) pdd; (void) pddc; (void) dcap; (void) dsd2;
            (void) dpf;
        }

        /* M60: URL Moniker Services (Urlmon.lib). */
        {
            PROTOCOLDATA       pd;
            HIT_LOGGING_INFO   hli;
            BINDINFO           bi;
            IInternetSession  *pses = (IInternetSession *)0;

            pd.grfFlags = 0; pd.cbData = 0;
            hli.dwStructSize = sizeof(HIT_LOGGING_INFO);
            bi.cbSize = sizeof(BINDINFO);
            bi.dwBindVerb = (DWORD)BINDVERB_GET;
            (void) CoInternetGetSession(0u, &pses, 0u);
            (void) CoInternetGetSecurityUrl((LPCWSTR)0, (LPWSTR *)0,
                                            PSU_DEFAULT, 0u);
            (void) CreateURLMoniker((IMoniker *)0, (LPWSTR)0,
                                    (IMoniker **)0);
            (void) RegisterMediaTypes(0u, (LPCSTR *)0,
                                      (CLIPFORMAT *)0);
            (void) ReleaseBindInfo(&bi);
            (void) IsLoggingEnabledW((LPCTSTR)0);
            (void) URLDownloadToFileW((LPUNKNOWN)0, (LPCTSTR)0,
                                      (LPCTSTR)0, 0u,
                                      (LPBINDSTATUSCALLBACK)0);
            (void) WriteHitLogging(&hli);
            (void) pd; (void) hli; (void) bi; (void) pses;
        }
    }
    (void)tick;
    (void)si;
    (void)mod;
    if (!ok)
        SetLastError(ERROR_INTERNAL_ERROR);
    return ok ? 0 : 1;
}
