/* Av_upnp.h -- UPnP AV framework (Windows CE 5.0).
 *
 * Pages: tools/manifests/servers.manifest (Servers book,
 * Universal Plug and Play node); Link Library rows print
 * Av_upnp.lib for all 148 pages -- the documented C++ class/
 * interface library.  A C API layer cannot compile this surface,
 * so every class, method and type page is recorded verbatim
 * (page id + printed signature).  Av_upnp.lib is the class library,
 * not a DLL import surface -- no def file.  See docs/inventory.md
 * M76.
 */

#ifndef AKARI_AV_UPNP_H
#define AKARI_AV_UPNP_H

#include "Windef.h"    /* DWORD */


/* --- AVTransportState (1 page) ---
 *   aa450295  AVTransportState : (no print)
 */

/* --- DeviceCapabilities (1 page) ---
 *   aa450330  DeviceCapabilities : (no print)
 */

/* --- DIRECTION (1 page) ---
 *   aa450332  DIRECTION : (no print)
 */

/* --- General String Constants (1 page) ---
 *   aa450391  General String Constants : (no print)
 */

/* --- IRenderingControl (37 pages) ---
 *   aa450476  IRenderingControl : (no print)
 *   aa450477  IRenderingControl::GetBlueVideoBlackLevel : virtual DWORD GetBlueVideoBlackLevel( unsigned short* pBlueVideoBlackLevel) = 0;
 *   aa450478  IRenderingControl::GetBlueVideoGain : virtual DWORD GetBlueVideoGain( unsigned short* pBlueVideoGain) = 0;
 *   aa450479  IRenderingControl::GetBrightness : virtual DWORD GetBrightness( unsigned short* pBrightness) = 0;
 *   aa450480  IRenderingControl::GetColorTemperature : virtual DWORD GetColorTemperature( unsigned short* pColorTemperature) = 0;
 *   aa450481  IRenderingControl::GetContrast : virtual DWORD GetContrast( unsigned short* pContrast) = 0;
 *   aa450482  IRenderingControl::GetGreenVideoBlackLevel : virtual DWORD GetGreenVideoBlackLevel( unsigned short* pGreenVideoBlackLevel) = 0;
 *   aa450483  IRenderingControl::GetGreenVideoGain : virtual DWORD GetGreenVideoGain( unsigned short* pGreenVideoGain) = 0;
 *   aa450484  IRenderingControl::GetHorizontalKeystone : virtual DWORD GetHorizontalKeystone( short* pHorizontalKeystone) = 0;
 *   aa450485  IRenderingControl::GetLoudness : virtual DWORD GetLoudness( LPCWSTR pszChannel, bool* pLoudness) = 0;
 *   aa450486  IRenderingControl::GetMute : virtual DWORD GetMute( LPCWSTR pszChannel, bool* pMute) = 0;
 *   aa450487  IRenderingControl::GetRedVideoBlackLevel : virtual DWORD GetRedVideoBlackLevel( unsigned short* pRedVideoBlackLevel) = 0;
 *   aa450488  IRenderingControl::GetRedVideoGain : virtual DWORD GetRedVideoGain( unsigned short* pRedVideoGain) = 0;
 *   aa450489  IRenderingControl::GetSharpness : virtual DWORD GetSharpness( unsigned short* pSharpness) = 0;
 *   ms890314  IRenderingControl::GetVerticalKeystone : virtual DWORD GetVerticalKeystone( short* pVerticalKeystone) = 0;
 *   aa450490  IRenderingControl::GetVolume : virtual DWORD GetVolume( LPCWSTR pszChannel, unsigned short* pVolume) = 0;
 *   aa450492  IRenderingControl::GetVolumeDB : virtual DWORD GetVolumeDB( LPCWSTR pszChannel, short* pVolumeDB) = 0;
 *   aa450493  IRenderingControl::GetVolumeDBRange : virtual DWORD GetVolumeDBRange( LPCWSTR pszChannel, short* pMinValue, short* pMaxValue) = 0;
 *   aa450497  IRenderingControl::InvokeVendorAction : virtual DWORD InvokeVendorAction( LPCWSTR pszActionName, DISPPARAMS* pdispparams, VARIANT* pvarResult) = 0;
 *   aa450499  IRenderingControl::ListPresets : virtual DWORD ListPresets( wstring* pstrPresetNameList) = 0;
 *   aa450502  IRenderingControl::SelectPreset : virtual DWORD SelectPreset( LPCWSTR pszPresetName) = 0;
 *   aa450504  IRenderingControl::SetBlueVideoBlackLevel : virtual DWORD SetBlueVideoBlackLevel( unsigned short BlueVideoBlackLevel) = 0;
 *   aa450506  IRenderingControl::SetBlueVideoGain : virtual DWORD SetBlueVideoGain( unsigned short BlueVideoGain) = 0;
 *   aa450507  IRenderingControl::SetBrightness : virtual DWORD SetBrightness( unsigned short Brightness) = 0;
 *   aa450509  IRenderingControl::SetColorTemperature : virtual DWORD SetColorTemperature( unsigned short ColorTemperature) = 0;
 *   aa450511  IRenderingControl::SetContrast : virtual DWORD SetContrast( unsigned short Contrast) = 0;
 *   aa450513  IRenderingControl::SetGreenVideoBlackLevel : virtual DWORD SetGreenVideoBlackLevel( unsigned short GreenVideoBlackLevel) = 0;
 *   aa450515  IRenderingControl::SetGreenVideoGain : virtual DWORD SetGreenVideoGain( unsigned short GreenVideoGain) = 0;
 *   aa450517  IRenderingControl::SetHorizontalKeystone : virtual DWORD SetHorizontalKeystone( short HorizontalKeystone) = 0;
 *   aa450519  IRenderingControl::SetLoudness : virtual DWORD SetLoudness( LPCWSTR pszChannel, bool Loudness) = 0;
 *   aa450521  IRenderingControl::SetMute : virtual DWORD SetMute( LPCWSTR pszChannel, bool Mute) = 0;
 *   aa450523  IRenderingControl::SetRedVideoBlackLevel : virtual DWORD SetRedVideoBlackLevel( unsigned short RedVideoBlackLevel) = 0;
 *   aa450525  IRenderingControl::SetRedVideoGain : virtual DWORD SetRedVideoGain( unsigned short RedVideoGain) = 0;
 *   aa450526  IRenderingControl::SetSharpness : virtual DWORD SetSharpness( unsigned short Sharpness) = 0;
 *   aa450528  IRenderingControl::SetVerticalKeystone : virtual DWORD SetVerticalKeystone( short VerticalKeystone) = 0;
 *   aa450530  IRenderingControl::SetVolume : virtual DWORD SetVolume( LPCWSTR pszChannel, unsigned short Volume) = 0;
 *   aa450532  IRenderingControl::SetVolumeDB : virtual DWORD SetVolumeDB( LPCWSTR pszChannel, short VolumeDB) = 0;
 */

/* --- IRenderingControlImpl (1 page) ---
 *   aa450495  IRenderingControlImpl : (no print)
 */

/* --- RenderingControlState (1 page) ---
 *   aa450873  RenderingControlState : (no print)
 */

/* --- SeekMode (1 page) ---
 *   aa450881  SeekMode : (no print)
 */

/* --- TransportAction (1 page) ---
 *   aa450976  TransportAction : (no print)
 */

/* --- TransportActions (1 page) ---
 *   aa450978  TransportActions : (no print)
 */

/* --- TransportInfo (1 page) ---
 *   aa451002  TransportInfo : (no print)
 */

/* --- TransportSettings (1 page) ---
 *   aa451004  TransportSettings : (no print)
 */

/* --- TransportState (1 page) ---
 *   aa451006  TransportState : (no print)
 */

/* --- ConnectionInfo (1 page) ---
 *   ms887911  ConnectionInfo : (no print)
 */

/* --- ConnectionManagerState (1 page) ---
 *   ms887912  ConnectionManagerState : (no print)
 */

/* --- ContentDirectoryState (1 page) ---
 *   ms887914  ContentDirectoryState : (no print)
 */

/* --- IAVTransport (19 pages) ---
 *   ms890334  IAVTransport : (no print)
 *   ms890335  IAVTransport::GetCurrentTransportActions : virtual DWORD GetCurrentTransportActions( TransportActions* pActions) = 0;
 *   ms890336  IAVTransport::GetDeviceCapabilities : virtual DWORD GetDeviceCapabilities( DeviceCapabilities* pDeviceCapabilities) = 0;
 *   ms890337  IAVTransport::GetMediaInfo : virtual DWORD GetMediaInfo( MediaInfo* pMediaInfo) = 0;
 *   ms890338  IAVTransport::GetPositionInfo : virtual DWORD GetPositionInfo( PositionInfo* pPositionInfo) = 0;
 *   ms890339  IAVTransport::GetTransportInfo : virtual DWORD GetTransportInfo( TransportInfo* pTransportInfo) = 0;
 *   ms890340  IAVTransport::GetTransportSettings : Send Feedback This method returns information about the current transport settings associated with this AVTransport instance, including play mode (normal, shuff
 *   ms890342  IAVTransport::InvokeVendorAction : virtual DWORD InvokeVendorAction( LPCWSTR pszActionName, DISPPARAMS* pdispparams, VARIANT* pvarResult) = 0;
 *   ms890343  IAVTransport::Next : virtual DWORD Next() = 0;
 *   ms890344  IAVTransport::Pause : virtual DWORD Pause() = 0;
 *   ms890345  IAVTransport::Play : virtual DWORD Play( LPCWSTR pszSpeed) = 0;
 *   ms890346  IAVTransport::Previous : virtual DWORD Previous() = 0;
 *   ms890347  IAVTransport::Record : virtual DWORD Record() = 0;
 *   ms890348  IAVTransport::Seek : virtual DWORD Seek( LPCWSTR pszUnit, LPCWSTR pszTarget) = 0;
 *   ms890349  IAVTransport::SetAVTransportURI : virtual DWORD SetAVTransportURI( LPCWSTR pszCurrentURI, LPCWSTR pszCurrentURIMetaData) = 0;
 *   ms890350  IAVTransport::SetNextAVTransportURI : virtual DWORD SetNextAVTransportURI( LPCWSTR pszNextURI, LPCWSTR pszNextURIMetaData) = 0;
 *   ms890351  IAVTransport::SetPlayMode : virtual DWORD SetPlayMode( LPCWSTR pszNewPlayMode) = 0;
 *   ms890353  IAVTransport::SetRecordQualityMode : virtual DWORD SetRecordQualityMode( LPCWSTR pszNewRecordQualityMode) = 0;
 *   ms890354  IAVTransport::Stop : virtual DWORD Stop() = 0;
 */

/* --- IAVTransportImpl (1 page) ---
 *   ms890341  IAVTransportImpl : (no print)
 */

/* --- IConnectionManager (8 pages) ---
 *   ms890364  IConnectionManager : (no print)
 *   ms890365  IConnectionManager::ConnectionComplete : virtual DWORD ConnectionComplete( long ConnectionID) = 0;
 *   ms890366  IConnectionManager::GetCurrentConnectionInfo : virtual DWORD GetCurrentConnectionInfo( long ConnectionID, ConnectionInfo* pConnectionInfo) = 0;
 *   ms890367  IConnectionManager::GetFirstConnectionID : virtual DWORD GetFirstConnectionID( long* pConnectionID) = 0;
 *   ms890368  IConnectionManager::GetNextConnectionID : virtual DWORD GetNextConnectionID( long* pConnectionID) = 0;
 *   ms890369  IConnectionManager::GetProtocolInfo : virtual DWORD GetProtocolInfo( wstring* pstrSourceProtocolInfo, wstring* pstrSinkProtocolInfo) = 0;
 *   ms890377  IConnectionManager::InvokeVendorAction : virtual DWORD InvokeVendorAction( LPCWSTR pszActionName, DISPPARAMS* pdispparams, VARIANT* pvarResult) = 0;
 *   ms890378  IConnectionManager::PrepareForConnection : virtual DWORD PrepareForConnection( LPCWSTR pszRemoteProtocolInfo, LPCWSTR pszPeerConnectionManager, long PeerConnectionID, DIRECTION Direction, long* pConnecti
 */

/* --- IConnectionManagerImpl (7 pages) ---
 *   ms890370  IConnectionManagerImpl : (no print)
 *   ms890371  IConnectionManagerImpl::AddSinkProtocol : virtual DWORD AddSinkProtocol( LPCWSTR pszProtocolInfo);
 *   ms890372  IConnectionManagerImpl::AddSourceProtocol : virtual DWORD AddSourceProtocol( LPCWSTR pszProtocolInfo);
 *   ms890373  IConnectionManagerImpl::CreateConnection : virtual DWORD CreateConnection( LPCWSTR pszRemoteProtocolInfo, DIRECTION Direction, long ConnectionID, IAVTransport** ppAVTransport, IRenderingControl** ppRende
 *   ms890374  IConnectionManagerImpl::EndConnection : virtual DWORD EndConnection( long ConnectionID) = 0;
 *   ms890375  IConnectionManagerImpl::RemoveSinkProtocol : virtual DWORD RemoveSinkProtocol( LPCWSTR pszProtocolInfo);
 *   ms890376  IConnectionManagerImpl::RemoveSourceProtocol : virtual DWORD RemoveSourceProtocol( LPCWSTR pszProtocolInfo);
 */

/* --- IContentDirectory (17 pages) ---
 *   ms890379  IContentDirectory : (no print)
 *   ms890380  IContentDirectory::BrowseChildren : virtual DWORD BrowseChildren( LPCWSTR pszObjectID, LPCWSTR pszFilter, unsigned long StartingIndex, unsigned long RequestedCount, LPCWSTR pszSortCriteria, wstrin
 *   ms890381  IContentDirectory::BrowseMetadata : virtual DWORD BrowseMetadata( LPCWSTR pszObjectID, LPCWSTR pszFilter, wstring* pstrResult, unsigned long* pUpdateID) = 0;
 *   ms890382  IContentDirectory::CreateObject : virtual DWORD CreateObject( LPCWSTR pszContainerID, LPCWSTR pszElements, wstring* pstrObjectID, wstring* pstrResult) = 0;
 *   ms890383  IContentDirectory::CreateReference : virtual DWORD CreateReference( LPCWSTR pszContainerID, LPCWSTR pszObjectID, wstring* pstrNewID) = 0;
 *   ms890384  IContentDirectory::DeleteResource : virtual DWORD DeleteResource( LPCWSTR pszResourceURI) = 0;
 *   ms890385  IContentDirectory::DestroyObject : virtual DWORD DestroyObject( LPCWSTR pszObjectID) = 0;
 *   ms890386  IContentDirectory::ExportResource : virtual DWORD ExportResource( LPCWSTR pszSourceURI, LPCWSTR pszDestinationURI, unsigned long* pTransferID) = 0;
 *   ms890387  IContentDirectory::GetSearchCapabilities : virtual DWORD GetSearchCapabilities( wstring* pstrSearchCaps) = 0;
 *   ms890388  IContentDirectory::GetSortCapabilities : virtual DWORD GetSortCapabilities( wstring* pstrSortCaps) = 0;
 *   ms890389  IContentDirectory::GetSystemUpdateID : virtual DWORD GetSystemUpdateID( unsigned long* pId) = 0;
 *   ms890390  IContentDirectory::GetTransferProgress : virtual DWORD GetTransferProgress( unsigned long TransferID, wstring* pstrTransferStatus, wstring* pstrTransferLength, wstring* pstrTransferTotal) = 0;
 *   ms890392  IContentDirectory::ImportResource : virtual DWORD ImportResource( LPCWSTR pszSourceURI, LPCWSTR pszDestinationURI, unsigned long* pTransferID) = 0;
 *   ms890393  IContentDirectory::InvokeVendorAction : virtual DWORD InvokeVendorAction( LPCWSTR pszActionName, DISPPARAMS* pdispparams, VARIANT* pvarResult) = 0;
 *   ms890394  IContentDirectory::Search : virtual DWORD Search( LPCWSTR pszContainerID, LPCWSTR pszSearchCriteria, LPCWSTR pszFilter, unsigned long StartingIndex, unsigned long RequestedCount, LPCWSTR p
 *   ms890395  IContentDirectory::StopTransferResource : virtual DWORD StopTransferResource( unsigned long TransferID) = 0;
 *   ms890396  IContentDirectory::UpdateObject : virtual DWORD UpdateObject( LPCWSTR pszObjectID, LPCWSTR pszCurrentTagValue, LPCWSTR pszNewTagValue) = 0;
 */

/* --- IContentDirectoryImpl (1 page) ---
 *   ms890391  IContentDirectoryImpl : (no print)
 */

/* --- IEventSink (2 pages) ---
 *   ms890401  IEventSink : (no print)
 *   ms890402  IEventSink::OnStateChanged : virtual DWORD OnStateChanged( LPCWSTR pszStateVariableName, LPCWSTR pszValue) = 0;
 */

/* --- IEventSource (3 pages) ---
 *   ms890403  IEventSource : (no print)
 *   ms890404  IEventSource::Advise : virtual DWORD Advise( IEventSink *pSubscriber) = 0;
 *   ms890881  IEventSource::Unadvise : virtual DWORD Unadvise( IEventSink *pSubscriber) = 0;
 */

/* --- IVirtualService (2 pages) ---
 *   ms893309  IVirtualService : (no print)
 *   ms893316  IVirtualService::Release : virtual void Release() = 0;
 */

/* --- MediaInfo (1 page) ---
 *   ms894570  MediaInfo : (no print)
 */

/* --- MediaRendererDevice (3 pages) ---
 *   ms894574  MediaRendererDevice : (no print)
 *   ms894576  MediaRendererDevice Constructor : MediaRendererDevice( IUPnPDevice* pDevice);
 *   ms894578  MediaRendererDevice::GetConnectionManager : DWORD GetConnectionManager( IConnectionManager** ppConnectionManager, wstring* pstrConnectionmanager);
 */

/* --- MediaServerDevice (4 pages) ---
 *   ms894581  MediaServerDevice : (no print)
 *   ms894584  MediaServerDevice Constructor : MediaServerDevice( IUPnPDevice* pDevice);
 *   ms894587  MediaServerDevice::GetConnectionManager : DWORD GetConnectionManager( IConnectionManager** ppIConnectionManager, wstring* pstrIConnectionManager);
 *   ms894589  MediaServerDevice::GetContentDirectory : DWORD GetContentDirectory( IContentDirectory** ppContentDirectory);
 */

/* --- Medium (1 page) ---
 *   ms894592  Medium : (no print)
 */

/* --- object (2 pages) ---
 *   ms895804  object (UPnP AV) : (no print)
 *   ms895802  object::GetProperty : bool GetProperty( LPCWSTR pszName, wstring* pValue, unsigned long nIndex = 0);
 */

/* --- parser (4 pages) ---
 *   ms895841  parser (UPnP AV) : (no print)
 *   ms895830  parser::AddNamespaceMapping : bool AddNamespaceMapping( LPCWSTR pszNamespace, LPCWSTR pszPrefix);
 *   ms895834  parser::GetFirstObject : bool GetFirstObject( LPCWSTR pszXml, object* pObj);
 *   ms895840  parser::GetNextObject : bool GetNextObject( object* pObj);
 */

/* --- PlayMode (1 page) ---
 *   ms896263  PlayMode : (no print)
 */

/* --- PositionInfo (1 page) ---
 *   ms896283  PositionInfo : (no print)
 */

/* --- wstring (16 pages) ---
 *   ms898916  wstring::append : bool append( const wstring& _X);
 *   ms898917  wstring::assign : bool assign( const wstring& _X);
 *   ms898918  wstring::capacity : size_type capacity() const;
 *   ms898919  wstring::clear : void clear();
 *   ms898920  wstring::compare : int compare( const wstring& _X) const;
 *   ms898921  wstring::empty : Send Feedback This method tests if the string contains elements (characters). bool empty() const;
 *   ms898922  wstring::length : size_type length() const;
 *   ms898925  wstring::operator const wchar_t* : (no print)
 *   ms898924  wstring::operator!= : (no print)
 *   ms898923  wstring::operator+= : (no print)
 *   ms898927  wstring::operator= : (no print)
 *   ms898926  wstring::operator== : (no print)
 *   ms898928  wstring::reserve : bool reserve( size_type _N);
 *   ms898929  wstring::resize : bool resize( size_type _N);
 *   ms898930  wstring::size : size_type size() const;
 *   ms898931  wstring::wstring : wstring( const wstring& _X);
 */

/* --- BIT_AV_ (1 page) ---
 *   ms898943  BIT_AV_ : (no print)
 */

/* --- UPnPAVError (1 page) ---
 *   ms899567  UPnPAVError : (no print)
 */

/* --- ZONE_AV_ (1 page) ---
 *   ms899589  ZONE_AV_ : (no print)
 */

#endif /* AKARI_AV_UPNP_H */
