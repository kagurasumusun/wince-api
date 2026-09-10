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

/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450391 General String Constants (Header: Av_upnp.h.) */
/* ms890335 IAVTransport::GetCurrentTransportActions (Header: Av_upnp.h.) */
/* ms890336 IAVTransport::GetDeviceCapabilities (Header: Av_upnp.h.) */
/* ms890337 IAVTransport::GetMediaInfo (Header: Av_upnp.h.) */
/* ms890338 IAVTransport::GetPositionInfo (Header: Av_upnp.h.) */
/* ms890339 IAVTransport::GetTransportInfo (Header: Av_upnp.h.) */
/* ms890340 IAVTransport::GetTransportSettings (Header: Av_upnp.h.) */
/* ms890342 IAVTransport::InvokeVendorAction (Header: Av_upnp.h.) */
/* ms890343 IAVTransport::Next (Header: Av_upnp.h.) */
/* ms890344 IAVTransport::Pause (Header: Av_upnp.h.) */
/* ms890345 IAVTransport::Play (Header: Av_upnp.h.) */
/* ms890346 IAVTransport::Previous (Header: Av_upnp.h.) */
/* ms890347 IAVTransport::Record (Header: Av_upnp.h.) */
/* ms890348 IAVTransport::Seek (Header: Av_upnp.h.) */
/* ms890349 IAVTransport::SetAVTransportURI (Header: Av_upnp.h.) */
/* ms890350 IAVTransport::SetNextAVTransportURI (Header: Av_upnp.h.) */
/* ms890351 IAVTransport::SetPlayMode (Header: Av_upnp.h.) */
/* ms890353 IAVTransport::SetRecordQualityMode (Header: Av_upnp.h.) */
/* ms890354 IAVTransport::Stop (Header: Av_upnp.h.) */
/* ms890365 IConnectionManager::ConnectionComplete (Header: Av_upnp.h.) */
/* ms890366 IConnectionManager::GetCurrentConnectionInfo (Header: Av_upnp.h.) */
/* ms890367 IConnectionManager::GetFirstConnectionID (Header: Av_upnp.h.) */
/* ms890368 IConnectionManager::GetNextConnectionID (Header: Av_upnp.h.) */
/* ms890369 IConnectionManager::GetProtocolInfo (Header: Av_upnp.h.) */
/* ms890377 IConnectionManager::InvokeVendorAction (Header: Av_upnp.h.) */
/* ms890378 IConnectionManager::PrepareForConnection (Header: Av_upnp.h.) */
/* ms890371 IConnectionManagerImpl::AddSinkProtocol (Header: Av_upnp.h.) */
/* ms890372 IConnectionManagerImpl::AddSourceProtocol (Header: Av_upnp.h.) */
/* ms890373 IConnectionManagerImpl::CreateConnection (Header: Av_upnp.h.) */
/* ms890374 IConnectionManagerImpl::EndConnection (Header: Av_upnp.h.) */
/* ms890375 IConnectionManagerImpl::RemoveSinkProtocol (Header: Av_upnp.h.) */
/* ms890376 IConnectionManagerImpl::RemoveSourceProtocol (Header: Av_upnp.h.) */
/* ms890380 IContentDirectory::BrowseChildren (Header: Av_upnp.h.) */
/* ms890381 IContentDirectory::BrowseMetadata (Header: Av_upnp.h.) */
/* ms890382 IContentDirectory::CreateObject (Header: Av_upnp.h.) */
/* ms890383 IContentDirectory::CreateReference (Header: Av_upnp.h.) */
/* ms890384 IContentDirectory::DeleteResource (Header: Av_upnp.h.) */
/* ms890385 IContentDirectory::DestroyObject (Header: Av_upnp.h.) */
/* ms890386 IContentDirectory::ExportResource (Header: Av_upnp.h.) */
/* ms890387 IContentDirectory::GetSearchCapabilities (Header: Av_upnp.h.) */
/* ms890388 IContentDirectory::GetSortCapabilities (Header: Av_upnp.h.) */
/* ms890389 IContentDirectory::GetSystemUpdateID (Header: Av_upnp.h.) */
/* ms890390 IContentDirectory::GetTransferProgress (Header: Av_upnp.h.) */
/* ms890392 IContentDirectory::ImportResource (Header: Av_upnp.h.) */
/* ms890393 IContentDirectory::InvokeVendorAction (Header: Av_upnp.h.) */
/* ms890394 IContentDirectory::Search (Header: Av_upnp.h.) */
/* ms890395 IContentDirectory::StopTransferResource (Header: Av_upnp.h.) */
/* ms890396 IContentDirectory::UpdateObject (Header: Av_upnp.h.) */
/* ms890402 IEventSink::OnStateChanged (Header: Av_upnp.h.) */
/* ms890404 IEventSource::Advise (Header: Av_upnp.h.) */
/* ms890881 IEventSource::Unadvise (Header: Av_upnp.h.) */
/* aa450477 IRenderingControl::GetBlueVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450478 IRenderingControl::GetBlueVideoGain (Header: Av_upnp.h.) */
/* aa450479 IRenderingControl::GetBrightness (Header: Av_upnp.h.) */
/* aa450480 IRenderingControl::GetColorTemperature (Header: Av_upnp.h.) */
/* aa450481 IRenderingControl::GetContrast (Header: Av_upnp.h.) */
/* aa450482 IRenderingControl::GetGreenVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450483 IRenderingControl::GetGreenVideoGain (Header: Av_upnp.h.) */
/* aa450484 IRenderingControl::GetHorizontalKeystone (Header: Av_upnp.h.) */
/* aa450485 IRenderingControl::GetLoudness (Header: Av_upnp.h.) */
/* aa450486 IRenderingControl::GetMute (Header: Av_upnp.h.) */
/* aa450487 IRenderingControl::GetRedVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450488 IRenderingControl::GetRedVideoGain (Header: Av_upnp.h.) */
/* aa450489 IRenderingControl::GetSharpness (Header: Av_upnp.h.) */
/* ms890314 IRenderingControl::GetVerticalKeystone (Header: Av_upnp.h.) */
/* aa450490 IRenderingControl::GetVolume (Header: Av_upnp.h.) */
/* aa450492 IRenderingControl::GetVolumeDB (Header: Av_upnp.h.) */
/* aa450493 IRenderingControl::GetVolumeDBRange (Header: Av_upnp.h.) */
/* aa450497 IRenderingControl::InvokeVendorAction (Header: Av_upnp.h.) */
/* aa450499 IRenderingControl::ListPresets (Header: Av_upnp.h.) */
/* aa450502 IRenderingControl::SelectPreset (Header: Av_upnp.h.) */
/* aa450504 IRenderingControl::SetBlueVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450506 IRenderingControl::SetBlueVideoGain (Header: Av_upnp.h.) */
/* aa450507 IRenderingControl::SetBrightness (Header: Av_upnp.h.) */
/* aa450509 IRenderingControl::SetColorTemperature (Header: Av_upnp.h.) */
/* aa450511 IRenderingControl::SetContrast (Header: Av_upnp.h.) */
/* aa450513 IRenderingControl::SetGreenVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450515 IRenderingControl::SetGreenVideoGain (Header: Av_upnp.h.) */
/* aa450517 IRenderingControl::SetHorizontalKeystone (Header: Av_upnp.h.) */
/* aa450519 IRenderingControl::SetLoudness (Header: Av_upnp.h.) */
/* aa450521 IRenderingControl::SetMute (Header: Av_upnp.h.) */
/* aa450523 IRenderingControl::SetRedVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450525 IRenderingControl::SetRedVideoGain (Header: Av_upnp.h.) */
/* aa450526 IRenderingControl::SetSharpness (Header: Av_upnp.h.) */
/* aa450528 IRenderingControl::SetVerticalKeystone (Header: Av_upnp.h.) */
/* aa450530 IRenderingControl::SetVolume (Header: Av_upnp.h.) */
/* aa450532 IRenderingControl::SetVolumeDB (Header: Av_upnp.h.) */
/* ms893316 IVirtualService::Release (Header: Av_upnp.h.) */
/* ms894576 MediaRendererDevice Constructor (Header: Av_upnp.h.) */
/* ms894578 MediaRendererDevice::GetConnectionManager (Header: Av_upnp.h.) */
/* ms894584 MediaServerDevice Constructor (Header: Av_upnp.h.) */
/* ms894587 MediaServerDevice::GetConnectionManager (Header: Av_upnp.h.) */
/* ms894589 MediaServerDevice::GetContentDirectory (Header: Av_upnp.h.) */
/* ms895804 object (UPnP AV) (Header: Av_upnp.h.) */
/* ms895802 object::GetProperty (Header: Av_upnp.h.) */
/* ms895841 parser (UPnP AV) (Header: Av_upnp.h.) */
/* ms895830 parser::AddNamespaceMapping (Header: Av_upnp.h.) */
/* ms895834 parser::GetFirstObject (Header: Av_upnp.h.) */
/* ms895840 parser::GetNextObject (Header: Av_upnp.h.) */
/* ms898916 wstring::append (Header: Av_upnp.h.) */
/* ms898917 wstring::assign (Header: Av_upnp.h.) */
/* ms898918 wstring::capacity (Header: Av_upnp.h.) */
/* ms898919 wstring::clear (Header: Av_upnp.h.) */
/* ms898920 wstring::compare (Header: Av_upnp.h.) */
/* ms898921 wstring::empty (Header: Av_upnp.h.) */
/* ms898922 wstring::length (Header: Av_upnp.h.) */
/* ms898925 wstring::operator const wchar_t* (Header: Av_upnp.h.) */
/* ms898924 wstring::operator!= (Header: Av_upnp.h.) */
/* ms898923 wstring::operator+= (Header: Av_upnp.h.) */
/* ms898927 wstring::operator= (Header: Av_upnp.h.) */
/* ms898926 wstring::operator== (Header: Av_upnp.h.) */
/* ms898928 wstring::reserve (Header: Av_upnp.h.) */
/* ms898929 wstring::resize (Header: Av_upnp.h.) */
/* ms898930 wstring::size (Header: Av_upnp.h.) */
/* ms898931 wstring::wstring (Header: Av_upnp.h.) */
/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms880913 Aborting a Request */
/* ms899601 Accessing Shares on the File Server */
/* ms880915 Accessing the FTP Protocol */
/* ms880918 Activating a Service Programmatically */
/* ms898940 Active Server Pages */
/* ms880919 Active Server Pages Application Development */
/* ms880920 Active Server Pages Migration */
/* ms880921 Active Server Pages Samples */
/* ms880922 Active Server Pages Security */
/* ms880929 Administration */
/* ms882822 Application Installation of MSMQ */
/* ms880935 Application-Specific Filter (COM) */
/* ms880937 ASP Functionality in Windows CE */
/* ms899603 Assigning User-Specific Permissions */
/* ms880941 Asynchronous Searching */
/* ms898942 AV String Constants */
/* ms880953 Backup */
/* ms880955 Base Registry Settings */
/* ms880957 Basic Scripting */
/* ms880978 C++ COM Code Example: Creating a Private Queue */
/* ms880979 C++ COM Code Example: Opening a Queue to Read Messages */
/* ms880980 C++ COM Code Example: Opening a Queue to Send Messages */
/* ms880981 C++ COM Code Example: Purging a Queue Synchronously */
/* ms880982 C++ COM Code Example: Reading Messages Synchronously */
/* ms880983 C++ COM Code Example: Sending a String */
/* ms883105 C++ Namespaces in the UPnP AV Framework */
/* ms880977 Callback Registration */
/* ms880992 Client Support */
/* ms880995 Collection Objects */
/* ms899619 Configuring a Web Server to use SSL */
/* ms881008 Configuring a WebDAV Server */
/* ms899609 Configuring FATFS Cache Parameters for the File Server */
/* ms899614 Configuring Services.exe to Load a Standalone Service */
/* ms899610 Configuring the File Server Registry */
/* ms899615 Configuring the File Server through the Registry */
/* ms881010 Configuring the Print Server through the Registry */
/* ms899616 Configuring the RAS Server */
/* ms881011 Configuring the SNTP Service */
/* ms899617 Configuring the Web Server Registry */
/* ms899618 Configuring User Permissions for the Web Server */
/* ms881352 Connecting to an OBEX Server */
/* ms881358 Connecting to Another Device */
/* ms881375 Connecting to WebDAV */
/* ms881389 Connection Points */
/* ms881613 Control Point Actions */
/* ms881520 Controlling a Running Service */
/* ms881662 Creating a Device Description Document */
/* ms881655 Creating a Private Queue (COM) */
/* ms881656 Creating a Queue (COM) */
/* ms881665 Creating an IUPnPDeviceControl Implementation */
/* ms899624 Creating an OS Design for a File Server Device */
/* ms899621 Creating an OS Design for a Web Server Device */
/* ms881661 Creating and Deleting a Peer Identity */
/* ms881668 Creating Queues */
/* ms881669 Creating Service Description Documents */
/* ms899744 Creating Virtual FTP Directories */
/* ms881672 Custom Service Extensions */
/* ms881676 Debugging MSMQ Installations */
/* ms881682 Deleting a Queue (COM) */
/* ms881690 Developing UPnP AV Framework Control Points */
/* ms881691 Developing UPnP AV Framework Devices */
/* ms881689 Developing UPnP AV Framework Devices and Control Points */
/* ms881692 Device Capability */
/* ms881693 Device Collections Returned by Synchronous Searches */
/* ms881694 Device Control */
/* ms881695 Device Description */
/* ms881698 Device Finder Creation */
/* ms881699 Device Location */
/* ms881712 Disconnecting from an OBEX Server */
/* ms881696 Discovering OBEX Devices */
/* ms881840 Enumerating Clouds */
/* ms881847 Eventing ContainerUpdateIDs */
/* ms881848 Eventing in the UPnP AV Framework */
/* ms898959 File Server */
/* ms881857 File Server Application Development */
/* ms886670 File Server Functions */
/* ms881858 File Server Migration */
/* ms881859 File Server OS Design Development */
/* ms886671 File Server Reference */
/* ms884924 File Server Registry Settings */
/* ms881860 File Server Samples */
/* ms881861 File Server Security */
/* ms881862 Filtering Messages (COM) */
/* ms881867 Folder Browsing Service */
/* ms898962 FTP Server */
/* ms881869 FTP Server Application Development */
/* ms881870 FTP Server Authentication */
/* ms881871 FTP Server Data Types */
/* ms881872 FTP Server Implementation */
/* ms881873 FTP Server Migration */
/* ms881874 FTP Server OS Design Development */
/* ms881875 FTP Server Registry Settings */
/* ms881876 FTP Server Samples */
/* ms881877 FTP Server Security */
/* ms881878 FTP Server User List */
/* ms881879 FTP WinInet Functions */
/* ms881890 Global Server Settings */
/* ms899776 Handling Command Line Parameters */
/* ms881902 Header File Differences */
/* ms881903 Headers to Use with Get Operations */
/* ms881904 Headers to Use with Put Operations */
/* aa450272 How to Configure a File Server */
/* ms900460 How to Configure the Web Server */
/* aa450152 How to Request a Data Object from the OBEX Server */
/* aa450199 How to Send a Data Object to the OBEX Server */
/* ms900321 How to Setup a Server Certificate for a Windows CE Web Server */
/* ms881916 HTTP Functionality */
/* ms881915 HTTP Implementation */
/* ms881917 HTTP Transport */
/* ms886681 Identity Manager Functions */
/* ms886682 Identity Manager Reference */
/* ms886683 Identity Manager Structures */
/* ms881922 Implementing a Hosted Device Using COM */
/* ms881925 Implementing an IDispatch Interface for Each Service */
/* ms881924 Implementing and Calling Custom Actions */
/* ms881928 Implementing Device Classes */
/* ms881926 Implementing the Get Operation */
/* ms881927 Implementing the Put Operation */
/* ms881929 Importing and Exporting a Peer Identity */
/* ms881930 Inbox Service */
/* aa450023 Initial Settings */
/* aa450025 Installable File Systems */
/* aa450027 Installation Options */
/* aa450028 Installing MSMQ Using MSMQADM.EXE */
/* aa450029 Installing MSMQ Using the Registry */
/* aa450030 Installing MSMQ Using Visadm */
/* ms900349 Installing the Certificate on a Windows CE-based Web Server */
/* aa450039 Internet Messaging */
/* aa450048 IOCTLs that are Sent by Applications */
/* aa450049 IOCTLs that are Sent by Services.exe */
/* aa450095 ISAPI Extension Functions */
/* aa450096 ISAPI Extensions */
/* aa450097 ISAPI Extensions, Filters, and Script Mapping */
/* aa450098 ISAPI Filter Functions */
/* aa450099 ISAPI Filters */
/* aa450100 ISAPI Filters and HTTP Headers */
/* aa450101 ISAPI Script Mapping */
/* aa450112 Limitations to Standalone Services */
/* ms882693 Mapping a File Extension to Content-Type */
/* ms882728 Message Class Filter (COM) */
/* ms882745 Message Conversion */
/* ms898982 Message Queuing */
/* ms882779 Message Routing */
/* ms898983 MSMQ Application Development */
/* ms886696 MSMQ COM Objects */
/* ms882757 MSMQ COM Support */
/* ms886697 MSMQ Functions */
/* ms898984 MSMQ Migration */
/* ms882831 MSMQ Modules and Descriptions */
/* ms882768 MSMQ OS Design Development */
/* ms882835 MSMQ Programming Model */
/* ms886698 MSMQ Properties */
/* ms886699 MSMQ Reference */
/* ms882845 MSMQ Registry Settings */
/* ms898985 MSMQ Samples */
/* ms882852 MSMQ Security */
/* ms886700 MSMQ Structures */
/* ms900390 Multiple Web Site Registry Settings */
/* ms899303 OBEX Application Development */
/* ms886703 OBEX Enumerations */
/* ms900556 OBEX Functions */
/* ms886704 OBEX Interfaces */
/* ms899412 OBEX Migration */
/* ms883307 OBEX OS Design Development */
/* ms886705 OBEX Reference */
/* ms883153 OBEX Registry Settings */
/* ms899590 OBEX Samples */
/* ms883154 OBEX Security */
/* ms883155 OBEX Server Architecture */
/* ms883156 OBEX Server Services */
/* ms886706 OBEX Structures */
/* ms883152 OBEXFTP */
/* ms883213 OBEXTool */
/* ms883300 Object Exchange Interfaces */
/* ms899516 Object Exchange Protocol */
/* ms883347 Opening a Queue (COM) */
/* ms883361 Opening a Queue to Read Messages (COM) */
/* ms883374 Opening a Queue to Send Messages (COM) */
/* ms899524 Parental Controls */
/* ms883393 Parental Controls Migration */
/* ms883394 Parental Controls OS Design Development */
/* ms883395 Parental Controls Samples */
/* ms883396 Parental Controls Security */
/* ms883408 Peer Names and Clouds */
/* ms883403 Peer-to-Peer Application Development */
/* ms886708 Peer-to-Peer Common Enumerations */
/* ms886709 Peer-to-Peer Common Functions */
/* ms883404 Peer-to-Peer Common Reference */
/* ms886710 Peer-to-Peer Common Structures */
/* ms899527 Peer-to-Peer Networking */
/* ms883405 Peer-to-Peer OS Design Development */
/* ms899528 Peer-to-Peer Reference */
/* ms883406 Peer-to-Peer Registry Settings */
/* ms886711 Peer-to-Peer Samples */
/* ms883407 Peer-to-Peer Security */
/* ms883409 Per-Line Settings */
/* ms886714 PNRP Enumerations */
/* ms886715 PNRP Functions */
/* ms886716 PNRP NSP Error Codes */
/* ms896277 PNRP Reference */
/* ms886717 PNRP Structures */
/* ms899532 Print Server */
/* ms899533 Print Server Application Development */
/* ms883439 Print Server Migration */
/* ms883440 Print Server OS Design Development */
/* ms883441 Print Server Registry Settings */
/* ms883442 Print Server Samples */
/* ms883443 Print Server Security */
/* ms883445 Processing Directives */
/* ms883446 Programming Considerations when Using Transactions (COM) */
/* ms883448 Programming Requirements */
/* ms896300 PROPID_M_COMPOUND_MESSAGE */
/* ms896301 PROPID_M_COMPOUND_MESSAGE_SIZE */
/* ms896308 PROPID_M_FIRST_IN_XACT */
/* ms896312 PROPID_M_LAST_IN_XACT */
/* ms896318 PROPID_M_SOAP_BODY */
/* ms896319 PROPID_M_SOAP_ENVELOPE */
/* ms896320 PROPID_M_SOAP_ENVELOPE_LEN */
/* ms896321 PROPID_M_SOAP_HEADER */
/* ms896327 PROPID_M_XACTID */
/* ms883454 Purging a Queue Asynchronously (COM) */
/* ms883455 Purging a Queue Synchronously (COM) */
/* ms883456 Purging Messages in a Queue (COM) */
/* ms883464 RAS Server Architecture */
/* ms883465 RAS Server Authentication */
/* ms899535 RAS Server/PPTP Server (Incoming) */
/* ms899536 RAS Server/PPTP Server (Incoming) Application Development */
/* ms886722 RAS Server/PPTP Server (Incoming) Enumerations */
/* aa450225 RAS Server/PPTP Server (Incoming) Functions */
/* ms883466 RAS Server/PPTP Server (Incoming) Migration */
/* ms883467 RAS Server/PPTP Server (Incoming) OS Design Development */
/* aa450226 RAS Server/PPTP Server (Incoming) Reference */
/* ms883468 RAS Server/PPTP Server (Incoming) Registry Settings */
/* ms899592 RAS Server/PPTP Server (Incoming) Samples */
/* ms883469 RAS Server/PPTP Server (Incoming) Security */
/* aa450227 RAS Server/PPTP Server (Incoming) Structures */
/* ms883470 Reading Messages Asynchronously (COM) */
/* ms883471 Reading Messages from a Computer Journal (COM) */
/* ms883472 Reading Messages from a Dead-Letter Queue (COM) */
/* ms883473 Reading Messages from a Queue Journal (COM) */
/* ms883474 Reading Messages in a Queue (COM) */
/* ms883475 Reading Messages Synchronously (COM) */
/* ms883476 Reading Messages Using a Cursor (COM) */
/* aa450128 Receiving Messages from a Queue */
/* aa450130 Receiving Notifications by Using WSANSPIoctl */
/* aa450137 Registering a Hosted Device */
/* aa450142 Registering a Peer Name */
/* aa450138 Registering a Service Programmatically */
/* aa450139 Registering a Super Service Automatically */
/* ms900401 Registering an Advanced Certificate on the Windows CE-based Web Server */
/* aa450143 Registering Device Implementations */
/* aa450158 Request Object Implementation */
/* aa450151 Requesting Acknowledgment Messages (COM) */
/* aa450153 Requesting Journaling (COM) */
/* aa450154 Requesting Report Messages (COM) */
/* aa450155 Requesting Response Messages (COM) */
/* aa450156 Requesting Source Journaling (COM) */
/* aa450157 Requesting Target Journaling (COM) */
/* aa450159 Resolving a Peer Name */
/* aa450161 Response Object Implementation */
/* ms900404 Retrieving an Advanced Certificate */
/* aa450167 Retrieving MSMQQueueInfo.Authenticate */
/* aa450168 Retrieving MSMQQueueInfo.BasePriority */
/* aa450169 Retrieving MSMQQueueInfo.CreateTime */
/* aa450170 Retrieving MSMQQueueInfo.FormatName */
/* aa450171 Retrieving MSMQQueueInfo.IsTransactional */
/* aa450172 Retrieving MSMQQueueInfo.Journal */
/* aa450173 Retrieving MSMQQueueInfo.JournalQuota */
/* aa450174 Retrieving MSMQQueueInfo.Label */
/* aa450175 Retrieving MSMQQueueInfo.ModifyTime */
/* aa450176 Retrieving MSMQQueueInfo.PathName */
/* aa450177 Retrieving MSMQQueueInfo.PrivLevel */
/* aa450178 Retrieving MSMQQueueInfo.QueueGuid */
/* aa450179 Retrieving MSMQQueueInfo.Quota */
/* aa450180 Retrieving MSMQQueueInfo.ServiceTypeGuid */
/* aa450183 Retrieving Queue Properties (COM) */
/* aa450198 Sending a Currency in a Message (COM) */
/* aa450200 Sending a Data Recordset in a Message (COM) */
/* aa450201 Sending a Date in a Message (COM) */
/* aa450202 Sending a File as a Message (COM) */
/* aa450206 Sending a Number in a Message (COM) */
/* aa450207 Sending a Persistent Object (COM) */
/* aa450208 Sending a Single-Message Transaction (COM) */
/* aa450209 Sending a String in a Message (COM) */
/* aa450203 Sending an Array of Bytes in a Message (COM) */
/* aa450210 Sending Messages to a Queue */
/* aa450211 Sending Messages to a Queue (COM) */
/* aa450212 Sending Response Messages (COM) */
/* aa450213 Server and Collection Objects */
/* aa450214 Server Object Implementation */
/* aa450215 Server Objects */
/* aa450216 Server Support */
/* ms899543 ServerSupportFunction (ISAPI Extensions) Request Types */
/* aa450218 Service Objects */
/* aa450223 Services.exe */
/* ms899544 Services.exe Application Development */
/* aa450232 Services.exe Functions */
/* aa450233 Services.exe IOCTLS */
/* ms899545 Services.exe Migration */
/* aa450224 Services.exe OS Design Development */
/* aa450234 Services.exe Reference */
/* ms884674 Services.exe Registry Settings */
/* ms884765 Services.exe Request Handling */
/* ms899546 Services.exe Samples */
/* ms884879 Services.exe Security */
/* aa450235 Services.exe Structures */
/* ms884897 Setting MSMQQueueInfo.Authenticate */
/* ms884898 Setting MSMQQueueInfo.BasePriority */
/* ms884900 Setting MSMQQueueInfo.Journal */
/* ms884901 Setting MSMQQueueInfo.JournalQuota */
/* ms884902 Setting MSMQQueueInfo.Label */
/* ms884903 Setting MSMQQueueInfo.PrivLevel */
/* ms884904 Setting MSMQQueueInfo.Quota */
/* ms884905 Setting MSMQQueueInfo.ServiceTypeGuid */
/* ms884906 Setting Queue Properties (COM) */
/* ms884908 Setting the Target Folder Path on the OBEX Server */
/* ms885793 Setting Virtual Paths */
/* aa451153 Sharing Folders Using the File Server */
/* ms884914 Shutting down a Standalone Service */
/* ms899547 Simple Network Time Protocol (SNTP) */
/* ms884917 Simple Network Time Protocol (SNTP) OS Design Development */
/* ms884925 SNTP Migration */
/* ms884926 SNTP Registry Settings */
/* ms884927 SNTP Samples */
/* ms884928 SNTP Security */
/* ms899593 SNTP Service Configuration Code Sample */
/* ms884929 SOAP Reliable Messaging Protocol */
/* ms884942 SSL Client Authentication */
/* ms884943 SSL Support */
/* ms900411 SSL Support Registry Settings */
/* ms884945 Starting and Stopping the Web Server */
/* ms884948 Stopping a Running Service */
/* ms884949 Summary of Supported MSMQ Functions */
/* ms884953 Super Services */
/* ms884955 Supported FTP Commands */
/* ms885767 Supported UPnP Functionality */
/* ms883003 Supporting Multiple Web Sites */
/* ms884958 Synchronous Searching */
/* ms899559 Telnet Server */
/* ms899560 Telnet Server Application Development */
/* ms884992 Telnet Server Input Options */
/* ms899561 Telnet Server Migration */
/* ms885110 Telnet Server OS Design Development */
/* ms885231 Telnet Server Registry Settings */
/* ms899595 Telnet Server Samples */
/* ms885237 Telnet Server Security */
/* ms885250 Telnet Server User Lists */
/* ms899875 Testing the Web Server */
/* ms885389 Uninstallation */
/* ms899563 Universal Plug and Play (UPnP) */
/* ms885406 Unregistering a Peer Name */
/* ms885414 Unsupported FTP Commands */
/* ms885424 UPnP Addressing */
/* ms899562 UPnP Application Development */
/* ms899564 UPnP AV Classes */
/* ms899565 UPnP AV Constants */
/* aa451139 UPnP AV Control Point Sample */
/* aa451140 UPnP AV Control Point Utility Classes */
/* ms885436 UPnP AV DCP Documentation */
/* ms885445 UPnP AV DCP Overview */
/* ms899566 UPnP AV Enumerations */
/* ms885430 UPnP AV Framework Class Organization */
/* ms885451 UPnP AV Framework Debug Zones */
/* ms885455 UPnP AV Framework Overview */
/* aa451141 UPnP AV Interface and Implementation Classes */
/* ms899568 UPnP AV Reference */
/* aa451142 UPnP AV Renderer Sample */
/* ms899569 UPnP AV Structures */
/* aa450249 UPnP C Device Host Enumerations */
/* aa450250 UPnP C Device Host Functions */
/* aa450251 UPnP C Device Host Reference */
/* aa450252 UPnP C Device Host Structures */
/* ms899570 UPnP Concepts */
/* ms885467 UPnP Control */
/* ms886649 UPnP Control Point API Interfaces */
/* ms886650 UPnP Control Point API Reference */
/* ms885502 UPnP Device and Control Point Architecture */
/* ms885482 UPnP Device Control Protocols */
/* ms885474 UPnP Device Description */
/* aa450253 UPnP Device Host Interfaces */
/* aa450254 UPnP Device Host Reference */
/* ms885488 UPnP Discovery */
/* ms885495 UPnP Eventing */
/* ms885509 UPnP Generic Control Point and Device Samples */
/* aa451147 UPnP Internet Gateway Device Schema Sample */
/* ms899571 UPnP Migration */
/* ms885398 UPnP OS Design Development */
/* ms899572 UPnP Other Utility Classes */
/* ms885587 UPnP Presentation */
/* ms899573 UPnP Reference */
/* ms885695 UPnP Registry Device Creation */
/* ms885763 UPnP Registry Device Creation Sample */
/* ms885765 UPnP Registry Settings */
/* ms899574 UPnP Samples */
/* ms885766 UPnP Security */
/* ms885770 Use of Streams */
/* ms885772 User Credential Information */
/* ms885780 Using Message Queuing COM Components in eMbedded Visual C++ */
/* ms885782 Using Services.exe from the Command Line */
/* ms885785 Using the COM Components */
/* ms885786 Using the MSMQAdm Utility */
/* ms899859 Using the Remote Configuration Tool to Configure the File Server */
/* ms899575 Using the UPnP AV Framework */
/* ms898948 Using the UPnP Control Point API */
/* ms885787 Using the UPnP Device Host API */
/* ms885788 Using Transactions (COM) */
/* ms885806 Using Web Server Logging */
/* ms900420 Virtual Path Registry Settings */
/* ms899577 Web Proxy */
/* ms885798 Web Proxy Filtering */
/* ms899578 Web Proxy Functions */
/* ms899579 Web Proxy IOCTLs */
/* ms885799 Web Proxy Migration */
/* ms899580 Web Proxy OS Design Development */
/* ms899581 Web Proxy Reference */
/* aa450255 Web Proxy Registry Settings */
/* ms885800 Web Proxy Samples */
/* ms885801 Web Proxy Security */
/* ms899582 Web Proxy Structures */
/* ms899583 Web Server (HTTPD) */
/* ms900424 Web Server (HTTPD) Application Development */
/* ms900426 Web Server (HTTPD) OS Design Development */
/* ms885802 Web Server Access Rights */
/* ms885803 Web Server Authentication */
/* ms885804 Web Server Authentication and Permissions */
/* ms900582 Web Server Enumerations */
/* aa450256 Web Server Functions */
/* ms885805 Web Server Implementation Details */
/* ms900429 Web Server Migration */
/* ms900432 Web Server Overview */
/* ms885807 Web Server Permissions */
/* aa450257 Web Server Reference */
/* ms900438 Web Server Registry Settings */
/* ms885808 Web Server Requirements */
/* ms900598 Web Server Samples */
/* ms885809 Web Server Security */
/* aa450258 Web Server Structures */
/* ms885810 Web Server User Lists */
/* ms885795 WebDAV */
/* ms885796 WebDAV Interoperability Issues */
/* ms885797 WebDAV Security */
/* ms886628 WSALookupServiceBegin Parameter Values for Enumerating Clouds */
/* ms886627 WSALookupServiceBegin Parameter Values for Resolving Peer Names */
/* ms886629 WSALookupServiceNext Parameter Values for Enumerating Clouds */
/* ms886630 WSALookupServiceNext Parameter Values for Resolving Peer Names */
/* ms899588 wstring class (UPnP AV) */
/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450391 General String Constants (Header: Av_upnp.h.) */
/* ms890335 IAVTransport::GetCurrentTransportActions (Header: Av_upnp.h.) */
/* ms890336 IAVTransport::GetDeviceCapabilities (Header: Av_upnp.h.) */
/* ms890337 IAVTransport::GetMediaInfo (Header: Av_upnp.h.) */
/* ms890338 IAVTransport::GetPositionInfo (Header: Av_upnp.h.) */
/* ms890339 IAVTransport::GetTransportInfo (Header: Av_upnp.h.) */
/* ms890340 IAVTransport::GetTransportSettings (Header: Av_upnp.h.) */
/* ms890342 IAVTransport::InvokeVendorAction (Header: Av_upnp.h.) */
/* ms890343 IAVTransport::Next (Header: Av_upnp.h.) */
/* ms890344 IAVTransport::Pause (Header: Av_upnp.h.) */
/* ms890345 IAVTransport::Play (Header: Av_upnp.h.) */
/* ms890346 IAVTransport::Previous (Header: Av_upnp.h.) */
/* ms890347 IAVTransport::Record (Header: Av_upnp.h.) */
/* ms890348 IAVTransport::Seek (Header: Av_upnp.h.) */
/* ms890349 IAVTransport::SetAVTransportURI (Header: Av_upnp.h.) */
/* ms890350 IAVTransport::SetNextAVTransportURI (Header: Av_upnp.h.) */
/* ms890351 IAVTransport::SetPlayMode (Header: Av_upnp.h.) */
/* ms890353 IAVTransport::SetRecordQualityMode (Header: Av_upnp.h.) */
/* ms890354 IAVTransport::Stop (Header: Av_upnp.h.) */
/* ms890365 IConnectionManager::ConnectionComplete (Header: Av_upnp.h.) */
/* ms890366 IConnectionManager::GetCurrentConnectionInfo (Header: Av_upnp.h.) */
/* ms890367 IConnectionManager::GetFirstConnectionID (Header: Av_upnp.h.) */
/* ms890368 IConnectionManager::GetNextConnectionID (Header: Av_upnp.h.) */
/* ms890369 IConnectionManager::GetProtocolInfo (Header: Av_upnp.h.) */
/* ms890377 IConnectionManager::InvokeVendorAction (Header: Av_upnp.h.) */
/* ms890378 IConnectionManager::PrepareForConnection (Header: Av_upnp.h.) */
/* ms890371 IConnectionManagerImpl::AddSinkProtocol (Header: Av_upnp.h.) */
/* ms890372 IConnectionManagerImpl::AddSourceProtocol (Header: Av_upnp.h.) */
/* ms890373 IConnectionManagerImpl::CreateConnection (Header: Av_upnp.h.) */
/* ms890374 IConnectionManagerImpl::EndConnection (Header: Av_upnp.h.) */
/* ms890375 IConnectionManagerImpl::RemoveSinkProtocol (Header: Av_upnp.h.) */
/* ms890376 IConnectionManagerImpl::RemoveSourceProtocol (Header: Av_upnp.h.) */
/* ms890380 IContentDirectory::BrowseChildren (Header: Av_upnp.h.) */
/* ms890381 IContentDirectory::BrowseMetadata (Header: Av_upnp.h.) */
/* ms890382 IContentDirectory::CreateObject (Header: Av_upnp.h.) */
/* ms890383 IContentDirectory::CreateReference (Header: Av_upnp.h.) */
/* ms890384 IContentDirectory::DeleteResource (Header: Av_upnp.h.) */
/* ms890385 IContentDirectory::DestroyObject (Header: Av_upnp.h.) */
/* ms890386 IContentDirectory::ExportResource (Header: Av_upnp.h.) */
/* ms890387 IContentDirectory::GetSearchCapabilities (Header: Av_upnp.h.) */
/* ms890388 IContentDirectory::GetSortCapabilities (Header: Av_upnp.h.) */
/* ms890389 IContentDirectory::GetSystemUpdateID (Header: Av_upnp.h.) */
/* ms890390 IContentDirectory::GetTransferProgress (Header: Av_upnp.h.) */
/* ms890392 IContentDirectory::ImportResource (Header: Av_upnp.h.) */
/* ms890393 IContentDirectory::InvokeVendorAction (Header: Av_upnp.h.) */
/* ms890394 IContentDirectory::Search (Header: Av_upnp.h.) */
/* ms890395 IContentDirectory::StopTransferResource (Header: Av_upnp.h.) */
/* ms890396 IContentDirectory::UpdateObject (Header: Av_upnp.h.) */
/* ms890402 IEventSink::OnStateChanged (Header: Av_upnp.h.) */
/* ms890404 IEventSource::Advise (Header: Av_upnp.h.) */
/* ms890881 IEventSource::Unadvise (Header: Av_upnp.h.) */
/* aa450477 IRenderingControl::GetBlueVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450478 IRenderingControl::GetBlueVideoGain (Header: Av_upnp.h.) */
/* aa450479 IRenderingControl::GetBrightness (Header: Av_upnp.h.) */
/* aa450480 IRenderingControl::GetColorTemperature (Header: Av_upnp.h.) */
/* aa450481 IRenderingControl::GetContrast (Header: Av_upnp.h.) */
/* aa450482 IRenderingControl::GetGreenVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450483 IRenderingControl::GetGreenVideoGain (Header: Av_upnp.h.) */
/* aa450484 IRenderingControl::GetHorizontalKeystone (Header: Av_upnp.h.) */
/* aa450485 IRenderingControl::GetLoudness (Header: Av_upnp.h.) */
/* aa450486 IRenderingControl::GetMute (Header: Av_upnp.h.) */
/* aa450487 IRenderingControl::GetRedVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450488 IRenderingControl::GetRedVideoGain (Header: Av_upnp.h.) */
/* aa450489 IRenderingControl::GetSharpness (Header: Av_upnp.h.) */
/* ms890314 IRenderingControl::GetVerticalKeystone (Header: Av_upnp.h.) */
/* aa450490 IRenderingControl::GetVolume (Header: Av_upnp.h.) */
/* aa450492 IRenderingControl::GetVolumeDB (Header: Av_upnp.h.) */
/* aa450493 IRenderingControl::GetVolumeDBRange (Header: Av_upnp.h.) */
/* aa450497 IRenderingControl::InvokeVendorAction (Header: Av_upnp.h.) */
/* aa450499 IRenderingControl::ListPresets (Header: Av_upnp.h.) */
/* aa450502 IRenderingControl::SelectPreset (Header: Av_upnp.h.) */
/* aa450504 IRenderingControl::SetBlueVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450506 IRenderingControl::SetBlueVideoGain (Header: Av_upnp.h.) */
/* aa450507 IRenderingControl::SetBrightness (Header: Av_upnp.h.) */
/* aa450509 IRenderingControl::SetColorTemperature (Header: Av_upnp.h.) */
/* aa450511 IRenderingControl::SetContrast (Header: Av_upnp.h.) */
/* aa450513 IRenderingControl::SetGreenVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450515 IRenderingControl::SetGreenVideoGain (Header: Av_upnp.h.) */
/* aa450517 IRenderingControl::SetHorizontalKeystone (Header: Av_upnp.h.) */
/* aa450519 IRenderingControl::SetLoudness (Header: Av_upnp.h.) */
/* aa450521 IRenderingControl::SetMute (Header: Av_upnp.h.) */
/* aa450523 IRenderingControl::SetRedVideoBlackLevel (Header: Av_upnp.h.) */
/* aa450525 IRenderingControl::SetRedVideoGain (Header: Av_upnp.h.) */
/* aa450526 IRenderingControl::SetSharpness (Header: Av_upnp.h.) */
/* aa450528 IRenderingControl::SetVerticalKeystone (Header: Av_upnp.h.) */
/* aa450530 IRenderingControl::SetVolume (Header: Av_upnp.h.) */
/* aa450532 IRenderingControl::SetVolumeDB (Header: Av_upnp.h.) */
/* ms893316 IVirtualService::Release (Header: Av_upnp.h.) */
/* ms894576 MediaRendererDevice Constructor (Header: Av_upnp.h.) */
/* ms894578 MediaRendererDevice::GetConnectionManager (Header: Av_upnp.h.) */
/* ms894584 MediaServerDevice Constructor (Header: Av_upnp.h.) */
/* ms894587 MediaServerDevice::GetConnectionManager (Header: Av_upnp.h.) */
/* ms894589 MediaServerDevice::GetContentDirectory (Header: Av_upnp.h.) */
/* ms895804 object (UPnP AV) (Header: Av_upnp.h.) */
/* ms895802 object::GetProperty (Header: Av_upnp.h.) */
/* ms895841 parser (UPnP AV) (Header: Av_upnp.h.) */
/* ms895830 parser::AddNamespaceMapping (Header: Av_upnp.h.) */
/* ms895834 parser::GetFirstObject (Header: Av_upnp.h.) */
/* ms895840 parser::GetNextObject (Header: Av_upnp.h.) */
/* ms898916 wstring::append (Header: Av_upnp.h.) */
/* ms898917 wstring::assign (Header: Av_upnp.h.) */
/* ms898918 wstring::capacity (Header: Av_upnp.h.) */
/* ms898919 wstring::clear (Header: Av_upnp.h.) */
/* ms898920 wstring::compare (Header: Av_upnp.h.) */
/* ms898921 wstring::empty (Header: Av_upnp.h.) */
/* ms898922 wstring::length (Header: Av_upnp.h.) */
/* ms898925 wstring::operator const wchar_t* (Header: Av_upnp.h.) */
/* ms898924 wstring::operator!= (Header: Av_upnp.h.) */
/* ms898923 wstring::operator+= (Header: Av_upnp.h.) */
/* ms898927 wstring::operator= (Header: Av_upnp.h.) */
/* ms898926 wstring::operator== (Header: Av_upnp.h.) */
/* ms898928 wstring::reserve (Header: Av_upnp.h.) */
/* ms898929 wstring::resize (Header: Av_upnp.h.) */
/* ms898930 wstring::size (Header: Av_upnp.h.) */
/* ms898931 wstring::wstring (Header: Av_upnp.h.) */
/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms880913 Aborting a Request */
/* ms899601 Accessing Shares on the File Server */
/* ms880915 Accessing the FTP Protocol */
/* ms880918 Activating a Service Programmatically */
/* ms898940 Active Server Pages */
/* ms880919 Active Server Pages Application Development */
/* ms880920 Active Server Pages Migration */
/* ms880921 Active Server Pages Samples */
/* ms880922 Active Server Pages Security */
/* ms880929 Administration */
/* ms882822 Application Installation of MSMQ */
/* ms880935 Application-Specific Filter (COM) */
/* ms880937 ASP Functionality in Windows CE */
/* ms899603 Assigning User-Specific Permissions */
/* ms880941 Asynchronous Searching */
/* ms898942 AV String Constants */
/* ms880953 Backup */
/* ms880955 Base Registry Settings */
/* ms880957 Basic Scripting */
/* ms880978 C++ COM Code Example: Creating a Private Queue */
/* ms880979 C++ COM Code Example: Opening a Queue to Read Messages */
/* ms880980 C++ COM Code Example: Opening a Queue to Send Messages */
/* ms880981 C++ COM Code Example: Purging a Queue Synchronously */
/* ms880982 C++ COM Code Example: Reading Messages Synchronously */
/* ms880983 C++ COM Code Example: Sending a String */
/* ms883105 C++ Namespaces in the UPnP AV Framework */
/* ms880977 Callback Registration */
/* ms880992 Client Support */
/* ms880995 Collection Objects */
/* ms899619 Configuring a Web Server to use SSL */
/* ms881008 Configuring a WebDAV Server */
/* ms899609 Configuring FATFS Cache Parameters for the File Server */
/* ms899614 Configuring Services.exe to Load a Standalone Service */
/* ms899610 Configuring the File Server Registry */
/* ms899615 Configuring the File Server through the Registry */
/* ms881010 Configuring the Print Server through the Registry */
/* ms899616 Configuring the RAS Server */
/* ms881011 Configuring the SNTP Service */
/* ms899617 Configuring the Web Server Registry */
/* ms899618 Configuring User Permissions for the Web Server */
/* ms881352 Connecting to an OBEX Server */
/* ms881358 Connecting to Another Device */
/* ms881375 Connecting to WebDAV */
/* ms881389 Connection Points */
/* ms881613 Control Point Actions */
/* ms881520 Controlling a Running Service */
/* ms881662 Creating a Device Description Document */
/* ms881655 Creating a Private Queue (COM) */
/* ms881656 Creating a Queue (COM) */
/* ms881665 Creating an IUPnPDeviceControl Implementation */
/* ms899624 Creating an OS Design for a File Server Device */
/* ms899621 Creating an OS Design for a Web Server Device */
/* ms881661 Creating and Deleting a Peer Identity */
/* ms881668 Creating Queues */
/* ms881669 Creating Service Description Documents */
/* ms899744 Creating Virtual FTP Directories */
/* ms881672 Custom Service Extensions */
/* ms881676 Debugging MSMQ Installations */
/* ms881682 Deleting a Queue (COM) */
/* ms881690 Developing UPnP AV Framework Control Points */
/* ms881691 Developing UPnP AV Framework Devices */
/* ms881689 Developing UPnP AV Framework Devices and Control Points */
/* ms881692 Device Capability */
/* ms881693 Device Collections Returned by Synchronous Searches */
/* ms881694 Device Control */
/* ms881695 Device Description */
/* ms881698 Device Finder Creation */
/* ms881699 Device Location */
/* ms881712 Disconnecting from an OBEX Server */
/* ms881696 Discovering OBEX Devices */
/* ms881840 Enumerating Clouds */
/* ms881847 Eventing ContainerUpdateIDs */
/* ms881848 Eventing in the UPnP AV Framework */
/* ms898959 File Server */
/* ms881857 File Server Application Development */
/* ms886670 File Server Functions */
/* ms881858 File Server Migration */
/* ms881859 File Server OS Design Development */
/* ms886671 File Server Reference */
/* ms884924 File Server Registry Settings */
/* ms881860 File Server Samples */
/* ms881861 File Server Security */
/* ms881862 Filtering Messages (COM) */
/* ms881867 Folder Browsing Service */
/* ms898962 FTP Server */
/* ms881869 FTP Server Application Development */
/* ms881870 FTP Server Authentication */
/* ms881871 FTP Server Data Types */
/* ms881872 FTP Server Implementation */
/* ms881873 FTP Server Migration */
/* ms881874 FTP Server OS Design Development */
/* ms881875 FTP Server Registry Settings */
/* ms881876 FTP Server Samples */
/* ms881877 FTP Server Security */
/* ms881878 FTP Server User List */
/* ms881879 FTP WinInet Functions */
/* ms881890 Global Server Settings */
/* ms899776 Handling Command Line Parameters */
/* ms881902 Header File Differences */
/* ms881903 Headers to Use with Get Operations */
/* ms881904 Headers to Use with Put Operations */
/* aa450272 How to Configure a File Server */
/* ms900460 How to Configure the Web Server */
/* aa450152 How to Request a Data Object from the OBEX Server */
/* aa450199 How to Send a Data Object to the OBEX Server */
/* ms900321 How to Setup a Server Certificate for a Windows CE Web Server */
/* ms881916 HTTP Functionality */
/* ms881915 HTTP Implementation */
/* ms881917 HTTP Transport */
/* ms886681 Identity Manager Functions */
/* ms886682 Identity Manager Reference */
/* ms886683 Identity Manager Structures */
/* ms881922 Implementing a Hosted Device Using COM */
/* ms881925 Implementing an IDispatch Interface for Each Service */
/* ms881924 Implementing and Calling Custom Actions */
/* ms881928 Implementing Device Classes */
/* ms881926 Implementing the Get Operation */
/* ms881927 Implementing the Put Operation */
/* ms881929 Importing and Exporting a Peer Identity */
/* ms881930 Inbox Service */
/* aa450023 Initial Settings */
/* aa450025 Installable File Systems */
/* aa450027 Installation Options */
/* aa450028 Installing MSMQ Using MSMQADM.EXE */
/* aa450029 Installing MSMQ Using the Registry */
/* aa450030 Installing MSMQ Using Visadm */
/* ms900349 Installing the Certificate on a Windows CE-based Web Server */
/* aa450039 Internet Messaging */
/* aa450048 IOCTLs that are Sent by Applications */
/* aa450049 IOCTLs that are Sent by Services.exe */
/* aa450095 ISAPI Extension Functions */
/* aa450096 ISAPI Extensions */
/* aa450097 ISAPI Extensions, Filters, and Script Mapping */
/* aa450098 ISAPI Filter Functions */
/* aa450099 ISAPI Filters */
/* aa450100 ISAPI Filters and HTTP Headers */
/* aa450101 ISAPI Script Mapping */
/* aa450112 Limitations to Standalone Services */
/* ms882693 Mapping a File Extension to Content-Type */
/* ms882728 Message Class Filter (COM) */
/* ms882745 Message Conversion */
/* ms898982 Message Queuing */
/* ms882779 Message Routing */
/* ms898983 MSMQ Application Development */
/* ms886696 MSMQ COM Objects */
/* ms882757 MSMQ COM Support */
/* ms886697 MSMQ Functions */
/* ms898984 MSMQ Migration */
/* ms882831 MSMQ Modules and Descriptions */
/* ms882768 MSMQ OS Design Development */
/* ms882835 MSMQ Programming Model */
/* ms886698 MSMQ Properties */
/* ms886699 MSMQ Reference */
/* ms882845 MSMQ Registry Settings */
/* ms898985 MSMQ Samples */
/* ms882852 MSMQ Security */
/* ms886700 MSMQ Structures */
/* ms900390 Multiple Web Site Registry Settings */
/* ms899303 OBEX Application Development */
/* ms886703 OBEX Enumerations */
/* ms900556 OBEX Functions */
/* ms886704 OBEX Interfaces */
/* ms899412 OBEX Migration */
/* ms883307 OBEX OS Design Development */
/* ms886705 OBEX Reference */
/* ms883153 OBEX Registry Settings */
/* ms899590 OBEX Samples */
/* ms883154 OBEX Security */
/* ms883155 OBEX Server Architecture */
/* ms883156 OBEX Server Services */
/* ms886706 OBEX Structures */
/* ms883152 OBEXFTP */
/* ms883213 OBEXTool */
/* ms883300 Object Exchange Interfaces */
/* ms899516 Object Exchange Protocol */
/* ms883347 Opening a Queue (COM) */
/* ms883361 Opening a Queue to Read Messages (COM) */
/* ms883374 Opening a Queue to Send Messages (COM) */
/* ms899524 Parental Controls */
/* ms883393 Parental Controls Migration */
/* ms883394 Parental Controls OS Design Development */
/* ms883395 Parental Controls Samples */
/* ms883396 Parental Controls Security */
/* ms883408 Peer Names and Clouds */
/* ms883403 Peer-to-Peer Application Development */
/* ms886708 Peer-to-Peer Common Enumerations */
/* ms886709 Peer-to-Peer Common Functions */
/* ms883404 Peer-to-Peer Common Reference */
/* ms886710 Peer-to-Peer Common Structures */
/* ms899527 Peer-to-Peer Networking */
/* ms883405 Peer-to-Peer OS Design Development */
/* ms899528 Peer-to-Peer Reference */
/* ms883406 Peer-to-Peer Registry Settings */
/* ms886711 Peer-to-Peer Samples */
/* ms883407 Peer-to-Peer Security */
/* ms883409 Per-Line Settings */
/* ms886714 PNRP Enumerations */
/* ms886715 PNRP Functions */
/* ms886716 PNRP NSP Error Codes */
/* ms896277 PNRP Reference */
/* ms886717 PNRP Structures */
/* ms899532 Print Server */
/* ms899533 Print Server Application Development */
/* ms883439 Print Server Migration */
/* ms883440 Print Server OS Design Development */
/* ms883441 Print Server Registry Settings */
/* ms883442 Print Server Samples */
/* ms883443 Print Server Security */
/* ms883445 Processing Directives */
/* ms883446 Programming Considerations when Using Transactions (COM) */
/* ms883448 Programming Requirements */
/* ms896300 PROPID_M_COMPOUND_MESSAGE */
/* ms896301 PROPID_M_COMPOUND_MESSAGE_SIZE */
/* ms896308 PROPID_M_FIRST_IN_XACT */
/* ms896312 PROPID_M_LAST_IN_XACT */
/* ms896318 PROPID_M_SOAP_BODY */
/* ms896319 PROPID_M_SOAP_ENVELOPE */
/* ms896320 PROPID_M_SOAP_ENVELOPE_LEN */
/* ms896321 PROPID_M_SOAP_HEADER */
/* ms896327 PROPID_M_XACTID */
/* ms883454 Purging a Queue Asynchronously (COM) */
/* ms883455 Purging a Queue Synchronously (COM) */
/* ms883456 Purging Messages in a Queue (COM) */
/* ms883464 RAS Server Architecture */
/* ms883465 RAS Server Authentication */
/* ms899535 RAS Server/PPTP Server (Incoming) */
/* ms899536 RAS Server/PPTP Server (Incoming) Application Development */
/* ms886722 RAS Server/PPTP Server (Incoming) Enumerations */
/* aa450225 RAS Server/PPTP Server (Incoming) Functions */
/* ms883466 RAS Server/PPTP Server (Incoming) Migration */
/* ms883467 RAS Server/PPTP Server (Incoming) OS Design Development */
/* aa450226 RAS Server/PPTP Server (Incoming) Reference */
/* ms883468 RAS Server/PPTP Server (Incoming) Registry Settings */
/* ms899592 RAS Server/PPTP Server (Incoming) Samples */
/* ms883469 RAS Server/PPTP Server (Incoming) Security */
/* aa450227 RAS Server/PPTP Server (Incoming) Structures */
/* ms883470 Reading Messages Asynchronously (COM) */
/* ms883471 Reading Messages from a Computer Journal (COM) */
/* ms883472 Reading Messages from a Dead-Letter Queue (COM) */
/* ms883473 Reading Messages from a Queue Journal (COM) */
/* ms883474 Reading Messages in a Queue (COM) */
/* ms883475 Reading Messages Synchronously (COM) */
/* ms883476 Reading Messages Using a Cursor (COM) */
/* aa450128 Receiving Messages from a Queue */
/* aa450130 Receiving Notifications by Using WSANSPIoctl */
/* aa450137 Registering a Hosted Device */
/* aa450142 Registering a Peer Name */
/* aa450138 Registering a Service Programmatically */
/* aa450139 Registering a Super Service Automatically */
/* ms900401 Registering an Advanced Certificate on the Windows CE-based Web Server */
/* aa450143 Registering Device Implementations */
/* aa450158 Request Object Implementation */
/* aa450151 Requesting Acknowledgment Messages (COM) */
/* aa450153 Requesting Journaling (COM) */
/* aa450154 Requesting Report Messages (COM) */
/* aa450155 Requesting Response Messages (COM) */
/* aa450156 Requesting Source Journaling (COM) */
/* aa450157 Requesting Target Journaling (COM) */
/* aa450159 Resolving a Peer Name */
/* aa450161 Response Object Implementation */
/* ms900404 Retrieving an Advanced Certificate */
/* aa450167 Retrieving MSMQQueueInfo.Authenticate */
/* aa450168 Retrieving MSMQQueueInfo.BasePriority */
/* aa450169 Retrieving MSMQQueueInfo.CreateTime */
/* aa450170 Retrieving MSMQQueueInfo.FormatName */
/* aa450171 Retrieving MSMQQueueInfo.IsTransactional */
/* aa450172 Retrieving MSMQQueueInfo.Journal */
/* aa450173 Retrieving MSMQQueueInfo.JournalQuota */
/* aa450174 Retrieving MSMQQueueInfo.Label */
/* aa450175 Retrieving MSMQQueueInfo.ModifyTime */
/* aa450176 Retrieving MSMQQueueInfo.PathName */
/* aa450177 Retrieving MSMQQueueInfo.PrivLevel */
/* aa450178 Retrieving MSMQQueueInfo.QueueGuid */
/* aa450179 Retrieving MSMQQueueInfo.Quota */
/* aa450180 Retrieving MSMQQueueInfo.ServiceTypeGuid */
/* aa450183 Retrieving Queue Properties (COM) */
/* aa450198 Sending a Currency in a Message (COM) */
/* aa450200 Sending a Data Recordset in a Message (COM) */
/* aa450201 Sending a Date in a Message (COM) */
/* aa450202 Sending a File as a Message (COM) */
/* aa450206 Sending a Number in a Message (COM) */
/* aa450207 Sending a Persistent Object (COM) */
/* aa450208 Sending a Single-Message Transaction (COM) */
/* aa450209 Sending a String in a Message (COM) */
/* aa450203 Sending an Array of Bytes in a Message (COM) */
/* aa450210 Sending Messages to a Queue */
/* aa450211 Sending Messages to a Queue (COM) */
/* aa450212 Sending Response Messages (COM) */
/* aa450213 Server and Collection Objects */
/* aa450214 Server Object Implementation */
/* aa450215 Server Objects */
/* aa450216 Server Support */
/* ms899543 ServerSupportFunction (ISAPI Extensions) Request Types */
/* aa450218 Service Objects */
/* aa450223 Services.exe */
/* ms899544 Services.exe Application Development */
/* aa450232 Services.exe Functions */
/* aa450233 Services.exe IOCTLS */
/* ms899545 Services.exe Migration */
/* aa450224 Services.exe OS Design Development */
/* aa450234 Services.exe Reference */
/* ms884674 Services.exe Registry Settings */
/* ms884765 Services.exe Request Handling */
/* ms899546 Services.exe Samples */
/* ms884879 Services.exe Security */
/* aa450235 Services.exe Structures */
/* ms884897 Setting MSMQQueueInfo.Authenticate */
/* ms884898 Setting MSMQQueueInfo.BasePriority */
/* ms884900 Setting MSMQQueueInfo.Journal */
/* ms884901 Setting MSMQQueueInfo.JournalQuota */
/* ms884902 Setting MSMQQueueInfo.Label */
/* ms884903 Setting MSMQQueueInfo.PrivLevel */
/* ms884904 Setting MSMQQueueInfo.Quota */
/* ms884905 Setting MSMQQueueInfo.ServiceTypeGuid */
/* ms884906 Setting Queue Properties (COM) */
/* ms884908 Setting the Target Folder Path on the OBEX Server */
/* ms885793 Setting Virtual Paths */
/* aa451153 Sharing Folders Using the File Server */
/* ms884914 Shutting down a Standalone Service */
/* ms899547 Simple Network Time Protocol (SNTP) */
/* ms884917 Simple Network Time Protocol (SNTP) OS Design Development */
/* ms884925 SNTP Migration */
/* ms884926 SNTP Registry Settings */
/* ms884927 SNTP Samples */
/* ms884928 SNTP Security */
/* ms899593 SNTP Service Configuration Code Sample */
/* ms884929 SOAP Reliable Messaging Protocol */
/* ms884942 SSL Client Authentication */
/* ms884943 SSL Support */
/* ms900411 SSL Support Registry Settings */
/* ms884945 Starting and Stopping the Web Server */
/* ms884948 Stopping a Running Service */
/* ms884949 Summary of Supported MSMQ Functions */
/* ms884953 Super Services */
/* ms884955 Supported FTP Commands */
/* ms885767 Supported UPnP Functionality */
/* ms883003 Supporting Multiple Web Sites */
/* ms884958 Synchronous Searching */
/* ms899559 Telnet Server */
/* ms899560 Telnet Server Application Development */
/* ms884992 Telnet Server Input Options */
/* ms899561 Telnet Server Migration */
/* ms885110 Telnet Server OS Design Development */
/* ms885231 Telnet Server Registry Settings */
/* ms899595 Telnet Server Samples */
/* ms885237 Telnet Server Security */
/* ms885250 Telnet Server User Lists */
/* ms899875 Testing the Web Server */
/* ms885389 Uninstallation */
/* ms899563 Universal Plug and Play (UPnP) */
/* ms885406 Unregistering a Peer Name */
/* ms885414 Unsupported FTP Commands */
/* ms885424 UPnP Addressing */
/* ms899562 UPnP Application Development */
/* ms899564 UPnP AV Classes */
/* ms899565 UPnP AV Constants */
/* aa451139 UPnP AV Control Point Sample */
/* aa451140 UPnP AV Control Point Utility Classes */
/* ms885436 UPnP AV DCP Documentation */
/* ms885445 UPnP AV DCP Overview */
/* ms899566 UPnP AV Enumerations */
/* ms885430 UPnP AV Framework Class Organization */
/* ms885451 UPnP AV Framework Debug Zones */
/* ms885455 UPnP AV Framework Overview */
/* aa451141 UPnP AV Interface and Implementation Classes */
/* ms899568 UPnP AV Reference */
/* aa451142 UPnP AV Renderer Sample */
/* ms899569 UPnP AV Structures */
/* aa450249 UPnP C Device Host Enumerations */
/* aa450250 UPnP C Device Host Functions */
/* aa450251 UPnP C Device Host Reference */
/* aa450252 UPnP C Device Host Structures */
/* ms899570 UPnP Concepts */
/* ms885467 UPnP Control */
/* ms886649 UPnP Control Point API Interfaces */
/* ms886650 UPnP Control Point API Reference */
/* ms885502 UPnP Device and Control Point Architecture */
/* ms885482 UPnP Device Control Protocols */
/* ms885474 UPnP Device Description */
/* aa450253 UPnP Device Host Interfaces */
/* aa450254 UPnP Device Host Reference */
/* ms885488 UPnP Discovery */
/* ms885495 UPnP Eventing */
/* ms885509 UPnP Generic Control Point and Device Samples */
/* aa451147 UPnP Internet Gateway Device Schema Sample */
/* ms899571 UPnP Migration */
/* ms885398 UPnP OS Design Development */
/* ms899572 UPnP Other Utility Classes */
/* ms885587 UPnP Presentation */
/* ms899573 UPnP Reference */
/* ms885695 UPnP Registry Device Creation */
/* ms885763 UPnP Registry Device Creation Sample */
/* ms885765 UPnP Registry Settings */
/* ms899574 UPnP Samples */
/* ms885766 UPnP Security */
/* ms885770 Use of Streams */
/* ms885772 User Credential Information */
/* ms885780 Using Message Queuing COM Components in eMbedded Visual C++ */
/* ms885782 Using Services.exe from the Command Line */
/* ms885785 Using the COM Components */
/* ms885786 Using the MSMQAdm Utility */
/* ms899859 Using the Remote Configuration Tool to Configure the File Server */
/* ms899575 Using the UPnP AV Framework */
/* ms898948 Using the UPnP Control Point API */
/* ms885787 Using the UPnP Device Host API */
/* ms885788 Using Transactions (COM) */
/* ms885806 Using Web Server Logging */
/* ms900420 Virtual Path Registry Settings */
/* ms899577 Web Proxy */
/* ms885798 Web Proxy Filtering */
/* ms899578 Web Proxy Functions */
/* ms899579 Web Proxy IOCTLs */
/* ms885799 Web Proxy Migration */
/* ms899580 Web Proxy OS Design Development */
/* ms899581 Web Proxy Reference */
/* aa450255 Web Proxy Registry Settings */
/* ms885800 Web Proxy Samples */
/* ms885801 Web Proxy Security */
/* ms899582 Web Proxy Structures */
/* ms899583 Web Server (HTTPD) */
/* ms900424 Web Server (HTTPD) Application Development */
/* ms900426 Web Server (HTTPD) OS Design Development */
/* ms885802 Web Server Access Rights */
/* ms885803 Web Server Authentication */
/* ms885804 Web Server Authentication and Permissions */
/* ms900582 Web Server Enumerations */
/* aa450256 Web Server Functions */
/* ms885805 Web Server Implementation Details */
/* ms900429 Web Server Migration */
/* ms900432 Web Server Overview */
/* ms885807 Web Server Permissions */
/* aa450257 Web Server Reference */
/* ms900438 Web Server Registry Settings */
/* ms885808 Web Server Requirements */
/* ms900598 Web Server Samples */
/* ms885809 Web Server Security */
/* aa450258 Web Server Structures */
/* ms885810 Web Server User Lists */
/* ms885795 WebDAV */
/* ms885796 WebDAV Interoperability Issues */
/* ms885797 WebDAV Security */
/* ms886628 WSALookupServiceBegin Parameter Values for Enumerating Clouds */
/* ms886627 WSALookupServiceBegin Parameter Values for Resolving Peer Names */
/* ms886629 WSALookupServiceNext Parameter Values for Enumerating Clouds */
/* ms886630 WSALookupServiceNext Parameter Values for Resolving Peer Names */
/* ms899588 wstring class (UPnP AV) */
#endif /* AKARI_AV_UPNP_H */
