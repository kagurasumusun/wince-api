/* Upnp.h -- UPnP COM device API (IUPnP* interfaces, Uuid.lib rows; Windows CE .NET 4.0+).  Pages: tools/manifests/servers.manifest (UPnP node).  See docs/inventory.md M75b. */

#ifndef AKARI_UPNP_H
#define AKARI_UPNP_H

#include "Windef.h"    /* DWORD, BOOL, HWND, WINAPI */
#include "Objbase.h"   /* IUnknown, HRESULT, IDispatch context */

/* COM interfaces (Uuid.lib rows; no import surface): opaque
 * forwards + verbatim method/property records. */
typedef struct IUPnPDescriptionDocument IUPnPDescriptionDocument;
typedef struct IUPnPDescriptionDocumentCallback IUPnPDescriptionDocumentCallback;
typedef struct IUPnPDevice IUPnPDevice;
typedef struct IUPnPDeviceFinder IUPnPDeviceFinder;
typedef struct IUPnPDeviceFinderCallback IUPnPDeviceFinderCallback;
typedef struct IUPnPDeviceDocumentAccess IUPnPDeviceDocumentAccess;
typedef struct IUPnPDevices IUPnPDevices;
typedef struct IUPnPService IUPnPService;
typedef struct IUPnPServiceCallback IUPnPServiceCallback;
typedef struct IUPnPServices IUPnPServices;

/* IUPnPDescriptionDocument (aa450637):
 *   IUPnPDescriptionDocument (aa450637)
 */

/* IUPnPDescriptionDocumentCallback (aa450631):
 *   IUPnPDescriptionDocumentCallback (aa450631)
 */

/* IUPnPDevice (aa450685):
 *   IUPnPDevice (aa450685)
 */

/* IUPnPDeviceFinder (aa450680):
 *   IUPnPDeviceFinder (aa450680)
 */

/* IUPnPDeviceFinderCallback (aa450668):
 *   IUPnPDeviceFinderCallback (aa450668)
 */

/* IUPnPDeviceDocumentAccess (aa450661):
 *   IUPnPDeviceDocumentAccess (aa450661)
 */

/* IUPnPDevices (aa450701):
 *   IUPnPDevices (aa450701)
 */

/* IUPnPService (aa450731):
 *   IUPnPService (aa450731)
 */

/* IUPnPServiceCallback (aa450727):
 *   IUPnPServiceCallback (aa450727)
 */

/* IUPnPServices (aa450737):
 *   IUPnPServices (aa450737)
 */

#endif /* AKARI_UPNP_H */
