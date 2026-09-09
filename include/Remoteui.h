/* Remoteui.h -- Remote UI modules (Windows CE; pages print Header
 * "Remoteui.h, Remoteui.idl" with Link Library Uuid.lib -- COM
 * interfaces, recorded verbatim, not compiled).
 * See docs/inventory.md M77c. */

#ifndef AKARI_REMOTEUI_H
#define AKARI_REMOTEUI_H

typedef struct IRemoteUIModule IRemoteUIModule;
typedef struct IRemoteUI_Array IRemoteUI_Array;
typedef struct IVariableContainer IVariableContainer;

/* IRemoteUIModule (aa450462):
 *   aa450463 IRemoteUIModule::Get : HRESULT Get( BOOL fForBackup, IVariableContainer* pToServer);
 *   aa450464 IRemoteUIModule::Init : HRESULT Init( const char* pInitArgs);
 *   aa450465 IRemoteUIModule::ModuleName : HRESULT ModuleName ( char** pModuleName);
 *   aa450466 IRemoteUIModule::NeedHTTPDRestart : HRESULT NeedHTTPDRestart( BOOL* pVal);
 *   aa450467 IRemoteUIModule::NeedNetworkRestart : HRESULT NeedNetworkRestart( BOOL* pVal);
 *   aa450468 IRemoteUIModule::Put : HRESULT Put( BOOL fForRestore, IVariableContainer* pFromServer, IVariableContainer* pReturn);
 *   aa450469 IRemoteUIModule::Reset : HRESULT Reset();
 */

/* IRemoteUI_Array (aa450470):
 *   aa450471 IRemoteUI_Array::AddValue : HRESULT AddValue( const char* pIndex, VARIANT* pValue);
 *   aa450472 IRemoteUI_Array::FindFirstVar : HRESULT FindFirstVar( char** pIndex, VARIANT** pValue);
 *   aa450473 IRemoteUI_Array::FindNextVar : HRESULT FindNextVar( char** pIndex, VARIANT** pValue);
 *   aa450474 IRemoteUI_Array::GetName : HRESULT GetName( char** pName);
 *   aa450475 IRemoteUI_Array::GetValue : HRESULT GetValue( const char* pIndex, VARIANT** pValue);
 */

/* IVariableContainer (ms893259):
 *   ms893266 IVariableContainer::AddArray : HRESULT AddArray( const char* pName, IRemoteUI_Array** pArray);
 *   ms893272 IVariableContainer::AddValue : HRESULT AddValue( const char* pName, VARIANT* pValue);
 *   ms893275 IVariableContainer::FindFirstArray : HRESULT FindFirstArray( IRemoteUI_Array** pArray);
 *   ms893281 IVariableContainer::FindFirstVar : HRESULT FindFirstVar( char** pName, VARIANT** pValue);
 *   ms893287 IVariableContainer::FindNextArray : HRESULT FindNextArray( IRemoteUI_Array** pArray);
 *   ms893292 IVariableContainer::FindNextVar : HRESULT FindNextVar( char** pName, VARIANT** pValue);
 *   ms893301 IVariableContainer::GetArray : (no print)
 *   ms893305 IVariableContainer::GetValue : HRESULT GetValue( const char* pName, VARIANT** pValue);
 */

#endif /* AKARI_REMOTEUI_H */
