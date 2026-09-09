/* Streams.h -- DirectShow base class library (record-only surface).
 *
 * The official "Building DirectShow Filters" page (aa451221,
 * Windows CE 5.0 documentation) instructs: "If you are using the
 * DirectShow base classes, ... Build the base class library.
 * Include the header file Streams.h." and links Strmbase.lib (the
 * source-built static base class library) plus Strmiids.lib
 * (CLSIDs/IIDs) and Ole32.lib/Ole32auth.lib/Uuid.lib (aa451220,
 * "Building DirectShow Applications": all DirectShow applications
 * use Dshow.h; Quartz.lib exports AMGetErrorText).
 *
 * The DirectShow Classes reference (922 pages, manifests/
 * dshow-classes.manifest) documents this surface as C++ classes --
 * a C API layer cannot compile them, so every class and method is
 * recorded verbatim below (page id + printed signature), not
 * declared.  Strmbase.lib is built from source, not an import
 * library, so no def file is generated.  See docs/inventory.md M74.
 */

#include "Dshow.h"

#ifndef AKARI_STREAMS_H
#define AKARI_STREAMS_H

/* --- CAggDirectDraw (ms936855, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class aggregates an IDirectDraw interface
 *   ms936854  CAggDirectDraw::CAggDirectDraw : CAggDirectDraw(TCHAR* pName, LPUNKNOWNpUnk);
 *   ms936856  CAggDirectDraw::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void**ppv);
 *   ms936857  CAggDirectDraw::SetDirectDraw : void SetDirectDraw(LPDIRECTDRAWpDirectDraw);
 */

/* --- CAggDrawSurface (ms936859, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class aggregates an IDirectDrawSurface interface
 *   ms936858  CAggDrawSurface::CAggDrawSurface : CAggDrawSurface(TCHAR* pName,LPUNKNOWNpUnk);
 *   ms936860  CAggDrawSurface::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms936861  CAggDrawSurface::SetDirectDrawSurface : void SetDirectDrawSurface(LPDIRECTDRAWSURFACEpDirectDrawSurface);
 */

/* --- CAMEvent (ms936864, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is an event object that can be set and waited on to provide interthread synchronization
 *   ms936862  CAMEvent::CAMEvent : CAMEvent(BOOLfManualReset=FALSE);
 *   ms936863  CAMEvent::Check : BOOL Check(void);
 *   ms936866  CAMEvent::Reset : void Reset(void);
 *   ms936867  CAMEvent::Set : void Set(void);
 *   ms936868  CAMEvent::Wait : BOOLWait(DWORDdwTimeout);
 *   ms936865  CAMEvent::operator HANDLE : operator HANDLE () const;
 */

/* --- CAMMsgEvent (ms936870, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is a wrapper for event objects that do message processing
 *   ms936871  CAMMsgEvent::WaitMsg : BOOL WaitMsg(DWORDdwTimeOut);
 */

/* --- CAMSchedule (ms936876, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class relieves clocks from the burden of managing the advise requests
 *   ms936872  CAMSchedule::AddAdvisePacket : DWORD AddAdvisePacket(const REFERENCE_TIME &time1,const REFERENCE_TIME &time2,HANDLEhNotify,BOOLbPeriodic);
 *   ms936873  CAMSchedule::Advise : REFERENCE_TIME Advise(const REFERENCE_TIME &rtTime);
 *   ms936875  CAMSchedule::CAMSchedule : CAMSchedule(HANDLEhEvent);
 *   ms936877  CAMSchedule::GetAdviseCount : DWORD GetAdviseCount( );
 *   ms936878  CAMSchedule::GetEvent : HANDLE GetEvent( );
 *   ms936879  CAMSchedule::GetNextAdviseTime : REFERENCE_TIME GetNextAdviseTime( );
 *   ms936880  CAMSchedule::Unadvise : HRESULT Unadvise(DWORDdwAdviseToken);
 */

/* --- CAMThread (ms936884, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract class, a worker thread class that provides creation, synchronization, and communication with a worker thread
 *   ms936882  CAMThread::CAMThread : CAMThread( );
 *   ms936881  CAMThread::CallWorker : DWORD CallWorker(DWORDdw);
 *   ms936883  CAMThread::CheckRequest : BOOL CheckRequest(DWORD* pParam);
 *   ms936885  CAMThread::Close : void Close(void);
 *   ms936886  CAMThread::Create : BOOL Create(void);
 *   ms936887  CAMThread::GetRequest : DWORD GetRequest( );
 *   ms936889  CAMThread::GetRequestHandle : HANDLE GetRequestHandle( ) const;
 *   ms936890  CAMThread::GetRequestParam : DWORD GetRequestParam( ) const;
 *   ms936891  CAMThread::InitialThreadProc : DWORD InitialThreadProc(LPVOIDpv);
 *   ms936892  CAMThread::Reply : void Reply(DWORDdw);
 *   ms936893  CAMThread::ThreadExists : BOOL ThreadExists( );
 *   ms936894  CAMThread::ThreadProc : virtual DWORD ThreadProc( );
 */

/* --- CAutoLock (ms936900, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class holds a critical section for the scope of a block or function
 *   ms936899  CAutoLock::CAutoLock : CAutoLock(CCritSec* plock);
 */

/* --- CBaseAllocator (ms936903, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class that implements the basic mechanisms for an allocator with a fixed number of fixed-size buffers
 *   ms936901  CBaseAllocator::Alloc : HRESULT Alloc(void);
 *   ms936902  CBaseAllocator::CBaseAllocator : CBaseAllocator(TCHAR* pName, LPUNKNOWNlpUnk, HRESULT* phr, BOOLbListSemaphore= TRUE);
 *   ms936904  CBaseAllocator::Commit : HRESULT Commit(void);
 *   ms936905  CBaseAllocator::Decommit : HRESULT Decommit(void);
 *   ms936906  CBaseAllocator::Free : virtual void Free(void) PURE;
 *   ms936907  CBaseAllocator::GetBuffer : HRESULT GetBuffer(IMediaSample** ppBuffer,REFERENCE_TIME* pStartTime,REFERENCE_TIME* pEndTime,DWORDdwFlags);
 *   ms936908  CBaseAllocator::GetProperties : HRESULT GetProperties(ALLOCATOR_PROPERTIES* pProps);
 *   ms936909  CBaseAllocator::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms936910  CBaseAllocator::NotifySample : void NotifySample(void);
 *   ms936911  CBaseAllocator::ReleaseBuffer : HRESULT ReleaseBuffer(IMediaSample* pSample);
 *   ms936912  CBaseAllocator::SetProperties : HRESULT SetProperties(ALLOCATOR_PROPERTIES* pRequest,ALLOCATOR_PROPERTIES* pActual);
 *   ms936913  CBaseAllocator::SetWaiting : void SetWaiting( );
 */

/* --- CBaseBasicVideo (ms936915, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class handles the IDispatch component of the IBasicVideo interface and leaves the properties and methods as a pure virtual function
 *   ms936914  CBaseBasicVideo::CBaseBasicVideo : CBaseBasicVideo(const TCHAR* pName,LPUNKNOWNpUnk);
 *   ms936916  CBaseBasicVideo::GetIDsOfNames : HRESULT GetIDsOfNames(REFIIDriid,OLECHAR** rgszNames,UINTcNames,LCIDlcid,DISPID* rgdispid);
 *   ms936917  CBaseBasicVideo::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo** pptinfo);
 *   ms936918  CBaseBasicVideo::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 *   ms936919  CBaseBasicVideo::Invoke : HRESULTInvoke(DISPIDdispidMember,REFIIDriid,LCIDlcid,WORDwFlags,DISPPARAMS* pdispparams,VARIANT* pvarResult,EXCEPINFO* pexcepinfo,UINT* puArgErr);
 *   ms936920  CBaseBasicVideo::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CBaseControlVideo (ms936924, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements the IBasicVideo dual interface and controls the video properties of a generic video window
 *   ms936921  CBaseControlVideo::CBaseControlVideo : CBaseControlVideo(CBaseFilter* pFilter,CCritSec* pInterfaceLock,TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr);
 *   ms936922  CBaseControlVideo::CheckSourceRect : virtual HRESULT CheckSourceRect(RECT* pSourceRect);
 *   ms936923  CBaseControlVideo::CheckTargetRect : virtual HRESULT CheckTargetRect(RECT* pTargetRect);
 *   ms936941  CBaseControlVideo::CopyImage : HRESULTCopyImage(IMediaSample* pMediaSample,VIDEOINFOHEADER* pVideoInfo,LONG* pBufferSize,BYTE* pVideoImage,RECT* pSourceRect);
 *   ms937074  CBaseControlVideo::GetCurrentImage : HRESULTGetCurrentImage(long* pBufferSize,long* pVideoImage);
 *   ms937099  CBaseControlVideo::GetDestinationPosition : HRESULT GetDestinationPosition(long* pLeft, long* pTop, long* pWidth, long* pHeight);
 *   ms937135  CBaseControlVideo::GetImageSize : HRESULTGetImageSize(VIDEOINFOHEADER* pVideoInfo,long* pBufferSize,RECT* pSourceRect);
 *   ms937140  CBaseControlVideo::GetSourcePosition : HRESULT GetSourcePosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms937141  CBaseControlVideo::GetSourceRect : virtual HRESULT GetSourceRect(RECT* pSourceRect) PURE;
 *   ms937144  CBaseControlVideo::GetStaticImage : virtual HRESULT GetStaticImage(long* pBufferSize, long* pDIBImage) PURE;
 *   ms937145  CBaseControlVideo::GetTargetRect : virtual HRESULT GetTargetRect(RECT* pTargetRect) PURE;
 *   ms937146  CBaseControlVideo::GetVideoFormat : virtual VIDEOINFOHEADER* GetVideoFormat( ) PURE;
 *   ms937148  CBaseControlVideo::GetVideoPaletteEntries : HRESULTGetVideoPaletteEntries(longStartIndex,longEntries,long* pRetrieved,long* pPalette);
 *   ms937149  CBaseControlVideo::GetVideoSize : HRESULT GetVideoSize(long* pWidth, long* pHeight);
 *   ms937151  CBaseControlVideo::IsDefaultSourceRect : virtual HRESULT IsDefaultSourceRect(void) PURE;
 *   ms937152  CBaseControlVideo::IsDefaultTargetRect : virtual HRESULT IsDefaultTargetRect(void) PURE;
 *   ms937153  CBaseControlVideo::IsUsingDefaultDestination : virtual HRESULT IsUsingDefaultDestination(void);
 *   ms937154  CBaseControlVideo::IsUsingDefaultSource : virtual HRESULT IsUsingDefaultSource(void);
 *   ms937155  CBaseControlVideo::OnUpdateRectangles : virtual HRESULT OnUpdateRectangles( );
 *   ms937156  CBaseControlVideo::OnVideoSizeChange : virtual HRESULT OnVideoSizeChange( );
 *   ms937165  CBaseControlVideo::SetControlVideoPin : void SetControlVideoPin(CBasePin* pPin);
 *   ms937166  CBaseControlVideo::SetDefaultDestinationPosition : Send Feedback Sets the renderer back to using the default destination position (typically the entire window client area). HRESULT SetDefaultDestinatio
 *   ms937167  CBaseControlVideo::SetDefaultSourcePosition : Send Feedback Sets the renderer back to using the default source position (typically all the native video). HRESULT SetDefaultSourcePosition( );
 *   ms937168  CBaseControlVideo::SetDefaultSourceRect : virtual HRESULT SetDefaultSourceRect( ) PURE;
 *   ms937169  CBaseControlVideo::SetDefaultTargetRect : virtual HRESULT SetDefaultTargetRect( ) PURE;
 *   ms937170  CBaseControlVideo::SetDestinationPosition : HRESULT SetDestinationPosition(longLeft,longTop,longWidth,longHeight);
 *   ms937171  CBaseControlVideo::SetSourcePosition : HRESULT SetSourcePosition(longLeft,longTop,longWidth,longHeight);
 *   ms937172  CBaseControlVideo::SetSourceRect : virtual HRESULT SetSourceRect(RECT* pSourceRect) PURE;
 *   ms937173  CBaseControlVideo::SetTargetRect : virtual HRESULT SetTargetRect(RECT* pTargetRect) PURE;
 *   ms937046  CBaseControlVideo::get_AvgTimePerFrame : HRESULT get_AvgTimePerFrame(REFTIME* pAvgTimePerFrame);
 *   ms937055  CBaseControlVideo::get_BitErrorRate : HRESULT get_BitErrorRate(long* pBitErrorRate);
 *   ms937063  CBaseControlVideo::get_BitRate : HRESULT get_BitRate(long* pBitRate);
 *   ms937083  CBaseControlVideo::get_DestinationHeight : HRESULT get_DestinationHeight(long* pDestinationHeight);
 *   ms937092  CBaseControlVideo::get_DestinationLeft : HRESULT get_DestinationLeft(long* pDestinationLeft);
 *   ms937110  CBaseControlVideo::get_DestinationTop : HRESULT get_DestinationTop(long* pDestinationTop);
 *   ms937126  CBaseControlVideo::get_DestinationWidth : HRESULT get_DestinationWidth(long* pDestinationWidth);
 *   ms937138  CBaseControlVideo::get_SourceHeight : HRESULT get_SourceHeight(long* pSourceHeight);
 *   ms937139  CBaseControlVideo::get_SourceLeft : HRESULT get_SourceLeft(long* pSourceLeft);
 *   ms937142  CBaseControlVideo::get_SourceTop : HRESULT get_SourceTop(long* pSourceTop);
 *   ms937143  CBaseControlVideo::get_SourceWidth : HRESULT get_SourceWidth(long* pSourceWidth);
 *   ms937147  CBaseControlVideo::get_VideoHeight : HRESULT get_VideoHeight(long* pVideoHeight);
 *   ms937157  CBaseControlVideo::put_DestinationHeight : HRESULT put_DestinationHeight(longDestinationHeight);
 *   ms937158  CBaseControlVideo::put_DestinationLeft : HRESULT put_DestinationLeft(longDestinationLeft);
 *   ms937159  CBaseControlVideo::put_DestinationTop : HRESULT put_DestinationTop(longDestinationTop);
 *   ms937160  CBaseControlVideo::put_DestinationWidth : HRESULT put_DestinationWidth(longDestinationWidth);
 *   ms937161  CBaseControlVideo::put_SourceHeight : HRESULT put_SourceHeight(longSourceHeight);
 *   ms937162  CBaseControlVideo::put_SourceLeft : HRESULT put_SourceLeft(longSourceLeft);
 *   ms937163  CBaseControlVideo::put_SourceTop : HRESULT put_SourceTop(longSourceTop);
 *   ms937164  CBaseControlVideo::put_SourceWidth : HRESULT put_SourceWidth(longSourceWidth);
 */

/* --- CBaseControlWindow (ms937175, Windows CE 3.0 and later.) ---
 * le Send Feedback NOT SUPPORTED IN DXPAK 1.0 This class implements the IVideoWindow interface and controls external access to its associated filter
 *   ms937174  CBaseControlWindow::CBaseControlWindow : CBaseControlWindow(CBaseMediaFilter* pFilter,CCritSec* pInterfaceLock,TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr);
 *   ms937176  CBaseControlWindow::DoGetWindowStyle : HRESULT DoGetWindowStyle(long* pStyle,longWindowLong);
 *   ms937177  CBaseControlWindow::DoSetWindowStyle : HRESULT DoSetWindowStyle(longStyle,longWindowLong);
 *   ms937181  CBaseControlWindow::GetBorderColour : COLORREF GetBorderColour( );
 *   ms937186  CBaseControlWindow::GetMaxIdealImageSize : HRESULT GetMaxIdealImageSize(long* pWidth,long* pHeight);
 *   ms937188  CBaseControlWindow::GetMinIdealImageSize : HRESULT GetMinIdealImageSize(long* pWidth,long* pHeight);
 *   ms937190  CBaseControlWindow::GetOwnerWindow : HWND GetOwnerWindow( );
 *   ms937191  CBaseControlWindow::GetRestorePosition : HRESULT GetRestorePosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms937195  CBaseControlWindow::GetWindowPosition : HRESULT GetWindowPosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms937199  CBaseControlWindow::HideCursor : HRESULT HideCursor(longHideCursor);
 *   ms937200  CBaseControlWindow::IsAutoShowEnabled : BOOL IsAutoShowEnabled( );
 *   ms937201  CBaseControlWindow::IsCursorHidden : HRESULT IsCursorHidden(long* CursorHidden);
 *   ms937202  CBaseControlWindow::NotifyOwnerMessage : HRESULT NotifyOwnerMessage(longhwnd,longuMsg,longwParam,longlParam);
 *   ms937203  CBaseControlWindow::PossiblyEatMessage : BOOL WINAPI PossiblyEatMessage(HWNDhwndDrain,UINTuMsg,WPARAMwParam,LPARAMlParam);
 *   ms937219  CBaseControlWindow::SetControlWindowPin : void SetControlWindowPin(CBasePin* pPin);
 *   ms937220  CBaseControlWindow::SetWindowForeground : HRESULT SetWindowForeground(longFocus);
 *   ms937221  CBaseControlWindow::SetWindowPosition : HRESULT SetWindowPosition(longLeft,longTop,longWidth,longHeight);
 *   ms937178  CBaseControlWindow::get_AutoShow : HRESULT get_AutoShow(long* AutoShow);
 *   ms937179  CBaseControlWindow::get_BackgroundPalette : HRESULT get_BackgroundPalette(long* pBackgroundPalette);
 *   ms937180  CBaseControlWindow::get_BorderColor : HRESULT get_BorderColor(long* Color);
 *   ms937182  CBaseControlWindow::get_Caption : HRESULT get_Caption(BSTR* pstrCaption);
 *   ms937183  CBaseControlWindow::get_FullScreenMode : HRESULT get_FullScreenMode(long* FullScreenMode);
 *   ms937184  CBaseControlWindow::get_Height : HRESULT get_Height(long* pHeight);
 *   ms937185  CBaseControlWindow::get_Left : HRESULT get_Left(long* pLeft);
 *   ms937187  CBaseControlWindow::get_MessageDrain : HRESULT get_MessageDrain(OAHWND* Drain);
 *   ms937189  CBaseControlWindow::get_Owner : HRESULT get_Owner(OAHWND* Owner);
 *   ms937192  CBaseControlWindow::get_Top : HRESULT get_Top(long* pTop);
 *   ms937193  CBaseControlWindow::get_Visible : HRESULT get_Visible(long* pVisible);
 *   ms937194  CBaseControlWindow::get_Width : HRESULT get_Width(long* pWidth);
 *   ms937196  CBaseControlWindow::get_WindowState : HRESULT get_WindowState(long* pWindowState);
 *   ms937197  CBaseControlWindow::get_WindowStyle : HRESULT get_WindowStyle(long* pWindowStyle);
 *   ms937198  CBaseControlWindow::get_WindowStyleEx : HRESULT get_WindowStyleEx(long* pWindowStyleEx);
 *   ms937204  CBaseControlWindow::put_AutoShow : HRESULT put_AutoShow(longAutoShow);
 *   ms937205  CBaseControlWindow::put_BackgroundPalette : HRESULT put_BackgroundPalette(longBackgroundPalette);
 *   ms937206  CBaseControlWindow::put_BorderColor : HRESULT put_BorderColor(longColor);
 *   ms937207  CBaseControlWindow::put_Caption : HRESULT put_Caption(BSTRstrCaption);
 *   ms937208  CBaseControlWindow::put_FullScreenMode : HRESULT put_FullScreenMode(longFullScreenMode);
 *   ms937209  CBaseControlWindow::put_Height : HRESULT put_Height(longHeight);
 *   ms937210  CBaseControlWindow::put_Left : HRESULT put_Left(longLeft);
 *   ms937211  CBaseControlWindow::put_MessageDrain : HRESULT put_MessageDrain(OAHWNDDrain);
 *   ms937212  CBaseControlWindow::put_Owner : HRESULT put_Owner(OAHWNDOwner);
 *   ms937213  CBaseControlWindow::put_Top : HRESULT put_Top(longTop);
 *   ms937214  CBaseControlWindow::put_Visible : HRESULT put_Visible(longVisible);
 *   ms937215  CBaseControlWindow::put_Width : HRESULT put_Width(longWidth);
 *   ms937216  CBaseControlWindow::put_WindowState : HRESULT put_WindowState(longWindowState);
 *   ms937217  CBaseControlWindow::put_WindowStyle : HRESULT put_WindowStyle(longWindowStyle);
 *   ms937218  CBaseControlWindow::put_WindowStyleEx : HRESULT put_WindowStyleEx(long WindowStyleEx);
 */

/* --- CBaseDispatch (ms937224, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is a base class that implements the IDispatch interface for use in a dual interface
 *   ms937223  CBaseDispatch::CBaseDispatch : CBaseDispatch( );
 *   ms937225  CBaseDispatch::GetIDsOfNames : HRESULT GetIDsOfNames(REFIIDriid,OLECHAR** rgszNames,UINTcNames,LCIDlcid,DISPID* rgdispid);
 *   ms937226  CBaseDispatch::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo**pptinfo);
 *   ms937227  CBaseDispatch::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 */

/* --- CBaseFilter (ms937420, Windows CE 3.0 and later.) ---
 * le Send Feedback This is an abstract base class from which all filters are derived
 *   ms937329  CBaseFilter::CBaseFilter : CBaseFilter(TCHAR* pName,LPUNKNOWNpUnk,CCritSec* pLock,REFCLSIDclsid);
 *   ms937528  CBaseFilter::EnumPins : HRESULT EnumPins(IEnumPins** ppEnum);
 *   ms937536  CBaseFilter::FindPin : HRESULT FindPin(LPCWSTRId,IPin** ppPin);
 *   ms937537  CBaseFilter::GetClassID : Send Feedback Fills the pClsID parameter with the class identifier of this filter (from m_clsid ). HRESULT GetClassID(CLSID* pClsID);
 *   ms937538  CBaseFilter::GetFilterGraph : IFilterGraph *GetFilterGraph( );
 *   ms937539  CBaseFilter::GetPin : virtual CBasePin* GetPin(intn) PURE;
 *   ms937540  CBaseFilter::GetPinCount : virtual int GetPinCount( ) PURE;
 *   ms937541  CBaseFilter::GetPinVersion : virtual long GetPinVersion( );
 *   ms937542  CBaseFilter::GetSetupData : virtual LPAMOVIESETUP_FILTER GetSetupData( );
 *   ms937544  CBaseFilter::GetState : HRESULT GetState(DWORDdwMilliSecsTimeout,FILTER_STATE* State);
 *   ms937545  CBaseFilter::GetSyncSource : HRESULT GetSyncSource(IReferenceClock** pClock);
 *   ms937546  CBaseFilter::IncrementPinVersion : void IncrementPinVersion( );
 *   ms937547  CBaseFilter::IsActive : Send Feedback Determines if the filter is currently active (running or paused) or stopped. BOOL IsActive(void);
 *   ms937548  CBaseFilter::JoinFilterGraph : HRESULT JoinFilterGraph(IFilterGraph* pGraph,LPCWSTRpName);
 *   ms937549  CBaseFilter::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms937550  CBaseFilter::NotifyEvent : HRESULTNotifyEvent(longEventCode,longEventParam1,longEventParam2);
 *   ms937551  CBaseFilter::Pause : HRESULT Pause (void);
 *   ms937552  CBaseFilter::QueryFilterInfo : HRESULT QueryFilterInfo(FILTER_INFO* pInfo);
 *   ms937553  CBaseFilter::QueryVendorInfo : HRESULT QueryVendorInfo(LPWSTR* pVendorInfo);
 *   ms937554  CBaseFilter::ReconnectPin : HRESULT ReconnectPin(IPin* pPin,AM_MEDIA_TYPE const* pmt);
 *   ms937556  CBaseFilter::Register : HRESULT Register( );
 *   ms937557  CBaseFilter::Run : HRESULT Run (REFERENCE_TIMEtStart);
 *   ms937558  CBaseFilter::SetSyncSource : HRESULT SetSyncSource (IReferenceClock* pClock);
 *   ms937559  CBaseFilter::Stop : HRESULT Stop(void);
 *   ms937560  CBaseFilter::StreamTime : virtual HRESULT StreamTime(CRefTime&rtStream);
 *   ms937561  CBaseFilter::Unregister : HRESULT Unregister( );
 */

/* --- CBaseInputPin (ms937565, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class derived from CBasePin that adds support for IMemInputPin in addition to the IPin interface support provided by CBasePin 
 *   ms937562  CBaseInputPin::BeginFlush : HRESULT BeginFlush(void);
 *   ms937563  CBaseInputPin::CBaseInputPin : CBaseInputPin::CBaseInputPin(TCHAR* pObjectName,CBaseFilter* pFilter,CCritSec* pLock,HRESULT* phr,LPCWSTRpPinName);
 *   ms937564  CBaseInputPin::CheckStreaming : virtual HRESULT CheckStreaming( );
 *   ms937566  CBaseInputPin::Disconnect : HRESULT Disconnect( );
 *   ms937567  CBaseInputPin::EndFlush : HRESULT EndFlush(void);
 *   ms937568  CBaseInputPin::GetAllocator : HRESULT GetAllocator(IMemAllocator** ppAllocator);
 *   ms937569  CBaseInputPin::GetAllocatorRequirements : HRESULT GetAllocatorRequirements(ALLOCATOR_PROPERTIES* pProps);
 *   ms937570  CBaseInputPin::Inactive : HRESULT Inactive(void);
 *   ms937571  CBaseInputPin::IsFlushing : BOOL IsFlushing(void);
 *   ms937572  CBaseInputPin::IsReadOnly : BOOL IsReadOnly(void);
 *   ms937573  CBaseInputPin::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms937574  CBaseInputPin::Notify : HRESULT Notify(IBaseFilter* pSelf,Qualityq);
 *   ms937575  CBaseInputPin::NotifyAllocator : HRESULT NotifyAllocator(IMemAllocator* pAllocator, BOOLbReadOnly);
 *   ms937576  CBaseInputPin::PassNotify : HRESULT PassNotify(Qualityq);
 *   ms937577  CBaseInputPin::Receive : HRESULT Receive(IMediaSample* pSample);
 *   ms937578  CBaseInputPin::ReceiveCanBlock : HRESULT ReceiveCanBlock(void);
 *   ms937579  CBaseInputPin::ReceiveMultiple : HRESULTReceiveMultiple(IMediaSample** pSamples,longnSamples,long* nSamplesProcessed);
 */

/* --- CBaseList (ms937589, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class represents a list of pointers to objects
 *   ms937580  CBaseList::AddAfter : BOOL AddAfter(POSITIONpos,CBaseList* pList);
 *   ms937582  CBaseList::AddBefore : BOOL AddBefore(POSITIONpos,CBaseList* pList);
 *   ms937584  CBaseList::AddHead : BOOL AddHead(CBaseList* pList);
 *   ms937586  CBaseList::AddTail : BOOL AddTail(CBaseList* pList);
 *   ms937588  CBaseList::CBaseList : CBaseList(TCHAR* pName,INTiItems);
 *   ms937591  CBaseList::GetCountI : Send Feedback Retrieves the number of objects (object count) in the list. int GetCountI( );
 *   ms937592  CBaseList::GetHeadPositionI : POSITION GetHeadPositionI( );
 *   ms937593  CBaseList::GetI : void *GetI(POSITIONpos);
 *   ms937594  CBaseList::GetNextI : void *GetNextI(POSITION&rp);
 *   ms937595  CBaseList::GetTailPositionI : POSITION GetTailPositionI( );
 *   ms937596  CBaseList::MoveToHead : BOOL MoveToHead(POSITIONpos,CBaseList* pList);
 *   ms937597  CBaseList::MoveToTail : BOOL MoveToTail(POSITIONpos,CBaseList* pList);
 *   ms937598  CBaseList::Next : POSITION Next(POSITIONpos);
 *   ms937599  CBaseList::Prev : POSITION Prev(POSITIONpos);
 *   ms937600  CBaseList::RemoveAll : void RemoveAll( );
 *   ms937601  CBaseList::RemoveHeadI : void *RemoveHeadI( );
 *   ms937602  CBaseList::RemoveI : void *RemoveI(POSITIONpos);
 *   ms937603  CBaseList::RemoveTailI : void *RemoveTailI( );
 *   ms937604  CBaseList::Reverse : void Reverse( );
 */

/* --- CBaseMediaFilter (ms937606, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class that provides support for the IMediaFilter interface
 *   ms937605  CBaseMediaFilter::CBaseMediaFilter : CBaseMediaFilter(TCHAR* pName,LPUNKNOWNpUnk,CCritSec* pLock,REFCLSIDclsid);
 *   ms937607  CBaseMediaFilter::GetClassID : Send Feedback Fills the pClsID parameter with the class identifier of this filter (from m_clsid ). HRESULT GetClassID(CLSID* pClsID);
 *   ms937608  CBaseMediaFilter::GetState : HRESULT GetState(DWORDdwMilliSecsTimeout,FILTER_STATE* State);
 *   ms937609  CBaseMediaFilter::GetSyncSource : HRESULT GetSyncSource(IReferenceClock** pClock);
 *   ms937610  CBaseMediaFilter::IsActive : Send Feedback Determines if the filter is active (running or paused) or stopped. BOOL IsActive(void);
 *   ms937611  CBaseMediaFilter::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms937612  CBaseMediaFilter::Pause : HRESULT Pause (void);
 *   ms937613  CBaseMediaFilter::Run : HRESULT Run (REFERENCE_TIMEtStart);
 *   ms937614  CBaseMediaFilter::SetSyncSource : HRESULT SetSyncSource(IReferenceClock* pClock);
 *   ms937615  CBaseMediaFilter::Stop : HRESULT Stop(void);
 *   ms937616  CBaseMediaFilter::StreamTime : virtual HRESULT StreamTime(CRefTime&rtStream);
 */

/* --- CBaseObject (ms937618, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is an abstract base class that is the basis for all component objects
 *   ms937617  CBaseObject::CBaseObject : CBaseObject(const TCHAR* pName);
 *   ms937619  CBaseObject::ObjectsActive : static LONG ObjectsActive( );
 */

/* --- CBaseOutputPin (ms937625, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class derived from the CBasePin class that provides support for the common memory transport
 *   ms937620  CBaseOutputPin::Active : HRESULT Active(void);
 *   ms937621  CBaseOutputPin::BeginFlush : HRESULT BeginFlush(void);
 *   ms937622  CBaseOutputPin::BreakConnect : HRESULT BreakConnect(void);
 *   ms937623  CBaseOutputPin::CBaseOutputPin : CBaseOutputPin(TCHAR* pObjectName,CBaseFilter* pFilter,CCritSec* pLock,HRESULT* phr,LPCWSTRpName);
 *   ms937624  CBaseOutputPin::CheckConnect : HRESULT CheckConnect(IPin* pPin);
 *   ms937626  CBaseOutputPin::CompleteConnect : virtual HRESULT CompleteConnect(IPin* pReceivePin);
 *   ms937627  CBaseOutputPin::DecideAllocator : virtual HRESULT DecideAllocator(IMemInputPin* pPin,IMemAllocator** pAlloc);
 *   ms937628  CBaseOutputPin::DecideBufferSize : virtual HRESULT DecideBufferSize(IMemAllocator* pAlloc,ALLOCATOR_PROPERTIES* ppropInputRequest) PURE;
 *   ms937629  CBaseOutputPin::Deliver : virtual HRESULT Deliver(IMediaSample* pSample);
 *   ms937630  CBaseOutputPin::DeliverBeginFlush : virtual HRESULT DeliverBeginFlush(void);
 *   ms937631  CBaseOutputPin::DeliverEndFlush : virtual HRESULT DeliverEndFlush(void);
 *   ms937632  CBaseOutputPin::DeliverEndOfStream : virtual HRESULT DeliverEndOfStream(void);
 *   ms937633  CBaseOutputPin::DeliverNewSegment : virtual HRESULT DeliverNewSegment(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop,doubledRate);
 *   ms937634  CBaseOutputPin::EndFlush : HRESULT EndFlush(void);
 *   ms937642  CBaseOutputPin::EndOfStream : HRESULT EndOfStream(void);
 *   ms937750  CBaseOutputPin::GetDeliveryBuffer : virtual HRESULT GetDeliveryBuffer(IMediaSample** ppSample,REFERENCE_TIME* pStartTime,REFERENCE_TIME* pEndTime,DWORDdwFlags);
 *   ms937761  CBaseOutputPin::Inactive : HRESULT Inactive(void);
 *   ms937769  CBaseOutputPin::InitAllocator : virtual HRESULT InitAllocator(IMemAllocator** ppAlloc);
 */

/* --- CBasePin (ms938008, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class from which all pins are derived
 *   ms937787  CBasePin::Active : virtual HRESULT Active(void);
 *   ms937793  CBasePin::AgreeMediaType : virtual HRESULT AgreeMediaType(IPin* pReceivePin, const CMediaType* pmt);
 *   ms937800  CBasePin::AttemptConnection : virtual HRESULT AttemptConnection(IPin* pReceivePin,const CMediaType* pmt);
 *   ms937906  CBasePin::BreakConnect : Send Feedback Called when a connection is broken to allow for customization (intended for overriding). virtual HRESULT BreakConnect( );
 *   ms937990  CBasePin::CBasePin : CBasePin(TCHAR* pObjectName,CBaseFilter* pFilter,CCritSec* pLock,HRESULT* phr,LPCWSTRpName,PIN_DIRECTIONdir);
 *   ms937992  CBasePin::CheckConnect : Send Feedback Allows for customization when the connection is first made (intended for overriding, if required). virtual HRESULT CheckConnect(IPin* pP
 *   ms938003  CBasePin::CheckMediaType : virtual HRESULT CheckMediaType(const CMediaType* pmt) PURE;
 *   ms938011  CBasePin::CompleteConnect : virtual HRESULT CompleteConnect(IPin* pReceivePin);
 *   ms938016  CBasePin::Connect : HRESULT Connect(IPin* pReceivePin,const AM_MEDIA_TYPE* pmt);
 *   ms938022  CBasePin::ConnectedTo : HRESULT ConnectedTo(IPin** ppPin);
 *   ms938024  CBasePin::ConnectionMediaType : HRESULT ConnectionMediaType(AM_MEDIA_TYPE* pmt);
 *   ms938030  CBasePin::CurrentRate : double CurrentRate( );
 *   ms938033  CBasePin::CurrentStartTime : REFERENCE_TIME CurrentStartTime( );
 *   ms938039  CBasePin::CurrentStopTime : REFERENCE_TIME CurrentStopTime( );
 *   ms938042  CBasePin::Disconnect : HRESULT Disconnect(void);
 *   ms938046  CBasePin::DisplayPinInfo : void DisplayPinInfo(IPin* pReceivePin);
 *   ms938049  CBasePin::DisplayTypeInfo : void DisplayTypeInfo(IPin* pPin, const CMediaType* pmt);
 *   ms938055  CBasePin::EndOfStream : HRESULT EndOfStream(void);
 *   ms938060  CBasePin::EnumMediaTypes : HRESULT EnumMediaTypes(IEnumMediaTypes** ppEnum);
 *   ms938061  CBasePin::GetConnected : IPin *GetConnected( );
 *   ms938068  CBasePin::GetMediaType : virtual HRESULT GetMediaType(intiPosition,const CMediaType* pMediaType);
 *   ms938072  CBasePin::GetMediaTypeVersion : virtual LONG GetMediaTypeVersion( );
 *   ms938077  CBasePin::Inactive : virtual HRESULT Inactive(void);
 *   ms938083  CBasePin::IncrementTypeVersion : void IncrementTypeVersion(void);
 *   ms938084  CBasePin::IsConnected : BOOL IsConnected(void);
 *   ms938091  CBasePin::IsStopped : BOOL IsStopped( );
 *   ms938108  CBasePin::Name : LPWSTR Name( );
 *   ms938112  CBasePin::NewSegment : HRESULT NewSegment(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop,doubledRate);
 *   ms938118  CBasePin::NonDelegatingAddRef : ULONG NonDelegatingAddRef( );
 *   ms938120  CBasePin::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms938124  CBasePin::NonDelegatingRelease : ULONG NonDelegatingRelease( );
 *   ms938128  CBasePin::Notify : HRESULT Notify(IBaseFilter* pSelf,Qualityq);
 *   ms938132  CBasePin::QueryAccept : HRESULT QueryAccept(const AM_MEDIA_TYPE* pmt);
 *   ms938136  CBasePin::QueryDirection : HRESULT QueryDirection(PIN_DIRECTION* pPinDir);
 *   ms938140  CBasePin::QueryId : HRESULT QueryId(LPWSTR* Id);
 *   ms938145  CBasePin::QueryInternalConnections : HRESULT QueryInternalConnections(IPin** apPin,ULONG* nPin);
 *   ms938148  CBasePin::QueryPinInfo : HRESULT QueryPinInfo(PIN_INFO* pInfo);
 *   ms938154  CBasePin::ReceiveConnection : HRESULT ReceiveConnection(IPin* pConnector,AM_MEDIA_TYPE* pmt);
 *   ms938159  CBasePin::Run : HRESULT Run(REFERENCE_TIMEtStart);
 *   ms938163  CBasePin::SetMediaType : virtual HRESULT SetMediaType(const CMediaType* pmt);
 *   ms938168  CBasePin::SetSink : HRESULT SetSink(IQualityControl* piqc);
 *   ms938173  CBasePin::TryMediaTypes : virtual HRESULT TryMediaTypes(IPin* pReceivePin,const CMediaType* pmt,IEnumMediaTypes* pEnum);
 */

/* --- CBasePropertyPage (ms938193, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is an abstract class for implementing a property page
 *   ms938177  CBasePropertyPage::Activate : HRESULT Activate( HWND hwndParent, LPCRECT prect, BOOL fModal);
 *   ms938184  CBasePropertyPage::Apply : HRESULT Apply(void);
 *   ms938186  CBasePropertyPage::CBasePropertyPage : CBasePropertyPage( TCHAR* pName, LPUNKNOWN pUnk, int DialogId, int TitleId);
 *   ms938194  CBasePropertyPage::Deactivate : HRESULT Deactivate(void);
 *   ms938199  CBasePropertyPage::GetPageInfo : HRESULT GetPageInfo( LPPROPPAGEINFO pPageInfo);
 *   ms938202  CBasePropertyPage::Help : HRESULT Help( LPCWSTR lpszHelpDir);
 *   ms938206  CBasePropertyPage::IsPageDirty : HRESULT IsPageDirty(void);
 *   ms938210  CBasePropertyPage::Move : HRESULT Move( LPCRECT prect);
 *   ms938245  CBasePropertyPage::OnActivate : virtual HRESULT OnActivate(void);
 *   ms938249  CBasePropertyPage::OnApplyChanges : virtual HRESULT OnApplyChanges(void);
 *   ms938255  CBasePropertyPage::OnConnect : virtual HRESULT OnConnect( IUnknown* pUnknown);
 *   ms938258  CBasePropertyPage::OnDeactivate : virtual HRESULT OnDeactivate(void);
 *   ms938263  CBasePropertyPage::OnDisconnect : virtual HRESULT OnDisconnect(void);
 *   ms938268  CBasePropertyPage::OnReceiveMessage : virtual INT_PTR OnReceiveMessage( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
 *   ms938273  CBasePropertyPage::SetObjects : HRESULT SetObjects( ULONG cObjects, LPUNKNOWN* ppUnk);
 *   ms938277  CBasePropertyPage::SetPageSite : HRESULT SetPageSite( IPropertyPageSite* pPageSite);
 *   ms938282  CBasePropertyPage::Show : HRESULT Show( UINT nCmdShow);
 *   ms938287  CBasePropertyPage::TranslateAccelerator : HRESULT TranslateAccelerator( LPMSG lpMsg);
 *   ms938219  CBasePropertyPage::m_DialogId : (no print)
 *   ms938227  CBasePropertyPage::m_Dlg : (no print)
 *   ms938240  CBasePropertyPage::m_TitleId : (no print)
 *   ms938215  CBasePropertyPage::m_bDirty : (no print)
 *   ms938230  CBasePropertyPage::m_hwnd : (no print)
 *   ms938235  CBasePropertyPage::m_pPageSite : (no print)
 *   ms938294  CBasePropertyPage::~CBasePropertyPage : (no print)
 */

/* --- CBaseReferenceClock (ms938312, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This base class implements the IReferenceClock interface
 *   ms938296  CBaseReferenceClock::AdvisePeriodic : HRESULT AdvisePeriodic(REFERENCE_TIMEStartTime,REFERENCE_TIMEPeriodTime,HSEMAPHOREhSemaphore,DWORD* pdwAdviseToken);
 *   ms938301  CBaseReferenceClock::AdviseTime : HRESULT AdviseTime(REFERENCE_TIMEbaseTime,REFERENCE_TIMEstreamTime,HEVENThEvent,DWORD* pdwAdviseToken);
 *   ms938308  CBaseReferenceClock::CBaseReferenceClock : CBaseReferenceClock(TCHAR*pName,LPUNKNOWNpUnk,HRESULT*phr,CAMSchedule*pSched);
 *   ms938318  CBaseReferenceClock::GetPrivateTime : virtual REFERENCE_TIME GetPrivateTime( );
 *   ms938320  CBaseReferenceClock::GetSchedule : CAMSchedule *GetSchedule( );
 *   ms938328  CBaseReferenceClock::GetTime : HRESULT GetTime( REFERENCE_TIME* pTime);
 *   ms938331  CBaseReferenceClock::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void**ppv);
 *   ms938340  CBaseReferenceClock::SetTimeDelta : HRESULT SetTimeDelta(const REFERENCE_TIME&TimeDelta);
 *   ms938342  CBaseReferenceClock::TriggerThread : void TriggerThread( );
 *   ms938348  CBaseReferenceClock::Unadvise : HRESULT Unadvise(DWORDdwAdviseToken);
 */

/* --- CBaseRenderer (ms938389, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is the base renderer class for writing renderers
 *   ms938351  CBaseRenderer::Active : virtual HRESULT Active(void);
 *   ms938357  CBaseRenderer::BeginFlush : virtual HRESULT BeginFlush(void);
 *   ms938365  CBaseRenderer::BreakConnect : virtual HRESULT BreakConnect(void);
 *   ms938374  CBaseRenderer::CBaseRenderer : CBaseRenderer(REFCLSIDRenderClass,TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr);
 *   ms938370  CBaseRenderer::CancelNotification : virtual HRESULT CancelNotification(void);
 *   ms938380  CBaseRenderer::CheckMediaType : virtual HRESULT CheckMediaType(const CMediaType* pmt) PURE;
 *   ms938385  CBaseRenderer::CheckReady : BOOL CheckReady(void);
 *   ms938393  CBaseRenderer::ClearPendingSample : virtual HRESULT ClearPendingSample(void);
 *   ms938398  CBaseRenderer::CompleteConnect : virtual HRESULT CompleteConnect(IPin* pReceivePin);
 *   ms938403  CBaseRenderer::CompleteStateChange : virtual HRESULT CompleteStateChange(FILTER_STATEOldState);
 *   ms938415  CBaseRenderer::DisplayRendererState : void CBaseRenderer::DisplayRendererState( );
 *   ms938423  CBaseRenderer::DoRenderSample : virtual HRESULT DoRenderSample(IMediaSample* pMediaSample) PURE;
 *   ms938431  CBaseRenderer::EndFlush : virtual HRESULT EndFlush(void);
 *   ms906500  CBaseRenderer::EndOfStream : HRESULT EndOfStream(void);
 *   ms906508  CBaseRenderer::FindPin : HRESULT FindPin(LPCWSTRId,IPin** ppPin);
 *   ms926228  CBaseRenderer::GetCurrentSample : virtual IMediaSample *GetCurrentSample(void);
 *   ms926237  CBaseRenderer::GetMediaPositionInterface : virtual HRESULT GetMediaPositionInterface(REFIIDriid,void** ppv);
 *   ms906554  CBaseRenderer::GetPin : virtual CBasePin *GetPin(intn);
 *   ms906561  CBaseRenderer::GetPinCount : virtual int GetPinCount(void);
 *   ms906569  CBaseRenderer::GetRealState : FILTER_STATE GetRealState(void);
 *   ms906577  CBaseRenderer::GetRenderEvent : CAMEvent *GetRenderEvent(void);
 *   ms906581  CBaseRenderer::GetSampleTimes : virtual HRESULT GetSampleTimes(IMediaSample* pMediaSample,REFERENCE_TIME* pStartTime,REFERENCE_TIME* pEndTime);
 *   ms906583  CBaseRenderer::GetState : HRESULT GetState(DWORDdwMilliSecsTimeout,FILTER_STATE* State);
 *   ms906588  CBaseRenderer::HaveCurrentSample : virtual BOOL HaveCurrentSample(void);
 *   ms906593  CBaseRenderer::Inactive : virtual HRESULT Inactive(void);
 *   ms906598  CBaseRenderer::IsEndOfStream : BOOL IsEndOfStream(void);
 *   ms906603  CBaseRenderer::IsEndOfStreamDelivered : BOOL IsEndOfStreamDelivered(void);
 *   ms906609  CBaseRenderer::IsStreaming : BOOL IsStreaming(void);
 *   ms906615  CBaseRenderer::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms906623  CBaseRenderer::NotReady : void NotReady(void);
 *   ms906618  CBaseRenderer::NotifyEndOfStream : void NotifyEndOfStream(void);
 *   ms906625  CBaseRenderer::OnReceiveFirstSample : virtual void OnReceiveFirstSample(IMediaSample* pMediaSample);
 *   ms906628  CBaseRenderer::OnRenderEnd : virtual void OnRenderEnd(IMediaSample* pMediaSample);
 *   ms906632  CBaseRenderer::OnRenderStart : virtual void OnRenderStart(IMediaSample* pMediaSample);
 *   ms906637  CBaseRenderer::OnStartStreaming : virtual HRESULT OnStartStreaming(void);
 *   ms906641  CBaseRenderer::OnStopStreaming : virtual HRESULT OnStopStreaming(void);
 *   ms906644  CBaseRenderer::OnWaitEnd : virtual void OnWaitEnd(void);
 *   ms906647  CBaseRenderer::OnWaitStart : virtual void OnWaitStart(void);
 *   ms906649  CBaseRenderer::Pause : HRESULT Pause(void);
 *   ms906654  CBaseRenderer::PrepareReceive : virtual HRESULT PrepareReceive(IMediaSample* pMediaSample);
 *   ms906658  CBaseRenderer::PrepareRender : virtual void PrepareRender(void);
 *   ms906672  CBaseRenderer::Ready : void Ready(void);
 *   ms906677  CBaseRenderer::Receive : virtual HRESULT Receive(IMediaSample* pMediaSample);
 *   ms906681  CBaseRenderer::Render : virtual HRESULT Render(IMediaSample* pMediaSample);
 *   ms906685  CBaseRenderer::ResetEndOfStream : virtual HRESULT ResetEndOfStream(void);
 *   ms906688  CBaseRenderer::ResetEndOfStreamTimer : void ResetEndOfStreamTimer(void);
 *   ms906692  CBaseRenderer::Run : HRESULT Run(void);
 *   ms906696  CBaseRenderer::ScheduleSample : virtual BOOL ScheduleSample(IMediaSample* pMediaSample);
 *   ms906698  CBaseRenderer::SendEndOfStream : virtual HRESULT SendEndOfStream(void);
 *   ms906701  CBaseRenderer::SendNotifyWindow : void SendNotifyWindow(IPin* pPin,HWNDhwnd);
 *   ms906704  CBaseRenderer::SendRepaint : void SendRepaint(void);
 *   ms906707  CBaseRenderer::SetAbortSignal : void SetAbortSignal(BOOLbAbort);
 *   ms906710  CBaseRenderer::SetMediaType : virtual HRESULT SetMediaType(const CMediaType* pmt);
 *   ms906713  CBaseRenderer::SetRepaintStatus : void SetRepaintStatus(BOOLbRepaint);
 *   ms906717  CBaseRenderer::ShouldDrawSampleNow : virtual HRESULT ShouldDrawSampleNow(IMediaSample* pMediaSample,REFERENCE_TIME* pStartTime,REFERENCE_TIME* pEndTime);
 *   ms906718  CBaseRenderer::SignalTimerFired : virtual void SignalTimerFired(void);
 *   ms906719  CBaseRenderer::SourceThreadCanWait : virtual HRESULT SourceThreadCanWait(BOOLbCanWait);
 *   ms906724  CBaseRenderer::StartStreaming : virtual HRESULT StartStreaming(void);
 *   ms906729  CBaseRenderer::Stop : HRESULT Stop(void);
 *   ms906734  CBaseRenderer::StopStreaming : virtual HRESULT StopStreaming(void);
 *   ms906738  CBaseRenderer::TimerCallback : void TimerCallback(void);
 *   ms906740  CBaseRenderer::WaitForReceiveToComplete : void WaitForReceiveToComplete( );
 *   ms906743  CBaseRenderer::WaitForRenderTime : virtual HRESULT WaitForRenderTime(void);
 */

/* --- CBaseStreamControl (ms906750, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements the IAMStreamControl interface on input and output pins in a filter graph
 *   ms906745  CBaseStreamControl::CBaseStreamControl : CBaseStreamControl( );
 *   ms906748  CBaseStreamControl::CheckStreamState : enum StreamControlState CheckStreamState( IMediaSample* pSample);
 *   ms906752  CBaseStreamControl::Flushing : void Flushing(BOOLbInProgress);
 *   ms906754  CBaseStreamControl::GetInfo : HRESULT GetInfo(AM_STREAM_INFO* pInfo);
 *   ms906758  CBaseStreamControl::NotifyFilterState : void NotifyFilterState(FILTER_STATEnew_state,REFERENCE_TIMEtStart= 0 );
 *   ms906762  CBaseStreamControl::SetFilterGraph : void SetFilterGraph(IMediaEventSink* pSink);
 *   ms906768  CBaseStreamControl::SetSyncSource : void SetSyncSource(IReferenceClock*pRefClock);
 *   ms938455  CBaseStreamControl::StartAt : (no print)
 *   ms938460  CBaseStreamControl::StopAt : HRESULT StopAt(const REFERENCE_TIME* ptStop= NULL,BOOLbSendExtra= FALSE,DWORDdwCookie= 0 );
 */

/* --- CBaseVideoRenderer (ms938474, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This base class is used for building video renderer filters
 *   ms938464  CBaseVideoRenderer::CBaseVideoRenderer : CBaseVideoRenderer(REFCLSIDRenderClass,TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr);
 *   ms938541  CBaseVideoRenderer::GetStdDev : HRESULTGetStdDev(intnSamples,int* piResult,LONGLONGllSumSq,LONGLONGiTot);
 *   ms938551  CBaseVideoRenderer::JoinFilterGraph : HRESULT JoinFilterGraph(IBaseFilterGraph* pGraph, LPCWSTRpName);
 *   ms938561  CBaseVideoRenderer::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,VOID** ppv);
 *   ms938571  CBaseVideoRenderer::Notify : HRESULT Notify(IBaseFilter* pSelf, Qualityq);
 *   ms938581  CBaseVideoRenderer::OnDirectRender : virtual void OnDirectRender(IMediaSample* pMediaSample);
 *   ms938590  CBaseVideoRenderer::OnRenderEnd : void OnRenderEnd(IMediaSample* pMediaSample);
 *   ms938602  CBaseVideoRenderer::OnRenderStart : void OnRenderStart(IMediaSample* pMediaSample);
 *   ms938614  CBaseVideoRenderer::OnStartStreaming : HRESULT OnStartStreaming(void);
 *   ms938623  CBaseVideoRenderer::OnStopStreaming : HRESULT OnStopStreaming(void);
 *   ms938639  CBaseVideoRenderer::OnWaitEnd : void OnWaitEnd(void);
 *   ms938648  CBaseVideoRenderer::OnWaitStart : void OnWaitStart(void);
 *   ms938661  CBaseVideoRenderer::PreparePerformanceData : void PreparePerformanceData(inttrLate,inttrFrame);
 *   ms938675  CBaseVideoRenderer::RecordFrameLateness : virtual void RecordFrameLateness(inttrLate,inttrFrame);
 *   ms938683  CBaseVideoRenderer::ResetStreamingTimes : virtual HRESULT ResetStreamingTimes(void);
 *   ms926248  CBaseVideoRenderer::ScheduleSample : Send Feedback Overrides the base class that does the main work to keep a count of samples drawn and dropped (which are used by the IQualProp implement
 *   ms926258  CBaseVideoRenderer::SendQuality : virtual HRESULT SendQuality(REFERENCE_TIMEtrLate,REFERENCE_TIMEtrRealStream);
 *   ms926270  CBaseVideoRenderer::SetSink : HRESULT SetSink(IQualityControl* piqc);
 *   ms926285  CBaseVideoRenderer::ShouldDrawSampleNow : virtual HRESULT ShouldDrawSampleNow(IMediaSample* pMediaSample,REFERENCE_TIME* ptrStart,REFERENCE_TIME* ptrEnd);
 *   ms926294  CBaseVideoRenderer::ThrottleWait : void ThrottleWait(void);
 *   ms938484  CBaseVideoRenderer::get_AvgFrameRate : HRESULT get_AvgFrameRate(int* piAvgFrameRate);
 *   ms938491  CBaseVideoRenderer::get_AvgSyncOffset : HRESULT get_AvgSyncOffset(int* piAvg);
 *   ms938502  CBaseVideoRenderer::get_DevSyncOffset : HRESULT get_DevSyncOffset(int* piDev);
 *   ms938512  CBaseVideoRenderer::get_FramesDrawn : HRESULT get_FramesDrawn(int* pcFramesDrawn);
 *   ms938521  CBaseVideoRenderer::get_FramesDroppedInRenderer : HRESULT get_FramesDroppedInRenderer(int* pcFramesDropped);
 *   ms938530  CBaseVideoRenderer::get_Jitter : HRESULT get_Jitter(int* piJitter);
 */

/* --- CBaseVideoWindow (ms926318, Windows CE 3.0 and later.) ---
 * le Send Feedback NOT SUPPORTED IN DXPAK 1.0 This class handles the IDispatch component of the IVideoWindow interface and leaves the IVideoWindow properties and methods as
 *   ms926306  CBaseVideoWindow::CBaseVideoWindow : CBaseVideoWindow(const TCHAR* pName,LPUNKNOWNpUnk);
 *   ms926328  CBaseVideoWindow::GetIDsOfNames : HRESULT GetIDsOfNames(REFIIDriid,OLECHAR** rgszNames,UINTcNames,LCIDlcid,DISPID* rgdispid);
 *   ms926337  CBaseVideoWindow::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo** pptinfo);
 *   ms926345  CBaseVideoWindow::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 *   ms926346  CBaseVideoWindow::Invoke : HRESULTInvoke(DISPIDdispidMember,REFIIDriid,LCIDlcid,WORDwFlags,DISPPARAMS* pdispparams,VARIANT* pvarResult,EXCEPINFO* pexcepinfo,UINT* puArgErr);
 *   ms926347  CBaseVideoWindow::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CBaseWindow (ms926350, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class creates a window and a worker thread
 *   ms926348  CBaseWindow::ActivateWindow : virtual HRESULT ActivateWindow( );
 *   ms926349  CBaseWindow::CBaseWindow : CBaseWindow(BOOLbDoGetDC= FALSE);
 *   ms926351  CBaseWindow::DoneWithWindow : virtual HRESULT DoneWithWindow( );
 *   ms926352  CBaseWindow::GetClassWindowStyles : virtualLPTSTRGetClassWindowStyles(DWORD* pClassStyles,DWORD* pWindowStyles,DWORD* pWindowStylesEx)PURE;
 *   ms926353  CBaseWindow::GetWindowHWND : HWND GetWindowHWND( );
 *   ms926354  CBaseWindow::InactivateWindow : Send Feedback Effectively hides the window (if it was visible). virtual HRESULT InactivateWindow( );
 *   ms926355  CBaseWindow::InitialiseWindow : virtual InitialiseWindow(HWNDhwnd);
 *   aa451466  CBaseWindow::OnClose : virtual BOOL OnClose( );
 *   aa451467  CBaseWindow::OnReceiveMessage : virtual LRESULT OnReceiveMessage(HWNDhwnd,INTuMsg,WPARAMwParam,LPARAMlParam);
 *   aa451468  CBaseWindow::PossiblyEatMessage : virtual BOOL PossiblyEatMessage(UINTuMsg,WPARAMwParam,LPARAMlParam);
 *   aa451469  CBaseWindow::PrepareWindow : virtual HRESULT PrepareWindow( );
 *   aa451470  CBaseWindow::UninitialiseWindow : virtual UninitialiseWindow( );
 */

/* --- CBasicAudio (aa451472, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class handles the IDispatch interface component of the IBasicAudio interface and leaves the properties and methods of IBasicAudio pure virtual to be
 *   aa451471  CBasicAudio::CBasicAudio : CBasicAudio(const TCHAR* pName,LPUNKNOWNpUnk);
 *   aa451473  CBasicAudio::GetIDsOfNames : HRESULT GetIDsOfNames(REFIIDriid,OLECHAR** rgszNames,UINTcNames,LCIDlcid,DISPID* rgdispid);
 *   aa451474  CBasicAudio::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo** pptinfo);
 *   aa451475  CBasicAudio::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 *   aa451476  CBasicAudio::Invoke : HRESULTInvoke(DISPIDdispidMember,REFIIDriid,LCIDlcid,WORDwFlags,DISPPARAMS* pdispparams,VARIANT* pvarResult,EXCEPINFO* pexcepinfo,UINT* puArgErr);
 *   aa451477  CBasicAudio::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CCritSec (aa451479, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This object provides intraprocess synchronization
 *   aa451478  CCritSec::CCritSec : CCritSec( );
 *   aa451481  CCritSec::Lock : void Lock( );
 *   aa451482  CCritSec::Unlock : void Unlock( );
 */

/* --- CDisp (aa451486, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides methods for displaying a number of data types for debugging
 *   aa451485  CDisp::CDisp : CDisp(LONGLONGll,intFormat= CDISP_HEX);
 */

/* --- CDispBasic (aa451484, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This internal class is used to implement the CDisp class
 *   aa451483  CDispBasic::CDispBasic : CDispBasic( );
 */

/* --- CEnumMediaTypes (aa451490, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides the mechanism for enumerating the pin's preferred media types
 *   aa451488  CEnumMediaTypes::AddRef : ULONG AddRef(void);
 *   aa451489  CEnumMediaTypes::CEnumMediaTypes : CEnumMediaTypes(CBasePin* pPin,CEnumMediaTypes* pEnumMediaTypes );
 *   aa451491  CEnumMediaTypes::Clone : HRESULT Clone(IEnumMediaTypes** ppEnum);
 *   aa451492  CEnumMediaTypes::Next : HRESULTNext(ULONGcMediaTypes,AM_MEDIA_TYPE** ppMediaTypes,ULONG* pcFetched );
 *   aa451493  CEnumMediaTypes::QueryInterface : HRESULT QueryInterface(REFIIDiid,void** ppvObject );
 *   aa451494  CEnumMediaTypes::Release : ULONG Release(void);
 *   aa451495  CEnumMediaTypes::Reset : HRESULT Reset(void);
 *   aa451496  CEnumMediaTypes::Skip : HRESULTSkip(ULONGcMediaTypes);
 */

/* --- CEnumPins (aa451499, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class supports the IEnumPins enumeration interface by calling CBaseFilter methods
 *   aa451497  CEnumPins::AddRef : ULONG AddRef(void);
 *   aa451498  CEnumPins::CEnumPins : CEnumPins(CBaseFilter* pFilter,CEnumPins* pEnumPins);
 *   aa451500  CEnumPins::Clone : HRESULT Clone(IEnumPins** ppEnum );
 *   aa451501  CEnumPins::Next : HRESULTNext(ULONGcPins,IPin** ppPins,ULONG* pcFetched);
 *   aa451502  CEnumPins::QueryInterface : HRESULTQueryInterface(REFIIDiid,void** ppvObject);
 *   aa451503  CEnumPins::Release : ULONG Release(void);
 *   aa451504  CEnumPins::Reset : HRESULT Reset(void);
 *   aa451505  CEnumPins::Skip : HRESULT Skip(ULONGcPins);
 */

/* --- CFactoryTemplate (aa451506, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides a template used by the default class factory code
 *   aa451507  CFactoryTemplate::CreateInstance : CUnknown* CreateInstance(LPUNKNOWNpUnk,HRESULT* phr);
 *   aa451508  CFactoryTemplate::IsClassID : Send Feedback Determines if the class identifier (CLSID) passed matches the CLSID assigned to this class template. BOOL IsClassID(REFCLSIDrclsid);
 */

/* --- CGenericList (aa451514, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is a template class that allows for a type-specific implementation of a list
 *   aa451509  CGenericList::AddAfter : POSITION AddAfter(POSITIONp,OBJECT* pObj);
 *   aa451510  CGenericList::AddBefore : POSITION AddBefore(POSITION p,OBJECT* pObj);
 *   aa451511  CGenericList::AddHead : POSITION AddHead(OBJECT* pObj);
 *   aa451512  CGenericList::AddTail : POSITION AddTail(OBJECT* pObj);
 *   aa451513  CGenericList::CGenericList : CGenericList(TCHAR* pName,INTiItems,BOOLbLock,BOOLbAlert);
 *   aa451515  CGenericList::Find : POSITION Find(OBJECT* pObj);
 *   aa451516  CGenericList::Get : OBJECT* Get(POSITIONpos);
 *   aa451517  CGenericList::GetCount : Send Feedback Retrieves the number of objects (object count) in the list. int GetCount( );
 *   aa451518  CGenericList::GetHead : OBJECT GetHead( );
 *   aa451519  CGenericList::GetHeadPosition : POSITION GetHeadPosition( );
 *   aa451520  CGenericList::GetNext : OBJECT* GetNext(POSITION&rp);
 *   aa451521  CGenericList::GetTailPosition : POSITION GetTailPosition( );
 *   aa451522  CGenericList::Remove : OBJECT* Remove(POSITIONpos);
 *   aa451523  CGenericList::RemoveHead : OBJECT* RemoveHead( );
 *   aa451524  CGenericList::RemoveTail : OBJECT* RemoveTail( );
 */

/* --- CGuidNameList (aa451525, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements an array of globally unique identifier (GUID) names based on the predefined names of GUID s that come with DirectShow
 *   aa451526  CGuidNameList::operator [] : (no print)
 */

/* --- CLoadDirectDraw (aa451533, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback DirectShow must work on multiple platforms
 *   aa451534  CLoadDirectDraw::CLoadDirectDraw : CLoadDirectDraw(void);
 *   aa451535  CLoadDirectDraw::GetDirectDraw : LPDIRECTDRAW GetDirectDraw(void);
 *   aa451536  CLoadDirectDraw::IsDirectDrawLoaded : HRESULT IsDirectDrawLoaded(void);
 *   aa451537  CLoadDirectDraw::IsDirectDrawVersion1 : BOOL IsDirectDrawVersion1(void);
 *   aa451538  CLoadDirectDraw::LoadDirectDraw : HRESULT LoadDirectDraw(LPSTRszDevice);
 *   aa451539  CLoadDirectDraw::ReleaseDirectDraw : void ReleaseDirectDraw(void);
 */

/* --- CMediaControl (aa451540, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides base class handling of the IDispatch methods of the dual-interface IMediaControl 
 *   aa451541  CMediaControl::CMediaControl : CMediaControl(const TCHAR* pName,LPUNKNOWNpUnk);
 *   aa451542  CMediaControl::GetIDsOfNames : Send Feedback Maps a single member function and an optional set of parameters to a corresponding set of integer dispatch identifiers (DISPIDs), which 
 *   aa451543  CMediaControl::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo** pptinfo);
 *   aa451544  CMediaControl::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 *   aa451545  CMediaControl::Invoke : HRESULTInvoke(DISPIDdispidMember,REFIIDriid,LCIDlcid,WORDwFlags,DISPPARAMS* pdispparams,VARIANT* pvarResult,EXCEPINFO* pexcepinfo,UINT* puArgErr);
 *   aa451546  CMediaControl::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CMediaEvent (aa451547, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides base class implementation of the IDispatch methods of the dual-interface IMediaEvent 
 *   aa451548  CMediaEvent::CMediaEvent : CMediaEvent(const TCHAR* pName,LPUNKNOWNpUnk);
 *   aa451549  CMediaEvent::GetIDsOfNames : HRESULTGetIDsOfNames(REFIIDriid,OLECHAR** rgszNames,UINTcNames,LCIDlcid,DISPID* rgdispid);
 *   aa451550  CMediaEvent::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo** pptinfo);
 *   aa451551  CMediaEvent::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 *   aa451552  CMediaEvent::Invoke : HRESULTInvoke(DISPIDdispidMember,REFIIDriid,LCIDlcid,WORDwFlags,DISPPARAMS* pdispparams,VARIANT* pvarResult,EXCEPINFO* pexcepinfo,UINT* puArgErr);
 *   aa451553  CMediaEvent::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CMediaPosition (aa451554, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is a base class that handles the IDispatch methods of the dual-interface IMediaPosition 
 *   aa451556  CMediaPosition::CMediaPosition : CMediaPosition(const TCHAR* pName,LPUNKNOWNpUnk);
 *   aa451557  CMediaPosition::GetIDsOfNames : HRESULTGetIDsOfNames(REFIIDriid,OLECHAR** rgszNames,UINTcNames,LCIDlcid,DISPID* rgdispid);
 *   aa451558  CMediaPosition::GetTypeInfo : HRESULT GetTypeInfo(UINTitinfo,LCIDlcid,ITypeInfo** pptinfo);
 *   aa451559  CMediaPosition::GetTypeInfoCount : HRESULT GetTypeInfoCount(UINT* pctinfo);
 *   aa451560  CMediaPosition::Invoke : HRESULTInvoke(DISPIDdispidMember,REFIIDriid,LCIDlcid,WORDwFlags,DISPPARAMS* pdispparams,VARIANT* pvarResult,EXCEPINFO* pexcepinfo,UINT* puArgErr);
 *   aa451561  CMediaPosition::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CMediaSample (aa451563, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class represents a buffer object that supports the IMediaSample interface
 *   aa451562  CMediaSample::AddRef : ULONG AddRef(void);
 *   aa451564  CMediaSample::CMediaSample : CMediaSample(TCHAR* pName,CBaseAllocator* pAllocator,HRESULT* phr,LPBYTEpBuffer=NULL,LONGlength=0);
 *   aa451565  CMediaSample::GetActualDataLength : HRESULT GetActualDataLength(void);
 *   aa451566  CMediaSample::GetMediaTime : HRESULT GetMediaTime(LONGLONG* pStart,LONGLONG* pEnd);
 *   ms926607  CMediaSample::GetMediaType : HRESULT GetMediaType(AM_MEDIA_TYPE** ppMediaType);
 *   ms926682  CMediaSample::GetPointer : HRESULT GetPointer(BYTE** ppBuffer);
 *   ms926690  CMediaSample::GetSize : HRESULT GetSize(void);
 *   ms926691  CMediaSample::GetTime : HRESULT GetTime(REFERENCE_TIME* pTimeStart,REFERENCE_TIME* pTimeEnd);
 *   ms926692  CMediaSample::IsDiscontinuity : HRESULT IsDiscontinuity(void);
 *   ms926693  CMediaSample::IsPreroll : HRESULT IsPreroll(void);
 *   ms926694  CMediaSample::IsSyncPoint : HRESULT IsSyncPoint(void);
 *   ms926695  CMediaSample::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms926696  CMediaSample::QueryInterface : HRESULT QueryInterface(REFIIDiid,void** ppvObject);
 *   ms926697  CMediaSample::Release : ULONG Release(void);
 *   ms926698  CMediaSample::SetActualDataLength : HRESULT SetActualDataLength(longlLen);
 *   ms926699  CMediaSample::SetDiscontinuity : HRESULTSetDiscontinuity(BOOLbDiscont);
 *   ms926700  CMediaSample::SetMediaTime : HRESULT SetMediaTime(LONGLONG* pStart,LONGLONG* pEnd);
 *   ms926701  CMediaSample::SetMediaType : HRESULT SetMediaType(AM_MEDIA_TYPE* pMediaType);
 *   ms926702  CMediaSample::SetPointer : SetPointer(BYTE* ptr,LONGcBytes );
 *   ms926703  CMediaSample::SetPreroll : HRESULT SetPreroll(BOOLbIsPreroll);
 *   ms926704  CMediaSample::SetSyncPoint : HRESULT SetSyncPoint(BOOLbIsSyncPoint);
 *   ms926705  CMediaSample::SetTime : HRESULT SetTime(REFERENCE_TIME* pTimeStart,REFERENCE_TIME* pTimeEnd);
 */

/* --- CMediaType (ms926708, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback When filters are connected, they typically negotiate a type between them
 *   ms926706  CMediaType::AllocFormatBuffer : BYTE* AllocFormatBuffer(ULONGlength);
 *   ms926709  CMediaType::CMediaType : CMediaType( );
 *   ms926710  CMediaType::Format : BYTE* Format( ) const;
 *   ms926711  CMediaType::FormatLength : ULONG FormatLength( ) const;
 *   ms926712  CMediaType::FormatType : const GUID* FormatType( ) const;
 *   ms926713  CMediaType::GetSampleSize : ULONG GetSampleSize( ) const;
 *   ms926714  CMediaType::InitMediaType : void InitMediaType( );
 *   ms926715  CMediaType::IsFixedSize : BOOL IsFixedSize( ) const;
 *   ms926716  CMediaType::IsPartiallySpecified : BOOL IsPartiallySpecified( ) const;
 *   ms926717  CMediaType::IsTemporalCompressed : BOOL IsTemporalCompressed( ) const;
 *   ms926718  CMediaType::IsValid : BOOL IsValid( ) const;
 *   ms926719  CMediaType::MatchesPartial : BOOL MatchesPartial(const CMediaType* ppartial) const;
 *   ms926723  CMediaType::ReallocFormatBuffer : BYTE* ReallocFormatBuffer(ULONGlength);
 *   ms926724  CMediaType::ResetFormatBuffer : void ResetFormatBuffer( );
 *   ms926725  CMediaType::SetFormat : BOOLSetFormat(BYTE* pFormat,ULONGlength);
 *   ms926726  CMediaType::SetFormatType : void SetFormatType(const GUID* pformattype);
 *   ms926727  CMediaType::SetSampleSize : void SetSampleSize(ULONGsz);
 *   ms926728  CMediaType::SetSubtype : void SetSubtype(const GUID* psubtype);
 *   ms926729  CMediaType::SetTemporalCompression : Send Feedback Marks the media type so that the data stream it describes might or might not contain temporal compression (according to the input Boolea
 *   ms926730  CMediaType::SetType : void SetType(const GUID* ptype);
 *   ms926731  CMediaType::SetVariableSize : void SetVariableSize( );
 *   ms926732  CMediaType::Subtype : const GUID* Type( ) const;
 *   ms926733  CMediaType::Type : const GUID* Type( ) const;
 *   ms926722  CMediaType::operator != : (no print)
 *   ms926720  CMediaType::operator = : (no print)
 *   ms926721  CMediaType::operator == : (no print)
 */

/* --- CMemAllocator (ms926735, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides support for IMemAllocator by using the new operator to allocate memory
 *   ms926734  CMemAllocator::Alloc : HRESULT Alloc(void);
 *   ms926736  CMemAllocator::CMemAllocator : CMemAllocator(TCHAR* pName,LPUNKNOWN lpUnk,HRESULT* phr);
 *   ms926737  CMemAllocator::CreateInstance : static CUnknown* CreateInstance(LPUNKNOWNpUnk,HRESULT* phr);
 *   ms926738  CMemAllocator::Free : HRESULT Free(void);
 *   ms926739  CMemAllocator::ReallyFree : void ReallyFree (void);
 *   ms926740  CMemAllocator::SetProperties : HRESULT SetProperties(ALLOCATOR_PROPERTIES* pRequest,ALLOCATOR_PROPERTIES* pActual);
 */

/* --- CMsg (ms926741, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback The CMsgThread class provides support for a worker thread to which requests can be posted asynchronously instead of sent directly
 *   ms926742  CMsg::CMsg : CMsg(UINTu,DWORDdw,LPVOIDlp,CAMEvent*pEvent);
 */

/* --- CMsgThread (ms926743, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is a worker thread class that queues requests to the queuing thread for completion asynchronously
 *   ms926744  CMsgThread::CMsgThread : CMsgThread( );
 *   ms926745  CMsgThread::CreateThread : BOOL CreateThread( );
 *   ms926746  CMsgThread::GetThreadHandle : HANDLE GetThreadHandle( );
 *   ms926747  CMsgThread::GetThreadID : DWORD GetThreadID( );
 *   ms926748  CMsgThread::GetThreadMsg : void virtual GetThreadMsg(CMsg* msg);
 *   ms926749  CMsgThread::GetThreadPriority : int GetThreadPriority( );
 *   ms926750  CMsgThread::OnThreadInit : virtual void OnThreadInit( );
 *   ms926751  CMsgThread::PutThreadMsg : voidPutThreadMsg(UINTuMsg,DWORDdwMsgFlags,LPVOIDlpMsgParam,CAMEvent* pEvent=NULL);
 *   ms926752  CMsgThread::ResumeThread : DWORD ResumeThread( );
 *   ms926753  CMsgThread::SetThreadPriority : BOOL SetThreadPriority(intnPriority);
 *   ms926754  CMsgThread::SuspendThread : DWORD SuspendThread( );
 *   ms926755  CMsgThread::ThreadMessageProc : virtual LRESULT ThreadMessageProc(UINTuMsg,DWORDdwFlags,LPVOIDlpParam,CAMEvent* pEvent);
 *   ms926756  CMsgThread::WaitForThreadExit : BOOL WaitForThreadExit(LPDWORDlpdwExitCode);
 */

/* --- COARefTime (ms926757, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class converts between the Automation-compatible REFTIME type and the REFERENCE_TIME type used within and between filters
 *   ms926758  COARefTime::COARefTime : COARefTime(CRefTimet);
 *   ms926763  COARefTime::Operator != : (no print)
 *   ms926765  COARefTime::Operator &gt; : BOOL operator > (const COARefTime&rt);
 *   ms926766  COARefTime::Operator &gt;= : (no print)
 *   ms926767  COARefTime::Operator &lt; : BOOL operator < (const COARefTime&rt);
 *   ms926768  COARefTime::Operator &lt;= : (no print)
 *   ms926760  COARefTime::Operator * : COARefTime operator*(LONGl);
 *   ms926771  COARefTime::Operator + : (no print)
 *   ms926772  COARefTime::Operator += : (no print)
 *   ms926769  COARefTime::Operator - : (no print)
 *   ms926770  COARefTime::Operator -= : (no print)
 *   ms926764  COARefTime::Operator / : (no print)
 *   ms926761  COARefTime::Operator = : (no print)
 *   ms926762  COARefTime::Operator == : (no print)
 *   ms926759  COARefTime::double : operator double();
 */

/* --- COutputQueue (ms926789, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback Output pins use the COutputQueue to send samples to another filter by using the local memory-based transport (that is, to input pins that support the IMe
 *   ms926788  COutputQueue::BeginFlush : void BeginFlush( );
 *   ms907059  COutputQueue::EOS : void EOS( );
 *   ms907055  COutputQueue::EndFlush : void EndFlush( );
 *   ms907069  COutputQueue::FreeSamples : void FreeSamples( );
 *   ms927025  COutputQueue::InitialThreadProc : static DWORD WINAPI InitialThreadProc(LPVOIDpv);
 *   ms927029  COutputQueue::IsIdle : BOOL IsIdle( );
 *   ms927035  COutputQueue::IsQueued : BOOL IsQueued( );
 *   ms927040  COutputQueue::IsSpecialSample : Send Feedback Determines if a sample is one of the special control samples (containing no data). BOOL IsSpecialSample(IMediaSample* pSample);
 *   ms927045  COutputQueue::NewSegment : HRESULT NewSegment(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop,doubledRate);
 *   ms927050  COutputQueue::NotifyThread : void NotifyThread( );
 *   ms927056  COutputQueue::QueueSample : void QueueSample(IMediaSample* pSample);
 *   ms927066  COutputQueue::Receive : HRESULT Receive(IMediaSample* pSample);
 *   ms927072  COutputQueue::ReceiveMultiple : HRESULTReceiveMultiple(IMediaSample** ppSamples,longnSamples,long* nSamplesProcessed);
 *   ms927080  COutputQueue::Reset : void Reset( );
 *   ms927084  COutputQueue::SendAnyway : void SendAnyway( );
 *   ms927088  COutputQueue::ThreadProc : DWORD ThreadProc( );
 */

/* --- CPersistStream (ms927092, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is the base class for persistent properties of filters (that is, filter properties in saved graphs)
 *   ms927096  CPersistStream::CPersistStream : CPersistStream( IUnknown* pUnk, HRESULT* phr);
 *   ms927100  CPersistStream::GetClassID : HRESULT GetClassID( CLSID* pClsID);
 *   ms927104  CPersistStream::GetSizeMax : HRESULT GetSizeMax( ULARGE_INTEGER* pcbSize);
 *   ms927107  CPersistStream::GetSoftwareVersion : virtual DWORD GetSoftwareVersion(void);
 *   ms927112  CPersistStream::IsDirty : HRESULT IsDirty(void);
 *   ms927116  CPersistStream::Load : HRESULT Load( LPSTREAM pStm);
 *   ms927120  CPersistStream::ReadFromStream : virtual HRESULT ReadFromStream( IStream* pStream);
 *   ms927124  CPersistStream::Save : HRESULT Save( LPSTREAM pStm, BOOL fClearDirty);
 *   ms927128  CPersistStream::SetDirty : HRESULT SetDirty( BOOL fDirty);
 *   ms927132  CPersistStream::SizeMax : virtual int SizeMax(void);
 *   ms927137  CPersistStream::WriteToStream : virtual HRESULT WriteToStream( IStream* pStream);
 */

/* --- CPosPassThru (ms927155, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is a utility class that handles the IMediaPosition and IMediaSeeking interfaces for single-input pin renderers and transform filters
 *   ms927167  CPosPassThru::CPosPassThru : CPosPassThru(const TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr,IPin* pPin);
 *   ms927143  CPosPassThru::CanSeekBackward : HRESULT CanSeekBackward(LONG* pCanSeekBackward);
 *   ms927146  CPosPassThru::CanSeekForward : HRESULT CanSeekForward(LONG* pCanSeekForward);
 *   ms927150  CPosPassThru::CheckCapabilities : HRESULT CheckCapabilities(DWORD* pCapabilities);
 *   ms927159  CPosPassThru::ConvertTimeFormat : HRESULT ConvertTimeFormat(LONGLONG* pTarget,const GUID* pTargetFormat,LONGLONGSource,const GUID* pSourceFormat);
 *   ms927174  CPosPassThru::ForceRefresh : HRESULT ForceRefresh( );
 *   ms927181  CPosPassThru::GetAvailable : HRESULT GetAvailable(LONGLONG* pEarliest,LONGLONG* pLatest);
 *   ms927186  CPosPassThru::GetCapabilities : HRESULT GetCapabilities(DWORD* pCapabilities);
 *   ms927192  CPosPassThru::GetCurrentPosition : HRESULT GetCurrentPosition(LONGLONG* pCurrent);
 *   ms927197  CPosPassThru::GetDuration : HRESULT GetDuration(LONGLONG* pDuration);
 *   ms927201  CPosPassThru::GetMediaTime : virtual HRESULT GetMediaTime(LONGLONG* pStartTime,LONGLONG* pEndTime);
 *   ms927209  CPosPassThru::GetPositions : HRESULT GetPositions(LONGLONG* pCurrent,LONGLONG* pStop);
 *   ms927214  CPosPassThru::GetPreroll : HRESULT GetPreroll(LONGLONG* pllPreroll);
 *   ms927224  CPosPassThru::GetRate : HRESULT GetRate(double* pdRate);
 *   ms927229  CPosPassThru::GetStopPosition : HRESULT GetStopPosition(LONGLONG* pStop);
 *   ms927236  CPosPassThru::GetTimeFormat : HRESULT GetTimeFormat(const GUID* pFormat);
 *   ms927266  CPosPassThru::IsFormatSupported : HRESULT IsFormatSupported(const GUID* pFormat);
 *   ms927271  CPosPassThru::IsUsingTimeFormat : HRESULT IsUsingTimeFormat(const GUID* pFormat);
 *   ms927277  CPosPassThru::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void**ppv);
 *   ms907116  CPosPassThru::QueryPreferredFormat : HRESULT QueryPreferredFormat(GUID* pFormat);
 *   ms907124  CPosPassThru::SetPositions : HRESULTSetPositions(LONGLONG* pCurrent,DWORDdwCurrentFlags,LONGLONG* pStop,DWORDdwStopFlags);
 *   ms907132  CPosPassThru::SetRate : HRESULT SetRate(doubledRate);
 *   ms907138  CPosPassThru::SetTimeFormat : HRESULT SetTimeFormat(const GUID* pFormat);
 *   ms927239  CPosPassThru::get_CurrentPosition : HRESULT get_CurrentPosition(REFTIME* pllTime);
 *   ms927249  CPosPassThru::get_Duration : HRESULT get_Duration(REFTIME* plength);
 *   ms927219  CPosPassThru::get_PrerollTime : HRESULT get_PrerollTime(REFTIME* pllTime);
 *   ms927254  CPosPassThru::get_Rate : HRESULT get_Rate(double* pdRate);
 *   ms927232  CPosPassThru::get_StopTime : HRESULT get_StopTime(REFTIME* pllTime);
 *   ms907082  CPosPassThru::put_CurrentPosition : HRESULT put_CurrentPosition(REFTIMEllTime);
 *   ms907092  CPosPassThru::put_PrerollTime : HRESULT put_PrerollTime(REFTIMEllTime);
 *   ms907099  CPosPassThru::put_Rate : HRESULT put_Rate(doubledRate);
 *   ms907109  CPosPassThru::put_StopTime : HRESULT put_StopTime(REFTIMEllTime);
 */

/* --- CPullPin (ms907177, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is provided to allow a filter downstream from the source to create a thread and pull a media stream from an asynchronous source filter that su
 *   ms907144  CPullPin::Active : HRESULT Active(void);
 *   ms907151  CPullPin::AlignDown : LONGLONG AlignDown(LONGLONGll,LONGlAlign);
 *   ms907161  CPullPin::AlignUp : LONGLONG AlignUp(LONGLONGll,LONGlAlign);
 *   ms907169  CPullPin::BeginFlush : virtual HRESULT BeginFlush(void);
 *   ms907194  CPullPin::CPullPin : CPullPin(void);
 *   ms907185  CPullPin::Connect : HRESULT Connect(Iunknown *pUnk,ImemAllocator *pAlloc,BOOLbSync);
 *   ms907200  CPullPin::DecideAllocator : virtual HRESULT DecideAllocator(ImemAllocator* pAlloc,ALLOCATOR_PROPERTIES* pProps);
 *   ms907206  CPullPin::Disconnect : HRESULT Disconnect(void);
 *   ms907211  CPullPin::Duration : HRESULT Duration(REFERENCE_TIME* ptDuration);
 *   ms907217  CPullPin::EndFlush : virtual HRESULT EndFlush(void) PURE;
 *   ms907220  CPullPin::EndOfStream : virtual HRESULT EndOfStream(void) PURE;
 *   ms907232  CPullPin::GetReader : IAsyncReader *GetReader(void);
 *   ms907238  CPullPin::Inactive : HRESULT Inactive(void);
 *   ms907244  CPullPin::OnError : virtual void OnError(HRESULThr) PURE;
 *   ms907252  CPullPin::Receive : virtual HRESULT Receive(IMediaSample* pSample) PURE;
 *   ms907260  CPullPin::Seek : HRESULT Seek(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop);
 */

/* --- CQueue (ms907266, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements a simple queue abstract data type
 *   ms907269  CQueue::CQueue : CQueue(intn);
 *   ms907271  CQueue::GetQueueObject : T GetQueueObject( );
 *   ms907273  CQueue::PutQueueObject : void PutQueueObject(Tobject);
 */

/* --- CRefTime (ms907283, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is used to manage reference times
 *   ms907290  CRefTime::CRefTime : CRefTime( );
 *   ms907295  CRefTime::GetUnits : LONGLONG GetUnits(void);
 *   ms907303  CRefTime::Millisecs : LONG Millisecs(void);
 *   ms927485  CRefTime::operator (REFERENCE_TIME) : operator REFERENCE_TIME() const;
 *   ms907321  CRefTime::operator += : (no print)
 *   ms927278  CRefTime::operator -= : (no print)
 *   ms907310  CRefTime::operator = : (no print)
 */

/* --- CRendererInputPin (ms927517, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This input pin class channels calls to the rendering filter
 *   ms927491  CRendererInputPin::Active : Send Feedback Switches the pin to the active (paused or running) mode. HRESULT Active( );
 *   ms927495  CRendererInputPin::Allocator : IMemAllocator* Allocator( ) const;
 *   ms927500  CRendererInputPin::BeginFlush : HRESULT BeginFlush( );
 *   ms927504  CRendererInputPin::BreakConnect : HRESULT BreakConnect( );
 *   ms938749  CRendererInputPin::CRendererInputPin : CRendererInputPin(CBaseRenderer* pRenderer,HRESULT* phr,LPCWSTRName);
 *   ms927513  CRendererInputPin::CheckMediaType : HRESULT CheckMediaType(const CMediaType* pmt);
 *   ms938724  CRendererInputPin::CompleteConnect : HRESULT CompleteConnect(IPin* pReceivePin);
 *   ms938807  CRendererInputPin::EndFlush : HRESULT EndFlush(void);
 *   ms938813  CRendererInputPin::EndOfStream : HRESULT EndOfStream(void);
 *   ms938820  CRendererInputPin::Inactive : HRESULT Inactive(void);
 *   ms938821  CRendererInputPin::QueryId : HRESULT QueryId(LPWSTR* Id);
 *   ms938822  CRendererInputPin::Receive : HRESULT Receive(IMediaSample* pMediaSample);
 *   ms938823  CRendererInputPin::SetMediaType : HRESULT SetMediaType(const CMediaType*pmt);
 */

/* --- CRendererPosPassThru (ms938824, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback The IMediaSeeking interface is used to seek to a specific sample, frame, or indexed field
 *   ms938825  CRendererPosPassThru::CRendererPosPassThru : CRendererPosPassThru(const TCHAR* pName,LPUNKNOWN pUnk,HRESULT* phr,IPin* pPin);
 *   ms938826  CRendererPosPassThru::GetMediaTime : HRESULT GetMediaTime(LONGLONG* pStartTime,LONGLONG* pEndTime);
 *   ms938828  CRendererPosPassThru::RegisterMediaTime : HRESULT RegisterMediaTime(IMediaSample* pMediaSample);
 *   ms938829  CRendererPosPassThru::ResetMediaTime : HRESULT ResetMediaTime(void);
 */

/* --- CSource (ms938833, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class and its corresponding class, CSourceStream , simplify the construction of source filters that produce continuous streams of data comparable to
 *   ms938832  CSource::AddPin : HRESULT AddPin(CSourceStream* pStream);
 *   ms938834  CSource::CSource : CSource(TCHAR* pName,LPUNKNOWNlpunk,CLSIDclsid);
 *   ms938835  CSource::FindPinNumber : int FindPinNumber(IPin* iPin);
 *   ms938836  CSource::GetPin : CBasePin* GetPin(intn);
 *   ms938837  CSource::GetPinCount : int GetPinCount(void);
 *   ms938853  CSource::RemovePin : HRESULT RemovePin(CSourceStream* pStream);
 *   ms938852  CSource::pStateLock : CCritSec* pStateLock(void);
 */

/* --- CSourcePosition (ms938841, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract class that assists source filters with the implementation of IMediaPosition methods
 *   ms938842  CSourcePosition::CSourcePosition : CSourcePosition(const TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr,CCritSec* pLock);
 *   ms938838  CSourcePosition::ChangeRate : virtual HRESULT ChangeRate( ) PURE;
 *   ms938839  CSourcePosition::ChangeStart : virtual HRESULT ChangeStart( ) PURE;
 *   ms938840  CSourcePosition::ChangeStop : virtual HRESULT ChangeStop( ) PURE;
 *   ms938843  CSourcePosition::get_CurrentPosition : HRESULT get_CurrentPosition(REFTIME* pllTime);
 *   ms938844  CSourcePosition::get_Duration : HRESULT get_Duration(REFTIME* plength);
 *   ms938845  CSourcePosition::get_PrerollTime : HRESULT get_PrerollTime(REFTIME* pllTime);
 *   ms938846  CSourcePosition::get_Rate : HRESULT get_Rate(double* pdRate);
 *   ms938847  CSourcePosition::get_StopTime : HRESULT get_StopTime(REFTIME* pllTime);
 *   ms938848  CSourcePosition::put_CurrentPosition : HRESULT put_CurrentPosition(REFTIMEllTime);
 *   ms938849  CSourcePosition::put_PrerollTime : HRESULT put_PrerollTime(REFTIMEllTime);
 *   ms938850  CSourcePosition::put_Rate : HRESULT put_Rate(doubledRate);
 *   ms938851  CSourcePosition::put_StopTime : HRESULT put_StopTime(REFTIMEllTime);
 */

/* --- CSourceSeeking (ms938858, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract class that assists source filters with the implementation of IMediaSeeking interface methods
 *   ms938860  CSourceSeeking::CSourceSeeking : CSourceSeeking(const TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr,CCritSec* pLock);
 *   ms938854  CSourceSeeking::ChangeRate : virtual HRESULT ChangeRate( ) PURE;
 *   ms938855  CSourceSeeking::ChangeStart : virtual HRESULT ChangeStart( ) PURE;
 *   ms938856  CSourceSeeking::ChangeStop : virtual HRESULT ChangeStop( ) PURE;
 *   ms938857  CSourceSeeking::CheckCapabilities : HRESULT CheckCapabilities(DWORD* pCapabilities);
 *   ms938859  CSourceSeeking::ConvertTimeFormat : HRESULT ConvertTimeFormat(LONGLONG* pTarget,const GUID* pTargetFormat,LONGLONGSource,const GUID* pSourceFormat);
 *   ms938861  CSourceSeeking::GetAvailable : HRESULT GetAvailable(LONGLONG* pEarliest,LONGLONG* pLatest);
 *   ms938862  CSourceSeeking::GetCapabilities : HRESULT GetCapabilities(DWORD* pCapabilities);
 *   ms938863  CSourceSeeking::GetCurrentPosition : HRESULT GetCurrentPosition(LONGLONG* pCurrent);
 *   ms938864  CSourceSeeking::GetDuration : HRESULT GetDuration(LONGLONG* pDuration);
 *   ms938865  CSourceSeeking::GetPositions : HRESULT GetPositions(LONGLONG* pCurrent,LONGLONG* pStop);
 *   ms938866  CSourceSeeking::GetPreroll : HRESULT GetPreroll(LONGLONG* pPreroll);
 *   ms938867  CSourceSeeking::GetRate : HRESULT GetRate(double* pdRate);
 *   ms938868  CSourceSeeking::GetStopPosition : HRESULT GetStopPosition(LONGLONG* pStop);
 *   ms938869  CSourceSeeking::GetTimeFormat : HRESULT GetTimeFormat(const GUID* pFormat);
 *   ms938870  CSourceSeeking::IsFormatSupported : HRESULT IsFormatSupported(const GUID* pFormat);
 *   ms938871  CSourceSeeking::IsUsingTimeFormat : HRESULT IsUsingTimeFormat(const GUID* pFormat);
 *   ms938872  CSourceSeeking::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms938873  CSourceSeeking::QueryPreferredFormat : HRESULT QueryPreferredFormat(GUID* pFormat);
 *   ms938874  CSourceSeeking::SetPositions : HRESULTSetPositions(LONGLONG* pCurrent,DWORDCurrentFlags,LONGLONG* pStop,DWORDStopFlags);
 *   ms938875  CSourceSeeking::SetRate : HRESULT SetRate(doubledRate);
 *   ms938876  CSourceSeeking::SetTimeFormat : HRESULT SetTimeFormat(const GUID* pFormat);
 */

/* --- CSourceStream (ms938890, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback Derive from this class to provide a class that creates the data stream from one of the output pins
 *   ms938877  CSourceStream::Active : HRESULT Active(void);
 *   ms938891  CSourceStream::CSourceStream : CSourceStream(TCHAR*pObjectName,HRESULT*phr,CSource*pms,LPCWSTRpName);
 *   ms938878  CSourceStream::CheckMediaType : virtual HRESULT CheckMediaType(CMediaType* pMediaType);
 *   ms938879  CSourceStream::CheckRequest : BOOL CheckRequest(Command* pCom);
 *   ms938892  CSourceStream::DoBufferProcessingLoop : virtual HRESULT DoBufferProcessingLoop(void);
 *   ms938893  CSourceStream::Exit : HRESULT Exit(void);
 *   ms938894  CSourceStream::FillBuffer : virtual HRESULT FillBuffer(IMediaSample* pSample) PURE;
 *   ms938895  CSourceStream::GetMediaType : virtual HRESULT GetMediaType(intiPosition,CMediaType* pMediaType);
 *   ms938896  CSourceStream::GetRequest : Command GetRequest(void);
 *   ms938897  CSourceStream::Inactive : HRESULT Inactive(void);
 *   ms938898  CSourceStream::Init : HRESULT Init(void);
 *   ms938899  CSourceStream::OnThreadCreate : virtual HRESULT OnThreadCreate(void);
 *   ms938900  CSourceStream::OnThreadDestroy : virtual HRESULT OnThreadDestroy(void);
 *   ms938901  CSourceStream::OnThreadStartPlay : virtual HRESULT OnThreadStartPlay(void);
 *   ms938902  CSourceStream::Pause : HRESULT Pause(void);
 *   ms938903  CSourceStream::Run : HRESULT Run(void);
 *   ms938904  CSourceStream::Stop : HRESULT Stop(void);
 *   ms938905  CSourceStream::ThreadProc : virtual DWORD ThreadProc(void);
 */

/* --- CSystemClock (ms938906, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements a system clock that provides time information and timing signals to an application
 *   ms938908  CSystemClock::CSystemClock : CSystemClock(TCHAR* pName,LPUNKNOWNpUnk,HRESULT* phr);
 *   ms938907  CSystemClock::CreateInstance : static CUnknown *WINAPI CreateInstance(LPUNKNOWNpUnk,HRESULT* phr);
 *   ms938909  CSystemClock::GetClassID : HRESULT GetClassID(CLSID* pClsID);
 *   ms938910  CSystemClock::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 */

/* --- CTransformFilter (ms938917, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class that supports a simple transform filter with a single input and a single output
 *   ms938911  CTransformFilter::AlterQuality : virtual HRESULT AlterQuality(Qualityq);
 *   ms938912  CTransformFilter::BeginFlush : virtual HRESULT BeginFlush( );
 *   ms938913  CTransformFilter::BreakConnect : virtual HRESULT BreakConnect(PIN_DIRECTIONdir);
 *   ms938919  CTransformFilter::CTransformFilter : CTransformFilter(TCHAR*pObjectName,LPUNKNOWNlpUnk,CLSIDclsid);
 *   ms938914  CTransformFilter::CheckConnect : virtual HRESULT CheckConnect(PIN_DIRECTIONdir,IPin* pPin);
 *   ms938915  CTransformFilter::CheckInputType : virtual HRESULT CheckInputType(const CmediaType* mtIn)PURE;
 *   ms938916  CTransformFilter::CheckTransform : virtual HRESULT CheckTransform(const CMediaType* mtIn,const CMediaType* mtOut)PURE;
 *   ms938918  CTransformFilter::CompleteConnect : virtual HRESULT CompleteConnect(PIN_DIRECTIONdirection,IPin* pReceivePin);
 *   ms938920  CTransformFilter::DecideBufferSize : virtual HRESULT DecideBufferSize(IMemAllocator* pAlloc,ALLOCATOR_PROPERTIES* ppropInputRequest)PURE;
 *   ms938921  CTransformFilter::EndFlush : virtual HRESULT EndFlush( );
 *   ms938922  CTransformFilter::EndOfStream : virtual HRESULT EndOfStream( );
 *   ms938923  CTransformFilter::FindPin : HRESULT FindPin(LPCWSTRId,IPin** ppPin);
 *   ms938924  CTransformFilter::GetMediaType : Send Feedback Returns one of the media types that the output pin supports (pure virtual). virtual HRESULT GetMediaType(intiPosition,CMediaType* pMedia
 *   ms938925  CTransformFilter::GetPin : virtual CBasePin *GetPin(intn);
 *   ms938926  CTransformFilter::GetPinCount : virtual int GetPinCount( );
 *   ms939037  CTransformFilter::NewSegment : virtual HRESULT NewSegment(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop,doubledRate);
 *   ms939039  CTransformFilter::Pause : HRESULT Pause (void);
 *   ms939048  CTransformFilter::Receive : HRESULT Receive(IMediaSample* pSample);
 *   ms939049  CTransformFilter::RegisterPerfId : virtual void RegisterPerfId( );
 *   ms939050  CTransformFilter::SetMediaType : virtual HRESULT SetMediaType(PIN_DIRECTIONdirection,const CMediaType* pmt) PURE;
 *   ms939051  CTransformFilter::StartStreaming : virtual HRESULT StartStreaming( );
 *   ms939052  CTransformFilter::Stop : HRESULT Stop(void);
 *   ms939053  CTransformFilter::StopStreaming : virtual HRESULT StopStreaming( );
 *   ms939054  CTransformFilter::Transform : virtual HRESULT Transform(IMediaSample* pIn,IMediaSample* pOut)PURE;
 */

/* --- CTransformInputPin (ms939061, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements the input pin of a simple transform filter
 *   ms939055  CTransformInputPin::BeginFlush : HRESULT BeginFlush(void);
 *   ms939057  CTransformInputPin::BreakConnect : HRESULT BreakConnect( );
 *   ms939063  CTransformInputPin::CTransformInputPin : CTransformInputPin(TCHAR* pObjectName,CTransformFilter* pTransformFilter,HRESULT* phr,LPCWSTRpName);
 *   ms939058  CTransformInputPin::CheckConnect : HRESULT CheckConnect(IPin* pPin);
 *   ms939059  CTransformInputPin::CheckMediaType : HRESULT CheckMediaType(const CmediaType* mtIn);
 *   ms939060  CTransformInputPin::CheckStreaming : HRESULT CheckStreaming( );
 *   ms939062  CTransformInputPin::CompleteConnect : HRESULT CompleteConnect(IPin* pReceivePin);
 *   ms939064  CTransformInputPin::CurrentMediaType : CMediaType& CurrentMediaType( );
 *   ms939065  CTransformInputPin::EndFlush : HRESULT EndFlush(void);
 *   ms939066  CTransformInputPin::EndOfStream : HRESULT EndOfStream(void);
 *   ms939067  CTransformInputPin::NewSegment : HRESULT NewSegment(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop,doubledRate);
 *   ms939068  CTransformInputPin::QueryId : HRESULT QueryId(LPWSTR* Id);
 *   ms939069  CTransformInputPin::Receive : HRESULT Receive(IMediaSample* pSample);
 *   ms939070  CTransformInputPin::SetMediaType : HRESULT SetMediaType(const CmediaType* mt);
 */

/* --- CTransformOutputPin (ms939074, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements the output pin of a simple transform filter
 *   ms939071  CTransformOutputPin::BreakConnect : HRESULT BreakConnect( );
 *   ms939076  CTransformOutputPin::CTransformOutputPin : CTransformOutputPin(TCHAR* pObjectName,CTransformFilter* pTransformFilter,HRESULT* phr,LPCWSTRpName);
 *   ms939072  CTransformOutputPin::CheckConnect : HRESULT CheckConnect(IPin* pPin);
 *   ms939073  CTransformOutputPin::CheckMediaType : HRESULT CheckMediaType(const CmediaType* mtIn);
 *   ms939075  CTransformOutputPin::CompleteConnect : HRESULT CompleteConnect(IPin* pReceivePin);
 *   ms939077  CTransformOutputPin::CurrentMediaType : CMediaType& CurrentMediaType( );
 *   ms939078  CTransformOutputPin::DecideBufferSize : HRESULT DecideBufferSize(IMemAllocator* pAlloc,ALLOCATOR_PROPERTIES* ppropInputRequest);
 *   ms939079  CTransformOutputPin::GetMediaType : HRESULT GetMediaType(intiPosition,CMediaType* pMediaType);
 *   ms939080  CTransformOutputPin::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms939081  CTransformOutputPin::Notify : HRESULT Notify(IBaseFilter* pSelf,Qualityq);
 *   ms939082  CTransformOutputPin::QueryId : HRESULT QueryId(LPWSTR* Id);
 *   ms939083  CTransformOutputPin::SetMediaType : HRESULT SetMediaType(const CMediaType* mt);
 */

/* --- CTransInPlaceFilter (ms939085, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This is an abstract base class that provides support for a simple transform filter with a single input and a single output
 *   ms939088  CTransInPlaceFilter::CTransInPlaceFilter : CTransInPlaceFilter(TCHAR* pObjectName,LPUNKNOWNlpUnk,REFCLSIDclsid,HRESULT* phr);
 *   ms939084  CTransInPlaceFilter::CheckTransform : HRESULT CheckTransform(const CMediaType* mtIn,const CMediaType* mtOut);
 *   ms939086  CTransInPlaceFilter::CompleteConnect : HRESULT CompleteConnect(PIN_DIRECTIONdirection,IPin* pReceivePin);
 *   ms939087  CTransInPlaceFilter::Copy : IMediaSample* CTransInPlaceFilter::Copy(IMediaSample* pSource);
 *   ms939089  CTransInPlaceFilter::DecideBufferSize : HRESULT DecideBufferSize(IMemAllocator* pAlloc,ALLOCATOR_PROPERTIES* pProperties);
 *   ms939090  CTransInPlaceFilter::GetMediaType : HRESULT GetMediaType(intiPosition,CMediaType* pMediaType);
 *   ms939091  CTransInPlaceFilter::GetPin : virtual CBasePin* GetPin(intn);
 *   ms939092  CTransInPlaceFilter::InputPin : CTransInPlaceInputPin* InputPin( );
 *   ms939093  CTransInPlaceFilter::OutputPin : CTransInPlaceOutputPin* OutputPin( );
 *   ms939094  CTransInPlaceFilter::Receive : HRESULT Receive(IMediaSample* pSample);
 *   ms939095  CTransInPlaceFilter::RegisterPerfId : virtual void RegisterPerfId( );
 *   ms939096  CTransInPlaceFilter::Transform : virtual HRESULT Transform(IMediaSample* pSample) PURE;
 */

/* --- CTransInPlaceInputPin (ms939098, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements the input pin of a transform-inplace filter ( CTransInPlaceFilter )
 *   ms939099  CTransInPlaceInputPin::CTransInPlaceInputPin : CTransInPlaceInputPin(TCHAR* pObjectName,CTransInPlaceFilter* pFilter,HRESULT* phr,LPCWSTRpName);
 *   ms939097  CTransInPlaceInputPin::CheckMediaType : HRESULT CheckMediaType(constCMediaType* pmt);
 *   ms939100  CTransInPlaceInputPin::EnumMediaTypes : HRESULT EnumMediaTypes(IEnumMediaTypes** ppEnum);
 *   ms939101  CTransInPlaceInputPin::GetAllocator : HRESULT GetAllocator(IMemAllocator** ppAllocator);
 *   ms939102  CTransInPlaceInputPin::GetAllocatorRequirements : HRESULT GetAllocatorRequirements(ALLOCATOR_PROPERTIES* pProps);
 *   ms939103  CTransInPlaceInputPin::NotifyAllocator : HRESULT NotifyAllocator(IMemAllocator* pAllocator,BOOLbReadOnly);
 *   ms939104  CTransInPlaceInputPin::PeekAllocator : (no print)
 *   ms939105  CTransInPlaceInputPin::ReadOnly : (no print)
 */

/* --- CTransInPlaceOutputPin (ms939107, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class implements the output pin of a simple transform-inplace filter ( CTransInPlaceFilter )
 *   ms939109  CTransInPlaceOutputPin::CTransInPlaceOutputPin : CTransInPlaceOutputPin(TCHAR* pObjectName,CTransInPlaceFilter* pFilter,HRESULT* phr,LPCWSTRpName);
 *   ms939106  CTransInPlaceOutputPin::CheckMediaType : HRESULT CheckMediaType(const CMediaType* pmt);
 *   ms939108  CTransInPlaceOutputPin::ConnectedIMemInputPin : (no print)
 *   ms939110  CTransInPlaceOutputPin::DecideAllocator : HRESULT DecideAllocator(IMemInputPin* pPin,IMemAllocator**ppAlloc);
 *   ms939112  CTransInPlaceOutputPin::EnumMediaTypes : HRESULT EnumMediaTypes(IEnumMediaTypes** ppEnum);
 *   ms939113  CTransInPlaceOutputPin::PeekAllocator : (no print)
 *   ms939114  CTransInPlaceOutputPin::ReceiveAllocator : HRESULT ReceiveAllocator(IMemAllocator* pAllocator,BOOLbReadOnly);
 */

/* --- CUnknown (ms939115, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback All DirectShow Component Object Model (COM) objects derive from the CUnknown abstract base class
 *   ms939116  CUnknown::CUnknown : CUnknown(const TCHAR* pName,LPUNKNOWNpUnk);
 *   ms939117  CUnknown::GetOwner : LPUNKNOWN GetOwner(void);
 *   ms939118  CUnknown::NonDelegatingAddRef : ULONG NonDelegatingAddRef( );
 *   ms939119  CUnknown::NonDelegatingQueryInterface : HRESULT NonDelegatingQueryInterface(REFIIDriid,void** ppv);
 *   ms939120  CUnknown::NonDelegatingRelease : ULONG NonDelegatingRelease( );
 */

/* --- CVideoTransformFilter (ms939125, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class is designed primarily as a base class for AVI decompressor filters
 *   ms939124  CVideoTransformFilter::AlterQuality : virtual HRESULT AlterQuality(Qualityq);
 *   ms939126  CVideoTransformFilter::CVideoTransformFilter : CVideoTransformFilter(TCHAR* pName,LPUNKNOWNpUnk,REFCLSIDclsid);
 *   ms939127  CVideoTransformFilter::EndFlush : HRESULT EndFlush( );
 *   ms939128  CVideoTransformFilter::Receive : HRESULT Receive(IMediaSample* pSample);
 *   ms939129  CVideoTransformFilter::RegisterPerfId : virtual void RegisterPerfId( );
 *   ms939130  CVideoTransformFilter::ShouldSkipFrame : BOOL ShouldSkipFrame(IMediaSample* pIn);
 *   ms939131  CVideoTransformFilter::StartStreaming : virtual HRESULT StartStreaming( );
 */

/* --- FOURCCMap (aa451715, Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 o) ---
 * le Send Feedback This class provides conversion between GUID media subtypes and old-style FOURCC 32-bit media tags
 *   aa451716  FOURCCMap::FOURCCMap : FOURCCMap( );
 *   aa451717  FOURCCMap::GetFOURCC : DWORD GetFOURCC(void);
 *   aa451718  FOURCCMap::SetFOURCC : void SetFOURCC(const GUID* pguid);
 */

#endif /* AKARI_STREAMS_H */
