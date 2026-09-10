/* strmif.h -- documented-case alias for Dshow.h.
 * The IAMTuner book pages print Header: strmif.h (29 rows in the
 * harvest; IAMTuner + its 15 methods); the IAMTuner surface is
 * carried by dshow.h (M71b records).  See docs/inventory.md M72. */
#include "Dshow.h"/* ------------------------------------------------------------------
 * Book surface: dshow-iface (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451750 IAMDevMemoryAllocator Interface */
/* aa451745 IAMDevMemoryAllocator::Alloc */
/* aa451746 IAMDevMemoryAllocator::CheckMemory */
/* aa451747 IAMDevMemoryAllocator::Free */
/* aa451748 IAMDevMemoryAllocator::GetDevMemoryObject */
/* aa451749 IAMDevMemoryAllocator::GetInfo */
/* aa451752 IAMDevMemoryControl Interface */
/* aa451751 IAMDevMemoryControl::GetDevId */
/* aa451753 IAMDevMemoryControl::QueryWriteSync */
/* aa451754 IAMDevMemoryControl::WriteSync */
/* aa452538 IAMDroppedFrames Interface */
/* aa452534 IAMDroppedFrames::GetAverageFrameSize */
/* aa452535 IAMDroppedFrames::GetDroppedInfo */
/* aa452536 IAMDroppedFrames::GetNumDropped */
/* aa452537 IAMDroppedFrames::GetNumNotDropped */
/* aa451755 IAMMediaContentEx Interface */
/* aa451756 IAMMediaContentEx::MediaParameter */
/* aa451757 IAMMediaContentEx::MediaParameterName */
/* aa451758 IAMMediaContentEx::PlaylistCount */
/* ms908725 IAMovieSetup Interface */
/* ms908728 IAMovieSetup::Register */
/* ms908731 IAMovieSetup::Unregister */
/* ms908817 IAMStreamConfig Interface */
/* ms908804 IAMStreamConfig::GetFormat */
/* ms908807 IAMStreamConfig::GetNumberOfCapabilities */
/* ms908811 IAMStreamConfig::GetStreamCaps */
/* ms908823 IAMStreamConfig::SetFormat */
/* ms908830 IAMStreamControl Interface */
/* ms908825 IAMStreamControl::GetInfo */
/* ms908841 IAMStreamControl::StartAt */
/* ms908842 IAMStreamControl::StopAt */
/* ms908860 IAMStreamSelect Interface */
/* ms908847 IAMStreamSelect::Count */
/* ms908850 IAMStreamSelect::Enable */
/* ms908855 IAMStreamSelect::Info */
/* ms908871 IAsyncReader Interface */
/* ms908864 IAsyncReader::BeginFlush */
/* ms908869 IAsyncReader::EndFlush */
/* ms908876 IAsyncReader::Length */
/* ms939468 IAsyncReader::Request */
/* ms939473 IAsyncReader::RequestAllocator */
/* ms939476 IAsyncReader::SyncRead */
/* ms939481 IAsyncReader::SyncReadAligned */
/* ms939486 IAsyncReader::WaitForNext */
/* ms939498 IBaseFilter Interface */
/* ms939490 IBaseFilter::EnumPins */
/* ms939495 IBaseFilter::FindPin */
/* ms939504 IBaseFilter::JoinFilterGraph */
/* ms939507 IBaseFilter::QueryFilterInfo */
/* ms939511 IBaseFilter::QueryVendorInfo */
/* ms939524 IBasicAudio Interface */
/* ms939515 IBasicAudio::get_Balance */
/* ms939519 IBasicAudio::get_Volume */
/* ms939529 IBasicAudio::put_Balance */
/* ms939532 IBasicAudio::put_Volume */
/* ms939570 IBasicVideo Interface */
/* ms939551 IBasicVideo::get_AvgTimePerFrame */
/* ms939552 IBasicVideo::get_BitErrorRate */
/* ms939553 IBasicVideo::get_BitRate */
/* ms939556 IBasicVideo::get_DestinationHeight */
/* ms939557 IBasicVideo::get_DestinationLeft */
/* ms939559 IBasicVideo::get_DestinationTop */
/* ms939560 IBasicVideo::get_DestinationWidth */
/* ms939561 IBasicVideo::get_SourceHeight */
/* ms939562 IBasicVideo::get_SourceLeft */
/* ms939564 IBasicVideo::get_SourceTop */
/* ms939565 IBasicVideo::get_SourceWidth */
/* ms939566 IBasicVideo::get_VideoHeight */
/* ms939569 IBasicVideo::get_VideoWidth */
/* ms939554 IBasicVideo::GetCurrentImage */
/* ms939558 IBasicVideo::GetDestinationPosition */
/* ms939563 IBasicVideo::GetSourcePosition */
/* ms939567 IBasicVideo::GetVideoPaletteEntries */
/* ms939568 IBasicVideo::GetVideoSize */
/* ms939571 IBasicVideo::IsUsingDefaultDestination */
/* ms939572 IBasicVideo::IsUsingDefaultSource */
/* ms939573 IBasicVideo::put_DestinationHeight */
/* ms939574 IBasicVideo::put_DestinationLeft */
/* ms939575 IBasicVideo::put_DestinationTop */
/* ms939576 IBasicVideo::put_DestinationWidth */
/* ms939577 IBasicVideo::put_SourceHeight */
/* ms939578 IBasicVideo::put_SourceLeft */
/* ms939579 IBasicVideo::put_SourceTop */
/* ms939580 IBasicVideo::put_SourceWidth */
/* ms939581 IBasicVideo::SetDefaultDestinationPosition */
/* ms939582 IBasicVideo::SetDefaultSourcePosition */
/* ms939583 IBasicVideo::SetDestinationPosition */
/* ms939584 IBasicVideo::SetSourcePosition */
/* aa451779 IDirectDrawVideo Interface */
/* aa451769 IDirectDrawVideo::CanUseOverlayStretch */
/* aa451770 IDirectDrawVideo::CanUseScanLine */
/* aa451771 IDirectDrawVideo::GetCaps */
/* aa451772 IDirectDrawVideo::GetDirectDraw */
/* aa451773 IDirectDrawVideo::GetEmulatedCaps */
/* aa451774 IDirectDrawVideo::GetFourCCCodes */
/* aa451775 IDirectDrawVideo::GetSurfaceDesc */
/* aa451776 IDirectDrawVideo::GetSurfaceType */
/* aa451778 IDirectDrawVideo::GetSwitches */
/* aa451795 IDirectDrawVideo::SetDefault */
/* aa451796 IDirectDrawVideo::SetDirectDraw */
/* aa451797 IDirectDrawVideo::SetSwitches */
/* aa451798 IDirectDrawVideo::UseOverlayStretch */
/* aa451799 IDirectDrawVideo::UseScanLine */
/* aa451800 IDirectDrawVideo::UseWhenFullScreen */
/* aa451801 IDirectDrawVideo::WillUseFullScreen */
/* aa451802 IDistributorNotify Interface */
/* aa451803 IDistributorNotify::NotifyGraphChange */
/* aa451804 IDistributorNotify::Pause */
/* aa451805 IDistributorNotify::Run */
/* aa451806 IDistributorNotify::SetSyncSource */
/* aa451807 IDistributorNotify::Stop */
/* aa452542 IDVREngineHelpers Interface */
/* aa452539 IDVREngineHelpers::CleanupOrphanedRecordings */
/* aa452540 IDVREngineHelpers::DeleteRecording */
/* aa452541 IDVREngineHelpers::GetRecordingSizeOnDisk */
/* ms910535 IEnumFilters Interface */
/* ms910534 IEnumFilters::Clone */
/* ms910536 IEnumFilters::Next */
/* ms910538 IEnumFilters::Reset */
/* ms910539 IEnumFilters::Skip */
/* ms910541 IEnumMediaTypes Interface */
/* ms910540 IEnumMediaTypes::Clone */
/* ms910542 IEnumMediaTypes::Next */
/* ms910543 IEnumMediaTypes::Reset */
/* ms910544 IEnumMediaTypes::Skip */
/* ms910546 IEnumPins Interface */
/* ms910545 IEnumPins::Clone */
/* ms910547 IEnumPins::Next */
/* ms910548 IEnumPins::Reset */
/* ms910549 IEnumPins::Skip */
/* ms910551 IEnumRegFilters Interface */
/* ms910550 IEnumRegFilters::Clone */
/* ms910552 IEnumRegFilters::Next */
/* ms910553 IEnumRegFilters::Reset */
/* ms910554 IEnumRegFilters::Skip */
/* ms910557 IFileSourceFilter Interface */
/* ms910556 IFileSourceFilter::GetCurfile */
/* ms910558 IFileSourceFilter::Load */
/* ms910566 IFilterGraph Interface */
/* ms910559 IFilterGraph2 Interface */
/* ms910560 IFilterGraph2::ReconnectEx */
/* ms910561 IFilterGraph::AddFilter */
/* ms910562 IFilterGraph::ConnectDirect */
/* ms910563 IFilterGraph::Disconnect */
/* ms910564 IFilterGraph::EnumFilters */
/* ms910565 IFilterGraph::FindFilterByName */
/* ms910567 IFilterGraph::Reconnect */
/* ms910568 IFilterGraph::RemoveFilter */
/* ms910569 IFilterGraph::SetDefaultSyncSource */
/* ms910571 IFilterMapper Interface */
/* ms910570 IFilterMapper::EnumMatchingFilters */
/* ms910572 IFilterMapper::RegisterFilter */
/* ms910573 IFilterMapper::RegisterFilterInstance */
/* ms910574 IFilterMapper::RegisterPin */
/* ms910575 IFilterMapper::RegisterPinType */
/* ms910576 IFilterMapper::UnregisterFilter */
/* ms910577 IFilterMapper::UnregisterFilterInstance */
/* ms910578 IFilterMapper::UnregisterPin */
/* ms910581 IGraphBuilder Interface */
/* ms910579 IGraphBuilder::AddSourceFilter */
/* ms910580 IGraphBuilder::Connect */
/* ms910582 IGraphBuilder::Render */
/* ms910583 IGraphBuilder::RenderFile */
/* ms910584 IGraphBuilder::SetLogFile */
/* ms910585 IGraphVersion Interface */
/* ms910586 IGraphVersion::QueryVersion */
/* aa452544 IKsPropertySet Interface */
/* aa452543 IKsPropertySet::Get */
/* aa452545 IKsPropertySet::QuerySupported */
/* aa452546 IKsPropertySet::Set */
/* aa452261 IMediaControl Interface */
/* aa452259 IMediaControl::AddSourceFilter */
/* aa452260 IMediaControl::GetState */
/* aa452262 IMediaControl::Pause */
/* aa452263 IMediaControl::RenderFile */
/* aa452264 IMediaControl::Run */
/* aa452265 IMediaControl::Stop */
/* aa452266 IMediaControl::StopWhenReady */
/* aa452275 IMediaEvent Interface */
/* aa452267 IMediaEvent::CancelDefaultHandling */
/* aa452272 IMediaEvent::FreeEventParams */
/* aa452273 IMediaEvent::GetEvent */
/* aa452274 IMediaEvent::GetEventHandle */
/* aa452276 IMediaEvent::RestoreDefaultHandling */
/* aa452282 IMediaEvent::WaitForCompletion */
/* aa452269 IMediaEventEx Interface */
/* aa452268 IMediaEventEx::GetNotifyFlags */
/* aa452270 IMediaEventEx::SetNotifyFlags */
/* aa452271 IMediaEventEx::SetNotifyWindow */
/* aa452278 IMediaEventSink Interface */
/* aa452280 IMediaEventSink::Notify */
/* aa452289 IMediaFilter Interface */
/* aa452284 IMediaFilter::GetState */
/* aa452287 IMediaFilter::GetSyncSource */
/* ms931255 IMediaFilter::Pause */
/* ms931338 IMediaFilter::Run */
/* ms931385 IMediaFilter::SetSyncSource */
/* ms931389 IMediaFilter::Stop */
/* ms911576 IMediaPosition Interface */
/* ms931423 IMediaPosition::CanSeekBackward */
/* ms931424 IMediaPosition::CanSeekForward */
/* ms931425 IMediaPosition::get_CurrentPosition */
/* ms931426 IMediaPosition::get_Duration */
/* ms931427 IMediaPosition::get_PrerollTime */
/* ms911574 IMediaPosition::get_Rate */
/* ms911575 IMediaPosition::get_StopTime */
/* ms911577 IMediaPosition::put_CurrentPosition */
/* ms911578 IMediaPosition::put_PrerollTime */
/* ms911579 IMediaPosition::put_Rate */
/* ms911580 IMediaPosition::put_StopTime */
/* ms911590 IMediaSample Interface */
/* ms911582 IMediaSample2 Interface */
/* ms911581 IMediaSample2::GetProperties */
/* ms911583 IMediaSample2::SetProperties */
/* ms911584 IMediaSample::GetActualDataLength */
/* ms911585 IMediaSample::GetMediaTime */
/* ms911586 IMediaSample::GetMediaType */
/* ms911587 IMediaSample::GetPointer */
/* ms911588 IMediaSample::GetSize */
/* ms911589 IMediaSample::GetTime */
/* ms911591 IMediaSample::IsDiscontinuity */
/* ms911592 IMediaSample::IsPreroll */
/* ms911593 IMediaSample::IsSyncPoint */
/* ms911594 IMediaSample::SetActualDataLength */
/* ms911595 IMediaSample::SetDiscontinuity */
/* ms911596 IMediaSample::SetMediaTime */
/* ms911597 IMediaSample::SetMediaType */
/* ms911598 IMediaSample::SetPreroll */
/* ms911599 IMediaSample::SetSyncPoint */
/* ms911600 IMediaSample::SetTime */
/* ms911612 IMediaSeeking Interface */
/* ms911602 IMediaSeeking::ConvertTimeFormat */
/* ms911603 IMediaSeeking::GetAvailable */
/* ms911604 IMediaSeeking::GetCapabilities */
/* ms911605 IMediaSeeking::GetCurrentPosition */
/* ms911606 IMediaSeeking::GetDuration */
/* ms911607 IMediaSeeking::GetPositions */
/* ms911608 IMediaSeeking::GetPreroll */
/* ms911609 IMediaSeeking::GetRate */
/* ms911610 IMediaSeeking::GetStopPosition */
/* ms911611 IMediaSeeking::GetTimeFormat */
/* ms911613 IMediaSeeking::IsFormatSupported */
/* ms911614 IMediaSeeking::IsUsingTimeFormat */
/* ms911615 IMediaSeeking::QueryPreferredFormat */
/* ms911616 IMediaSeeking::SetPositions */
/* ms911617 IMediaSeeking::SetRate */
/* ms911618 IMediaSeeking::SetTimeFormat */
/* ms911623 IMediaStream Interface */
/* ms911619 IMediaStream::AllocateSample */
/* ms911620 IMediaStream::CreateSharedSample */
/* ms911621 IMediaStream::GetInformation */
/* ms911622 IMediaStream::GetMultiMediaStream */
/* ms911624 IMediaStream::SendEndOfStream */
/* ms911625 IMediaStream::SetSameFormat */
/* ms911630 IMemAllocator Interface */
/* ms911626 IMemAllocator::Commit */
/* ms911627 IMemAllocator::Decommit */
/* ms911628 IMemAllocator::GetBuffer */
/* ms911629 IMemAllocator::GetProperties */
/* ms911631 IMemAllocator::ReleaseBuffer */
/* ms931499 IMemAllocator::SetProperties */
/* ms931622 IMemInputPin Interface */
/* ms931604 IMemInputPin::GetAllocator */
/* ms931613 IMemInputPin::GetAllocatorRequirements */
/* ms931631 IMemInputPin::NotifyAllocator */
/* ms931640 IMemInputPin::Receive */
/* ms931649 IMemInputPin::ReceiveCanBlock */
/* ms931660 IMemInputPin::ReceiveMultiple */
/* ms911956 IMultiMediaStream Interface */
/* ms931669 IMultiMediaStream::EnumMediaStreams */
/* ms931676 IMultiMediaStream::GetDuration */
/* ms931682 IMultiMediaStream::GetEndOfStreamEventHandle */
/* ms911837 IMultiMediaStream::GetInformation */
/* ms911850 IMultiMediaStream::GetMediaStream */
/* ms911855 IMultiMediaStream::GetState */
/* ms911946 IMultiMediaStream::GetTime */
/* ms911969 IMultiMediaStream::Seek */
/* ms911980 IMultiMediaStream::SetState */
/* ms912007 INonDelegatingUnknown Interface */
/* ms911992 INonDelegatingUnknown::INonDelegatingUnknown */
/* ms912154 IOverlay Interface */
/* ms912083 IOverlay::Advise */
/* ms912095 IOverlay::GetClipList */
/* ms912107 IOverlay::GetColorKey */
/* ms912119 IOverlay::GetDefaultColorKey */
/* ms912127 IOverlay::GetPalette */
/* ms912134 IOverlay::GetVideoPosition */
/* ms912142 IOverlay::GetWindowHandle */
/* ms912211 IOverlay::SetColorKey */
/* ms912218 IOverlay::SetPalette */
/* ms912237 IOverlay::Unadvise */
/* ms912167 IOverlayNotify Interface */
/* ms912176 IOverlayNotify::OnClipChange */
/* ms912185 IOverlayNotify::OnColorKeyChange */
/* ms912194 IOverlayNotify::OnPaletteChange */
/* ms912200 IOverlayNotify::OnPositionChange */
/* ms912308 IPin Interface */
/* ms912246 IPin::BeginFlush */
/* ms912252 IPin::Connect */
/* ms912262 IPin::ConnectedTo */
/* ms912270 IPin::ConnectionMediaType */
/* ms912278 IPin::Disconnect */
/* ms912286 IPin::EndFlush */
/* ms912294 IPin::EndOfStream */
/* ms912300 IPin::EnumMediaTypes */
/* ms912310 IPin::NewSegment */
/* ms912318 IPin::QueryAccept */
/* ms912328 IPin::QueryDirection */
/* ms912337 IPin::QueryId */
/* ms912346 IPin::QueryInternalConnections */
/* ms912352 IPin::QueryPinInfo */
/* ms931694 IPin::ReceiveConnection */
/* ms931702 IQualityControl Interface */
/* ms931711 IQualityControl::Notify */
/* ms931717 IQualityControl::SetSink */
/* ms931802 IQualProp Interface */
/* ms931726 IQualProp::get_AvgFrameRate */
/* ms931785 IQualProp::get_AvgSyncOffset */
/* ms931794 IQualProp::get_DevSyncOffset */
/* ms931798 IQualProp::get_FramesDrawn */
/* ms931799 IQualProp::get_FramesDroppedInRenderer */
/* ms931801 IQualProp::get_Jitter */
/* ms931806 IReferenceClock Interface */
/* ms931803 IReferenceClock::AdvisePeriodic */
/* ms931804 IReferenceClock::AdviseTime */
/* ms931805 IReferenceClock::GetTime */
/* ms931807 IReferenceClock::Unadvise */
/* ms931811 ISeekingPassThru Interface */
/* ms931810 ISeekingPassThru::Init */
/* aa452554 IStreamBufferCapture Interface */
/* aa452547 IStreamBufferCapture::BeginPermanentRecording */
/* aa452548 IStreamBufferCapture::BeginTemporaryRecording */
/* aa452549 IStreamBufferCapture::ConvertToTemporaryRecording */
/* aa452550 IStreamBufferCapture::GetBoundToLiveToken */
/* aa452551 IStreamBufferCapture::GetCaptureMode */
/* aa452552 IStreamBufferCapture::GetCurrentPosition */
/* aa452553 IStreamBufferCapture::GetRecordingPath */
/* aa452556 IStreamBufferCapture::SetRecordingPath */
/* aa452558 IStreamBufferPlayback Interface */
/* aa452557 IStreamBufferPlayback::GetTunePolicy */
/* aa452559 IStreamBufferPlayback::NotifyGraphIsConnected */
/* aa452560 IStreamBufferPlayback::SetTunePolicy */
/* ms931816 IStreamSample Interface */
/* ms931813 IStreamSample::CompletionStatus */
/* ms931814 IStreamSample::GetMediaStream */
/* ms931815 IStreamSample::GetSampleTimes */
/* ms931817 IStreamSample::SetSampleTimes */
/* ms931818 IStreamSample::Update */
/* ms931969 IVideoWindow Interface */
/* ms931820 IVideoWindow::get_AutoShow */
/* ms931821 IVideoWindow::get_BackgroundPalette */
/* ms931822 IVideoWindow::get_BorderColor */
/* ms931823 IVideoWindow::get_Caption */
/* ms931824 IVideoWindow::get_FullScreenMode */
/* ms931825 IVideoWindow::get_Height */
/* ms931826 IVideoWindow::get_Left */
/* ms931828 IVideoWindow::get_MessageDrain */
/* ms931830 IVideoWindow::get_Owner */
/* ms931832 IVideoWindow::get_Top */
/* ms931833 IVideoWindow::get_Visible */
/* ms931834 IVideoWindow::get_Width */
/* ms912445 IVideoWindow::get_WindowState */
/* ms912561 IVideoWindow::get_WindowStyle */
/* ms931962 IVideoWindow::get_WindowStyleEx */
/* ms931827 IVideoWindow::GetMaxIdealImageSize */
/* ms931829 IVideoWindow::GetMinIdealImageSize */
/* ms931831 IVideoWindow::GetRestorePosition */
/* ms912426 IVideoWindow::GetWindowPosition */
/* ms931968 IVideoWindow::HideCursor */
/* ms931970 IVideoWindow::IsCursorHidden */
/* ms931972 IVideoWindow::NotifyOwnerMessage */
/* ms931974 IVideoWindow::put_AutoShow */
/* ms931975 IVideoWindow::put_BackgroundPalette */
/* ms931976 IVideoWindow::put_BorderColor */
/* ms931977 IVideoWindow::put_Caption */
/* ms931978 IVideoWindow::put_FullScreenMode */
/* ms931979 IVideoWindow::put_Height */
/* ms931981 IVideoWIndow::put_Left */
/* ms931982 IVideoWindow::put_MessageDrain */
/* ms931983 IVideoWindow::put_Owner */
/* ms931984 IVideoWindow::put_Top */
/* ms931985 IVideoWindow::put_Visible */
/* ms931986 IVideoWindow::put_Width */
/* ms931987 IVideoWindow::put_WindowState */
/* ms931988 IVideoWindow::put_WindowStyle */
/* ms931989 IVideoWindow::put_WindowStyleEx */
/* ms931990 IVideoWindow::SetWindowForeground */
/* ms931991 IVideoWindow::SetWindowPosition */
/* ms931998 IVPBaseConfig Interface */
/* ms931992 IVPBaseConfig::GetConnectInfo */
/* ms931993 IVPBaseConfig::GetMaxPixelRate */
/* ms931994 IVPBaseConfig::GetOverlaySurface */
/* ms931995 IVPBaseConfig::GetVideoFormats */
/* ms931996 IVPBaseConfig::GetVPDataInfo */
/* ms931997 IVPBaseConfig::InformVPInputFormats */
/* ms932001 IVPBaseConfig::SetConnectInfo */
/* ms932002 IVPBaseConfig::SetDDSurfaceKernelHandles */
/* ms932003 IVPBaseConfig::SetDirectDrawKernelHandle */
/* ms932004 IVPBaseConfig::SetInvertPolarity */
/* ms932005 IVPBaseConfig::SetSurfaceParameters */
/* ms932006 IVPBaseConfig::SetVideoFormat */
/* ms932007 IVPBaseConfig::SetVideoPortID */
/* ms932008 IVPBaseNotify Interface */
/* ms932009 IVPBaseNotify::RenegotiateVPParameters */
/* ms932010 IVPConfig Interface */
/* ms932011 IVPConfig::IsVPDecimationAllowed */
/* ms932012 IVPConfig::SetScalingFactors */
/* ms932015 IVPNotify Interface */
/* ms932013 IVPNotify::GetColorControls */
/* ms932014 IVPNotify::GetDeinterlaceMode */
/* ms932016 IVPNotify::SetColorControls */
/* ms932017 IVPNotify::SetDeinterlaceMode */
/* ------------------------------------------------------------------
 * Book surface: dshow-iface (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452506 IAMTuner Interface (Header: strmif.h.) */
/* aa452500 IAMTuner::ChannelMinMax (Header: strmif.h.) */
/* aa452502 IAMTuner::get_Channel (Header: strmif.h.) */
/* aa452503 IAMTuner::get_CountryCode (Header: strmif.h.) */
/* aa452504 IAMTuner::get_Mode (Header: strmif.h.) */
/* aa452505 IAMTuner::get_TuningSpace (Header: strmif.h.) */
/* aa452501 IAMTuner::GetAvailableModes (Header: strmif.h.) */
/* aa452507 IAMTuner::Logon (Header: strmif.h.) */
/* aa452508 IAMTuner::Logout (Header: strmif.h.) */
/* aa452509 IAMTuner::put_Channel (Header: strmif.h.) */
/* aa452510 IAMTuner::put_CountryCode (Header: strmif.h.) */
/* aa452511 IAMTuner::put_Mode (Header: strmif.h.) */
/* aa452512 IAMTuner::put_TuningSpace (Header: strmif.h.) */
/* aa452513 IAMTuner::RegisterNotificationCallBack (Header: strmif.h.) */
/* aa452514 IAMTuner::SignalPresent (Header: strmif.h.) */
/* aa452515 IAMTuner::UnRegisterNotificationCallBack (Header: strmif.h.) */
/* aa452524 IAMTVTuner Interface (Header: strmif.h.) */
/* aa452524 IAMTVTuner Interface (Header: strmif.h.) */
/* aa452516 IAMTVTuner::AutoTune (Header: strmif.h.) */
/* aa452517 IAMTVTuner::get_AudioFrequency (Header: strmif.h.) */
/* aa452518 IAMTVTuner::get_AvailableTVFormats (Header: strmif.h.) */
/* aa452519 IAMTVTuner::get_ConnectInput (Header: strmif.h.) */
/* aa452520 IAMTVTuner::get_InputType (Header: strmif.h.) */
/* aa452521 IAMTVTuner::get_NumInputConnections (Header: strmif.h.) */
/* aa452522 IAMTVTuner::get_TVFormat (Header: strmif.h.) */
/* aa452523 IAMTVTuner::get_VideoFrequency (Header: strmif.h.) */
/* aa452525 IAMTVTuner::put_ConnectInput (Header: strmif.h.) */
/* aa452526 IAMTVTuner::put_InputType (Header: strmif.h.) */
/* aa452527 IAMTVTuner::StoreAutoTune (Header: strmif.h.) */

