/* Upnphost.h -- UPnP COM host API (IUPnPRegistrar &c., Uuid.lib rows; Windows CE .NET 4.0+).  Pages: tools/manifests/servers.manifest (UPnP node).  See docs/inventory.md M75b. */

#ifndef AKARI_UPNPHOST_H
#define AKARI_UPNPHOST_H

#include "Windef.h"    /* DWORD, BOOL, HWND, WINAPI */
#include "Objbase.h"   /* IUnknown, HRESULT, IDispatch context */

/* COM interfaces (Uuid.lib rows; no import surface): opaque
 * forwards + verbatim method/property records. */
typedef struct IUPnPDeviceControl IUPnPDeviceControl;
typedef struct IUPnPEventSink IUPnPEventSink;
typedef struct IUPnPEventSource IUPnPEventSource;
typedef struct IUPnPRegistrar IUPnPRegistrar;
typedef struct IUPnPReregistrar IUPnPReregistrar;

/* IUPnPDeviceControl (aa450655):
 *   IUPnPDeviceControl (aa450655)
 */

/* IUPnPEventSink (aa450712):
 *   IUPnPEventSink (aa450712)
 */

/* IUPnPEventSource (aa450716):
 *   IUPnPEventSource (aa450716)
 */

/* IUPnPRegistrar (aa450719):
 *   IUPnPRegistrar (aa450719)
 */

/* IUPnPReregistrar (aa450723):
 *   IUPnPReregistrar (aa450723)
 */

/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450651 IUPnPDeviceControl::GetServiceObject (Header: Upnphost.h.) */
/* aa450653 IUPnPDeviceControl::Initialize (Header: Upnphost.h.) */
/* aa450713 IUPnPEventSink::OnStateChanged (Header: Upnphost.h.) */
/* aa450714 IUPnPEventSink::OnStateChangedSafe (Header: Upnphost.h.) */
/* aa450715 IUPnPEventSource::Advise (Header: Upnphost.h.) */
/* aa450717 IUPnPEventSource::Unadvise (Header: Upnphost.h.) */
/* aa450718 IUPnPRegistrar::GetUniqueDeviceName (Header: Upnphost.h.) */
/* aa450720 IUPnPRegistrar::RegisterDevice (Header: Upnphost.h.) */
/* aa450721 IUPnPRegistrar::RegisterRunningDevice (Header: Upnphost.h.) */
/* aa450722 IUPnPRegistrar::UnregisterDevice (Header: Upnphost.h.) */
/* aa450724 IUPnPReregistrar::ReregisterDevice (Header: Upnphost.h.) */
/* aa450725 IUPnPReregistrar::ReregisterRunningDevice (Header: Upnphost.h.) */
#endif /* AKARI_UPNPHOST_H */
