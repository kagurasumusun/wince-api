/* Oaidl.h -- documented-case alias for Objbase.h.
 * The Automation/COM type pages print Header: Oaidl.h (Oaidl.h,
 * Oaidl.idl -- 164 rows in the harvest: VARIANT, TYPEDESC, FUNCDESC,
 * CALLCONV, DESCKIND, ... plus the PropVariant* functions); the
 * type surface is carried by Objbase.h in this tree.  See
 * docs/inventory.md M73a. */
#include "Objbase.h"/* ------------------------------------------------------------------
 * Book surface: dcom-aut (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms880205 ICreateErrorInfo::SetDescription (Header: Oaidl.h, Oaidl.idl.) */
/* ms880208 ICreateErrorInfo::SetGUID (Header: Oaidl.h, Oaidl.idl.) */
/* ms880214 ICreateErrorInfo::SetHelpContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880219 ICreateErrorInfo::SetHelpFile (Header: Oaidl.h, Oaidl.idl.) */
/* ms880226 ICreateErrorInfo::SetSource (Header: Oaidl.h, Oaidl.idl.) */
/* ms880230 ICreateTypeInfo2::DeleteFuncDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms880237 ICreateTypeInfo2::DeleteFuncDescByMemId (Header: Oaidl.h, Oaidl.idl.) */
/* ms880241 ICreateTypeInfo2::DeleteImplType (Header: Oaidl.h, Oaidl.idl.) */
/* ms880247 ICreateTypeInfo2::DeleteVarDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms880252 ICreateTypeInfo2::DeleteVarDescByMemId (Header: Oaidl.h, Oaidl.idl.) */
/* ms880260 ICreateTypeInfo2::SetCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms880265 ICreateTypeInfo2::SetFuncCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms880271 ICreateTypeInfo2::SetFuncHelpStringContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880272 ICreateTypeInfo2::SetHelpStringContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880280 ICreateTypeInfo2::SetImplTypeCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms880288 ICreateTypeInfo2::SetName (Header: Oaidl.h, Oaidl.idl.) */
/* ms880290 ICreateTypeInfo2::SetParamCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms880295 ICreateTypeInfo2::SetVarCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms880371 ICreateTypeInfo2::SetVarHelpStringContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880379 ICreateTypeInfo::AddFuncDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms880384 ICreateTypeInfo::AddImplType (Header: Oaidl.h, Oaidl.idl.) */
/* ms880385 ICreateTypeInfo::AddRefTypeInfo (Header: Oaidl.h, Oaidl.idl.) */
/* ms880386 ICreateTypeInfo::AddVarDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms880387 ICreateTypeInfo::DefineFuncAsDllEntry (Header: Oaidl.h, Oaidl.idl.) */
/* ms880388 ICreateTypeInfo::LayOut (Header: Oaidl.h, Oaidl.idl.) */
/* ms880389 ICreateTypeInfo::SetAlignment (Header: Oaidl.h, Oaidl.idl.) */
/* ms880390 ICreateTypeInfo::SetDocString (Header: Oaidl.h, Oaidl.idl.) */
/* ms880393 ICreateTypeInfo::SetFuncAndParamNames (Header: Oaidl.h, Oaidl.idl.) */
/* ms880394 ICreateTypeInfo::SetFuncDocString (Header: Oaidl.h, Oaidl.idl.) */
/* ms880395 ICreateTypeInfo::SetFuncHelpContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880396 ICreateTypeInfo::SetGuid (Header: Oaidl.h, Oaidl.idl.) */
/* ms880397 ICreateTypeInfo::SetHelpContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880398 ICreateTypeInfo::SetImplTypeFlags (Header: Oaidl.h, Oaidl.idl.) */
/* ms880399 ICreateTypeInfo::SetMops (Header: Oaidl.h, Oaidl.idl.) */
/* ms880400 ICreateTypeInfo::SetTypeDescAlias (Header: Oaidl.h, Oaidl.idl.) */
/* ms880401 ICreateTypeInfo::SetTypeFlags (Header: Oaidl.h, Oaidl.idl.) */
/* ms880402 ICreateTypeInfo::SetVarDocString (Header: Oaidl.h, Oaidl.idl.) */
/* ms880403 ICreateTypeInfo::SetVarHelpContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880404 ICreateTypeInfo::SetVarName (Header: Oaidl.h, Oaidl.idl.) */
/* ms880405 ICreateTypeInfo::SetVersion (Header: Oaidl.h, Oaidl.idl.) */
/* ms880407 ICreateTypeLib2::DeleteTypeInfo (Header: Oaidl.h, Oaidl.idl.) */
/* ms880409 ICreateTypeLib2::SetCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms880410 ICreateTypeLib2::SetHelpStringContext (Header: Oaidl.h, Oaidl.idl.) */
/* ms880411 ICreateTypeLib2::SetHelpStringDll (Header: Oaidl.h, Oaidl.idl.) */
/* aa515505 ICreateTypeLib::CreateTypeInfo (Header: Oaidl.h, Oaidl.idl.) */
/* aa515506 ICreateTypeLib::SetGuid (Header: Oaidl.h, Oaidl.idl.) */
/* aa515528 ICreateTypeLib::SetHelpContext (Header: Oaidl.h, Oaidl.idl.) */
/* aa515529 ICreateTypeLib::SetHelpFileName (Header: Oaidl.h, Oaidl.idl.) */
/* aa515530 ICreateTypeLib::SetLcid (Header: Oaidl.h, Oaidl.idl.) */
/* aa515531 ICreateTypeLib::SetLibFlags (Header: Oaidl.h, Oaidl.idl.) */
/* aa515532 ICreateTypeLib::SetName (Header: Oaidl.h, Oaidl.idl.) */
/* aa515533 ICreateTypeLib::SetVersion (Header: Oaidl.h, Oaidl.idl.) */
/* aa515582 IDispatch::GetIDsOfNames (Header: Oaidl.h, Oaidl.idl.) */
/* aa515584 IDispatch::GetTypeInfo (Header: Oaidl.h, Oaidl.idl.) */
/* aa515585 IDispatch::GetTypeInfoCount (Header: Oaidl.h, Oaidl.idl.) */
/* aa515589 IDispatch::Invoke (Header: Oaidl.h, Oaidl.idl.) */
/* aa515685 IEnumVARIANT::Clone (Header: Oaidl.h, Oaidl.idl.) */
/* aa515688 IEnumVARIANT::Next (Header: Oaidl.h, Oaidl.idl.) */
/* aa515691 IEnumVARIANT::Reset (Header: Oaidl.h, Oaidl.idl.) */
/* aa515694 IEnumVARIANT::Skip (Header: Oaidl.h, Oaidl.idl.) */
/* aa515702 IErrorInfo::GetDescription (Header: Oaidl.h, Oaidl.idl.) */
/* aa515705 IErrorInfo::GetGUID (Header: Oaidl.h, Oaidl.idl.) */
/* aa515706 IErrorInfo::GetHelpContext (Header: Oaidl.h, Oaidl.idl.) */
/* aa515707 IErrorInfo::GetHelpFile (Header: Oaidl.h, Oaidl.idl.) */
/* aa515708 IErrorInfo::GetSource (Header: Oaidl.h, Oaidl.idl.) */
/* ms890756 ISupportErrorInfo::InterfaceSupportsErrorInfo (Header: Oaidl.h, Oaidl.idl.) */
/* ms890890 ITypeComp::Bind (Header: Oaidl.h, Oaidl.idl.) */
/* ms890896 ITypeComp::BindType (Header: Oaidl.h, Oaidl.idl.) */
/* ms890921 ITypeInfo2::GetAllCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890930 ITypeInfo2::GetAllFuncCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890936 ITypeInfo2::GetAllImplTypeCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890945 ITypeInfo2::GetAllParamCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890954 ITypeInfo2::GetAllVarCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890962 ITypeInfo2::GetCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890971 ITypeInfo2::GetDocumentation2 (Header: Oaidl.h, Oaidl.idl.) */
/* ms890980 ITypeInfo2::GetFuncCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms890986 ITypeInfo2::GetFuncIndexOfMemId (Header: Oaidl.h, Oaidl.idl.) */
/* ms890994 ITypeInfo2::GetImplTypeCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms891006 ITypeInfo2::GetParamCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms891010 ITypeInfo2::GetTypeFlags (Header: Oaidl.h, Oaidl.idl.) */
/* ms891019 ITypeInfo2::GetTypeKind (Header: Oaidl.h, Oaidl.idl.) */
/* ms891027 ITypeInfo2::GetVarCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms891032 ITypeInfo2::GetVarIndexOfMemId (Header: Oaidl.h, Oaidl.idl.) */
/* ms891040 ITypeInfo::AddressOfMember (Header: Oaidl.h, Oaidl.idl.) */
/* ms891048 ITypeInfo::CreateInstance (Header: Oaidl.h, Oaidl.idl.) */
/* ms891056 ITypeInfo::GetContainingTypeLib (Header: Oaidl.h, Oaidl.idl.) */
/* ms891065 ITypeInfo::GetDllEntry (Header: Oaidl.h, Oaidl.idl.) */
/* ms891070 ITypeInfo::GetDocumentation (Header: Oaidl.h, Oaidl.idl.) */
/* ms891080 ITypeInfo::GetFuncDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms891088 ITypeInfo::GetIDsOfNames (Header: Oaidl.h, Oaidl.idl.) */
/* ms891098 ITypeInfo::GetImplTypeFlags (Header: Oaidl.h, Oaidl.idl.) */
/* ms891106 ITypeInfo::GetMops (Header: Oaidl.h, Oaidl.idl.) */
/* ms891123 ITypeInfo::GetNames (Header: Oaidl.h, Oaidl.idl.) */
/* ms891131 ITypeInfo::GetRefTypeInfo (Header: Oaidl.h, Oaidl.idl.) */
/* ms891140 ITypeInfo::GetRefTypeOfImplType (Header: Oaidl.h, Oaidl.idl.) */
/* ms891249 ITypeInfo::GetTypeAttr (Header: Oaidl.h, Oaidl.idl.) */
/* ms891334 ITypeInfo::GetTypeComp (Header: Oaidl.h, Oaidl.idl.) */
/* ms891338 ITypeInfo::GetVarDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms891343 ITypeInfo::Invoke (Header: Oaidl.h, Oaidl.idl.) */
/* ms891345 ITypeInfo::ReleaseFuncDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms891352 ITypeInfo::ReleaseTypeAttr (Header: Oaidl.h, Oaidl.idl.) */
/* ms891356 ITypeInfo::ReleaseVarDesc (Header: Oaidl.h, Oaidl.idl.) */
/* ms891365 ITypeLib2::GetAllCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms891369 ITypeLib2::GetCustData (Header: Oaidl.h, Oaidl.idl.) */
/* ms891374 ITypeLib2::GetDocumentation2 (Header: Oaidl.h, Oaidl.idl.) */
/* ms891478 ITypeLib2::GetLibStatistics (Header: Oaidl.h, Oaidl.idl.) */
/* ms891489 ITypeLib::FindName (Header: Oaidl.h, Oaidl.idl.) */
/* ms891492 ITypeLib::GetDocumentation (Header: Oaidl.h, Oaidl.idl.) */
/* ms891497 ITypeLib::GetLibAttr (Header: Oaidl.h, Oaidl.idl.) */
/* ms891502 ITypeLib::GetTypeComp (Header: Oaidl.h, Oaidl.idl.) */
/* ms891508 ITypeLib::GetTypeInfo (Header: Oaidl.h, Oaidl.idl.) */
/* ms891513 ITypeLib::GetTypeInfoCount (Header: Oaidl.h, Oaidl.idl.) */
/* ms891517 ITypeLib::GetTypeInfoOfGuid (Header: Oaidl.h, Oaidl.idl.) */
/* ms891521 ITypeLib::GetTypeInfoType (Header: Oaidl.h, Oaidl.idl.) */
/* ms891529 ITypeLib::IsName (Header: Oaidl.h, Oaidl.idl.) */
/* ms891535 ITypeLib::ReleaseTLibAttr (Header: Oaidl.h, Oaidl.idl.) */
/* aa519089 VARIANT and VARIANTARG (Header: Oaidl.h.) */
/* ------------------------------------------------------------------
 * Book surface: dcom-aut (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa513563 Automation Data Types */
/* aa513565 Automation Enumerations */
/* aa513569 Automation Functions */
/* aa513587 Automation Interfaces */
/* aa513603 Automation Structures */
/* ms864424 dispinterface */
/* ------------------------------------------------------------------
 * Book surface: dcom-com (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa515710 IErrorlog::AddError (Header: Oaidl.h, Oaidl.idl.) */

