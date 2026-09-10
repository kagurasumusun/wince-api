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

/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450629 IUPnPDescriptionDocument::Abort (Header: Upnp.h.) */
/* aa450635 IUPnPDescriptionDocument::DeviceByUDN (Header: Upnp.h.) */
/* aa450639 IUPnPDescriptionDocument::Load (Header: Upnp.h.) */
/* aa450641 IUPnPDescriptionDocument::LoadAsync (Header: Upnp.h.) */
/* aa450643 IUPnPDescriptionDocument::LoadResult (Header: Upnp.h.) */
/* aa450645 IUPnPDescriptionDocument::ReadyState (Header: Upnp.h.) */
/* aa450647 IUPnPDescriptionDocument::RootDevice (Header: Upnp.h.) */
/* aa450633 IUPnPDescriptionDocumentCallback::LoadComplete (Header: Upnp.h.) */
/* aa450649 IUPnPDevice::Children (Header: Upnp.h.) */
/* aa450657 IUPnPDevice::Description (Header: Upnp.h.) */
/* aa450682 IUPnPDevice::FriendlyName (Header: Upnp.h.) */
/* aa450683 IUPnPDevice::HasChildren (Header: Upnp.h.) */
/* aa450684 IUPnPDevice::IconURL (Header: Upnp.h.) */
/* aa450686 IUPnPDevice::IsRootDevice (Header: Upnp.h.) */
/* aa450687 IUPnPDevice::ManufacturerName (Header: Upnp.h.) */
/* aa450688 IUPnPDevice::ManufacturerURL (Header: Upnp.h.) */
/* aa450689 IUPnPDevice::ModelName (Header: Upnp.h.) */
/* aa450690 IUPnPDevice::ModelNumber (Header: Upnp.h.) */
/* aa450691 IUPnPDevice::ModelURL (Header: Upnp.h.) */
/* aa450692 IUPnPDevice::ParentDevice (Header: Upnp.h.) */
/* aa450693 IUPnPDevice::PresentationURL (Header: Upnp.h.) */
/* aa450694 IUPnPDevice::RootDevice (Header: Upnp.h.) */
/* aa450697 IUPnPDevice::SerialNumber (Header: Upnp.h.) */
/* aa450699 IUPnPDevice::Services (Header: Upnp.h.) */
/* aa450707 IUPnPDevice::Type (Header: Upnp.h.) */
/* aa450710 IUPnPDevice::UniqueDeviceName (Header: Upnp.h.) */
/* aa450711 IUPnPDevice::UPC (Header: Upnp.h.) */
/* aa450659 IUPnPDeviceDocumentAccess::GetDocumentURL (Header: Upnp.h.) */
/* aa450672 IUPnPDeviceFinder::CancelAsyncFind (Header: Upnp.h.) */
/* aa450674 IUPnPDeviceFinder::CreateAsyncFind (Header: Upnp.h.) */
/* aa450676 IUPnPDeviceFinder::FindByType (Header: Upnp.h.) */
/* aa450678 IUPnPDeviceFinder::FindByUDN (Header: Upnp.h.) */
/* aa450681 IUPnPDeviceFinder::StartAsyncFind (Header: Upnp.h.) */
/* aa450663 IUPnPDeviceFinderCallback::DeviceAdded (Header: Upnp.h.) */
/* aa450665 IUPnPDeviceFinderCallback::DeviceRemoved (Header: Upnp.h.) */
/* aa450670 IUPnPDeviceFinderCallback::SearchComplete (Header: Upnp.h.) */
/* aa450705 IUPnPDevices::_NewEnum (Header: Upnp.h.) */
/* aa450695 IUPnPDevices::Count (Header: Upnp.h.) */
/* aa450703 IUPnPDevices::Item (Header: Upnp.h.) */
/* aa450726 IUPnPService::AddCallback (Header: Upnp.h.) */
/* aa450730 IUPnPService::Id (Header: Upnp.h.) */
/* aa450732 IUPnPService::InvokeAction (Header: Upnp.h.) */
/* aa450733 IUPnPService::LastTransportStatus (Header: Upnp.h.) */
/* aa450734 IUPnPService::QueryStateVariable (Header: Upnp.h.) */
/* aa450736 IUPnPService::ServiceTypeIdentifier (Header: Upnp.h.) */
/* aa450728 IUPnPServiceCallback::ServiceInstanceDied (Header: Upnp.h.) */
/* aa450729 IUPnPServiceCallback::StateVariableChanged (Header: Upnp.h.) */
/* ms893153 IUPnPServices::_NewEnum (Header: Upnp.h.) */
/* aa450735 IUPnPServices::Count (Header: Upnp.h.) */
/* ms893062 IUPnPServices::Item (Header: Upnp.h.) */
#endif /* AKARI_UPNP_H */
