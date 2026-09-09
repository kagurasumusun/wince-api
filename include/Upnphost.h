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

#endif /* AKARI_UPNPHOST_H */
