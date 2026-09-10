/* Oleidl.h -- documented-case alias for Objbase.h.
 * The COM and DCOM Reference pages print Header: Oleidl.h (72 rows) or
 * the lowercase spelling oleidl.h (17 rows): the OLE container/object
 * surface (IOleObject, IOleClientSite, OLEVERB, OLEUPDATE, ...) is
 * carried by Objbase.h (M73b). */
#include "Objbase.h"/* ------------------------------------------------------------------
 * Book surface: dcom-com (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms882901 IOleLink::BindIfRunning (Header: Oleidl.h, Oleidl.idl.) */
/* ms882902 IOleLink::BindToSource (Header: Oleidl.h, Oleidl.idl.) */
/* ms882903 IOleLink::GetBoundSource (Header: Oleidl.h, Oleidl.idl.) */
/* ms882904 IOleLink::GetSourceDisplayName (Header: Oleidl.h, Oleidl.idl.) */
/* ms882905 IOleLink::GetSourceMoniker (Header: Oleidl.h, Oleidl.idl.) */
/* ms882906 IOleLink::GetUpdateOptions (Header: Oleidl.h, Oleidl.idl.) */
/* ms882908 IOleLink::SetSourceDisplayName (Header: Oleidl.h, Oleidl.idl.) */
/* ms882909 IOleLink::SetSourceMoniker (Header: Oleidl.h, Oleidl.idl.) */
/* ms882910 IOleLink::SetUpdateOptions (Header: Oleidl.h, Oleidl.idl.) */
/* ms882911 IOleLink::UnbindSource (Header: Oleidl.h, Oleidl.idl.) */
/* ms882912 IOleLink::Update (Header: Oleidl.h, Oleidl.idl.) */
/* ms882936 IParseDisplayName::ParseDisplayName (Header: Oleidl.h, Oleidl.idl.) */
/* ms891559 IViewObject2::GetExtent (Header: Oleidl.h, Oleidl.idl.) */
/* ------------------------------------------------------------------
 * Book surface: dcom-ole (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa515631 IEnumOLEVERB::Clone (Header: Oleidl.h, Oleidl.idl.) */
/* aa515635 IEnumOLEVERB::Next (Header: Oleidl.h, Oleidl.idl.) */
/* aa515636 IEnumOLEVERB::Reset (Header: Oleidl.h, Oleidl.idl.) */
/* aa515638 IEnumOLEVERB::Skip (Header: Oleidl.h, Oleidl.idl.) */
/* ms882882 IOleAdviseHolder::Advise (Header: Oleidl.h, Oleidl.idl.) */
/* ms882883 IOleAdviseHolder::EnumAdvise (Header: Oleidl.h, Oleidl.idl.) */
/* ms882885 IOleAdviseHolder::SendOnClose (Header: Oleidl.h, Oleidl.idl.) */
/* ms882886 IOleAdviseHolder::SendOnRename (Header: Oleidl.h, Oleidl.idl.) */
/* ms882887 IOleAdviseHolder::SendOnSave (Header: Oleidl.h, Oleidl.idl.) */
/* ms882889 IOleAdviseHolder::Unadvise (Header: Oleidl.h, Oleidl.idl.) */
/* ms882890 IOleClientSite::GetContainer (Header: Oleidl.h, Oleidl.idl.) */
/* ms882891 IOleClientSite::GetMoniker (Header: Oleidl.h, Oleidl.idl.) */
/* ms882893 IOleClientSite::OnShowWindow (Header: Oleidl.h, Oleidl.idl.) */
/* ms882894 IOleClientSite::RequestNewObjectLayout (Header: Oleidl.h, Oleidl.idl.) */
/* ms882895 IOleClientSite::SaveObject (Header: Oleidl.h, Oleidl.idl.) */
/* ms882896 IOleClientSite::ShowObject (Header: Oleidl.h, Oleidl.idl.) */
/* aa519256 IOleContainer::EnumObjects (Header: oleidl.h.) */
/* aa519258 IOleContainer::LockContainer (Header: oleidl.h.) */
/* aa519268 IOleInPlaceSite::CanInPlaceActivate (Header: oleidl.h.) */
/* aa519269 IOleInPlaceSite::DeactivateAndUndo (Header: oleidl.h.) */
/* aa519270 IOleInPlaceSite::DiscardUndoState (Header: oleidl.h.) */
/* aa519271 IOleInPlaceSite::GetWindowContext (Header: oleidl.h.) */
/* aa519273 IOleInPlaceSite::OnInPlaceActivate (Header: oleidl.h.) */
/* aa519274 IOleInPlaceSite::OnInPlaceDeactivate (Header: oleidl.h.) */
/* aa519275 IOleInPlaceSite::OnPosRectChange (Header: oleidl.h.) */
/* aa519276 IOleInPlaceSite::OnUIActivate (Header: oleidl.h.) */
/* aa519277 IOleInPlaceSite::OnUIDeactivate (Header: oleidl.h.) */
/* aa519278 IOleInPlaceSite::Scroll (Header: oleidl.h.) */
/* ms882913 IOleObject::Advise (Header: Oleidl.h, Oleidl.idl.) */
/* ms882914 IOleObject::Close (Header: Oleidl.h, Oleidl.idl.) */
/* ms882915 IOleObject::DoVerb (Header: Oleidl.h, Oleidl.idl.) */
/* ms882916 IOleObject::EnumAdvise (Header: Oleidl.h, Oleidl.idl.) */
/* ms882917 IOleObject::EnumVerbs (Header: Oleidl.h, Oleidl.idl.) */
/* ms882918 IOleObject::GetClientSite (Header: Oleidl.h, Oleidl.idl.) */
/* ms882919 IOleObject::GetClipboardData (Header: Oleidl.h, Oleidl.idl.) */
/* ms882920 IOleObject::GetExtent (Header: Oleidl.h, Oleidl.idl.) */
/* ms882921 IOleObject::GetMiscStatus (Header: Oleidl.h, Oleidl.idl.) */
/* ms882922 IOleObject::GetMoniker (Header: Oleidl.h, Oleidl.idl.) */
/* ms882923 IOleObject::GetUserClassID (Header: Oleidl.h, Oleidl.idl.) */
/* ms882924 IOleObject::GetUserType (Header: Oleidl.h, Oleidl.idl.) */
/* ms882925 IOleObject::InitFromData (Header: Oleidl.h, Oleidl.idl.) */
/* ms882926 IOleObject::IsUpToDate (Header: Oleidl.h, Oleidl.idl.) */
/* ms882928 IOleObject::SetClientSite (Header: Oleidl.h, Oleidl.idl.) */
/* ms882929 IOleObject::SetColorScheme (Header: Oleidl.h, Oleidl.idl.) */
/* ms882930 IOleObject::SetExtent (Header: Oleidl.h, Oleidl.idl.) */
/* ms882931 IOleObject::SetHostNames (Header: Oleidl.h, Oleidl.idl.) */
/* ms882932 IOleObject::SetMoniker (Header: Oleidl.h, Oleidl.idl.) */
/* ms882933 IOleObject::Unadvise (Header: Oleidl.h, Oleidl.idl.) */
/* ms882934 IOleObject::Update (Header: Oleidl.h, Oleidl.idl.) */
/* aa519279 IOleWindow::ContextSensitiveHelp (Header: oleidl.h.) */
/* aa519280 IOleWindow::GetWindow (Header: oleidl.h.) */
/* ms891568 IViewObject::Draw (Header: Oleidl.h, Oleidl.idl.) */
/* ms891597 IViewObject::Freeze (Header: Oleidl.h, Oleidl.idl.) */
/* ms891602 IViewObject::GetAdvise (Header: Oleidl.h, Oleidl.idl.) */
/* ms891695 IViewObject::GetColorSet (Header: Oleidl.h, Oleidl.idl.) */
/* ms891709 IViewObject::SetAdvise (Header: Oleidl.h, Oleidl.idl.) */
/* ms891710 IViewObject::Unfreeze (Header: Oleidl.h, Oleidl.idl.) */

