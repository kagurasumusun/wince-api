/*
 * Pimstore.h -- Pocket Outlook Object Model (POOM) constants, the
 * menu add-in entry point and COM interface records for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs; Applications and Services Development > Pocket Outlook Object
 * Model (POOM) book, 90 leaves harvested under tools/manifests/
 * poom.manifest, M65).
 *
 * The CE POOM is a C++ COM API (CoCreateInstance with CLSID_Application,
 * Pimstore.h, Pimstore.lib, CE 2.0+).  No page publishes a vtable
 * layout, so -- following the M44 objbase.h interface-record policy --
 * each interface is carried as an opaque forward declaration plus
 * verbatim method/accessor signature records (the property tables are
 * printed "Properties in Vtable Order"; the method pages are separate,
 * so the full vtable interleaving is NOT published and no vtable is
 * invented).  The one free function, CePimCommand, is a menu add-in
 * entry point that the ADD-IN DLL must define and expose (ms863874:
 * "The dynamic-link library (DLL) that supports the menu add-in must
 * define and expose this function") -- a user-side export, not an
 * import, so no import-library def is derived (the waveInProc/waveOutProc
 * callback decision, M63).
 *
 * Archive-print traps recorded verbatim: eaten parameter-type spaces
 * (BSTRpwszName / DATEdate / intiIndex / VARIANT_BOOLfDisplayUI /
 * VARIANT_BOOLfDescending), the eaten asterisk in "void pReserved"
 * (CePimCommand), the doc's own misspellings ITask ClearReccurencePattern
 * and GetRecurrence (title GetRecurrencePattern, aa515363/aa590827-era
 * prints), and the misspelled interface names in accessor prints
 * (Irecipients / Iexceptions / Iappointment).
 */

#ifndef AKARI_PIMSTORE_H
#define AKARI_PIMSTORE_H

#include "Windef.h"    /* HWND, HANDLE, UINT, void */
#include "Objbase.h"   /* BSTR, VARIANT_BOOL, DATE, IDispatch record use */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* ms863874 "CePimCommand" (Windows CE 2.0 and later; Pimstore.h;      */
/* Pimstore.lib).  Menu add-in entry point for the Contacts/Calendar/  */
/* Tasks Tools menu; the add-in DLL defines and exposes it (user-side  */
/* export -- no import def).  The print's "void pReserved" has an      */
/* eaten asterisk; recorded as printed with the correction noted.      */
/* ------------------------------------------------------------------ */
typedef void (*PFNCEPIMCOMMAND)(HWND hWnd, int ptData, UINT uDataCount,
                                HANDLE *rghData, void *pReserved);

/* PIMTYPE enumeration -- printed verbatim on ms863874 with values
 * (primary definition; the page also notes that on the Palm-sized PC
 * 1.2 the constants are ordered differently -- PT_CONTACT = 0,
 * PT_CALENDAR, PT_TASKS -- recorded here, not defined twice):
 *   typedef enum tagPIMTYPE { PT_CALENDAR = 0, PT_TASKS, PT_CONTACT }
 *   PIMTYPE;                                                          */
typedef enum tagPIMTYPE {
    PT_CALENDAR = 0,
    PT_TASKS    = 1,
    PT_CONTACT  = 2
} PIMTYPE;

/* CePimCommand prototype (ms863874; Pimstore.h).  The pReserved
 * parameter prints "void pReserved" (asterisk eaten by the archive
 * print); it is a reserved parameter, currently NULL. */
void CePimCommand(HWND hWnd, PIMTYPE ptData, UINT uDataCount,
                  HANDLE *rghData, void *pReserved);

/* ------------------------------------------------------------------ */
/* aa513746 "Pocket Outlook Object Model Constants" (Windows CE 2.0     */
/* and later; Pimstore.h) -- every value printed on the page.          */
/* ------------------------------------------------------------------ */

/* Task Priorities */
#define olImportanceLow       0
#define olImportanceNormal    1
#define olImportanceHigh      2

/* Folder types */
#define olFolderCalendar      9
#define olFolderContacts     10
#define olFolderTasks        13
#define olFolderInfrared    102

/* Item types */
#define olAppointmentItem     1
#define olContactItem         2
#define olTaskItem            3

/* Recurrence Types */
#define olRecursDaily         0
#define olRecursWeekly        1
#define olRecursMonthly       2
#define olRecursMonthNth      3
#define olRecursYearly        5
#define olRecursYearNth       6

/* Days of Week */
#define olSunday              1
#define olMonday              2
#define olTuesday             4
#define olWednesday           8
#define olThursday           16
#define olFriday             32
#define olSaturday           64

/* Reminder Options */
#define olLED                 1
#define olVibrate             2
#define olDialog              4
#define olSound               8
#define olRepeat             16

/* Busy Status */
#define olFree                0
#define olTentative           1
#define olBusy                2
#define olOutOfOffice         3

/* Sensitivity */
#define olNormal              0
#define olPrivate             2

/* Meeting Status */
#define olNonMeeting          0
#define olMeeting             1

/* ------------------------------------------------------------------ */
/* POOM interfaces (aa513748 lists 13).  Opaque forward declarations   */
/* (M44 objbase.h policy: the docs publish method/accessor            */
/* signatures, never vtable layouts).                                 */
/* ------------------------------------------------------------------ */
typedef struct IPOutlookApp           IPOutlookApp;
typedef struct IAppointment           IAppointment;
typedef struct IContact               IContact;
typedef struct ITask                  ITask;
typedef struct IRecurrencePattern     IRecurrencePattern;
typedef struct IException             IException;
typedef struct IExceptions            IExceptions;
typedef struct IFolder                IFolder;
typedef struct IPOutlookItemCollection IPOutlookItemCollection;
typedef struct IPOlRecipient          IPOlRecipient;
typedef struct IRecipient             IRecipient;
typedef struct IRecipients            IRecipients;
typedef struct ITimeZone              ITimeZone;

/* Auxiliary names that appear inside the published signatures or the
 * Logon example but have no CE 5.0 POOM page of their own (recorded,
 * not declared): IDispatch (Add/CreateItem/Find out-parameters and
 * AddItemToInfraredFolder in-parameter), CEOID (GetItemFromOid
 * ms883912), CEBLOB (BodyInk accessors), IAppointmentItem (the
 * GetOccurrence print ms884582), CLSID_Application and
 * IID_IPOutlookApp (the Logon example ms883962; GUID values are not
 * published).  IPOlRecipient is documented as "derived from
 * IRecipient" (aa513748). */

/* IPOutlookApp: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IPOutlookApp properties (2 accessors):
 *   HRESULT get_Version ([out] BSTR *pbstrVersion);
 *   HRESULT get_OutlookCompatible ([out] VARIANT_BOOL *pbOutlookCompatible);
 *
 * IPOutlookApp methods (9 pages):
 *   ms883892 CreateItem: HRESULT CreateItem(int olItem,IDispatch** ppolItem);
 *   ms883903 GetDefaultFolder: HRESULT GetDefaultFolder(int olFolder,IFolder** ppIFolder);
 *   ms883912 GetItemFromOid: HRESULT GetItemFromOid(CEOID oid,IDispatch** ppolItem);
 *   ms883922 GetTimeZoneFromIndex: HRESULT GetTimeZoneFromIndex(int iIndex,ITimeZone** ppTimeZone);
 *   ms883930 GetTimeZoneInformationFromIndex: HRESULT GetTimeZoneInformationFromIndex(int iIndex,TIME_ZONE_INFORMATION* ptz);
 *   ms883952 Logoff: HRESULT Logoff ();
 *   ms883962 Logon: HRESULT Logon(long hWnd);
 *   ms883983 ReceiveFromInfrared: HRESULT ReceiveFromInfrared ();
 *   ms884055 SysFreeString: HRESULT SysFreeString(BSTR bstr);
 */

/* IAppointment: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IAppointment properties (35 accessors):
 *   HRESULT get_Subject ([out] BSTR *pbstrSubject);
 *   HRESULT put_Subject ([in] BSTR bstrSubject);
 *   HRESULT get_Location ([out] BSTR *pbstrLocation);
 *   HRESULT put_Location ([in] BSTR bstrLocation);
 *   HRESULT get_Categories ([out] BSTR *pbstrCategories);
 *   HRESULT put_Categories ([in] BSTR bstrCategories);
 *   HRESULT get_Start ([out] DATE *pdaStart);
 *   HRESULT put_Start ([in] DATE daStart);
 *   HRESULT get_Duration ([out] long *plDuration);
 *   HRESULT put_Duration ([in] long lDuration);
 *   HRESULT get_End ([out] DATE *pdaEnd);
 *   HRESULT put_End ([in] DATE daEnd);
 *   HRESULT get_AllDayEvent ([out] VARIANT_BOOL *pbAllDayEvent);
 *   HRESULT put_AllDayEvent ([in] VARIANT_BOOL bAllDayEvent);
 *   HRESULT get_IsRecurring ([out] VARIANT_BOOL *pbIsRecurring);
 *   HRESULT get_MeetingStatus ([out] long *plMeetingStatus);
 *   HRESULT get_Sensitivity ([out] long *plSensitivity);
 *   HRESULT put_Sensitivity ([in] long lSensitivity);
 *   HRESULT get_BusyStatus ([out] long *plBusyStatus);
 *   HRESULT put_BusyStatus ([in] long lBusyStatus);
 *   HRESULT get_ReminderSet ([out] VARIANT_BOOL *pbReminderSet);
 *   HRESULT put_ReminderSet ([in] VARIANT_BOOL bReminderSet);
 *   HRESULT get_ReminderSoundFile ([out] BSTR *pbstrReminderSoundFile);
 *   HRESULT put_ReminderSoundFile ([in] BSTR bstrReminderSoundFile);
 *   HRESULT get_ReminderOptions ([out] long *plReminderOptions);
 *   HRESULT put_ReminderOptions ([in] long lReminderOptions);
 *   HRESULT get_ReminderMinutesBeforeStart ([out] long *plReminderMinutesBeforeStart);
 *   HRESULT put_ReminderMinutesBeforeStart ([in] long lReminderMinutesBeforeStart);
 *   HRESULT get_Recipients ([out] Irecipients **ppRecipients);
 *   HRESULT get_Body ([out] BSTR *pbstrBody);
 *   HRESULT put_Body ([in] BSTR bstrBody);
 *   HRESULT get_BodyInk ([out] CEBLOB **ppBodyInk);
 *   HRESULT put_BodyInk ([in] CEBLOB *pBodyInk);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *   HRESULT get_Oid ([out] long *plOid);
 *
 * IAppointment methods (7 pages):
 *   aa515347 Cancel: HRESULT Cancel ();
 *   aa515349 ClearRecurrencePattern: HRESULT ClearRecurrencePattern ();
 *   aa515351 Copy: HRESULT Copy(IAppointment** ppolItem);
 *   aa515355 Delete: HRESULT Delete ();
 *   aa515357 GetRecurrencePattern: HRESULT GetRecurrencePattern(IRecurrencePattern* pRec);
 *   aa515363 Save: HRESULT Save ();
 *   aa515365 Send: HRESULT Send ();
 */

/* IContact: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IContact properties (104 accessors):
 *   HRESULT get_Anniversary ([out] DATE *pdaAnniversary);
 *   HRESULT put_Anniversary ([in] DATE daAnniversary);
 *   HRESULT get_Birthday ([out] DATE *pdaBirthday);
 *   HRESULT put_Birthday ([in] DATE daBirthday);
 *   HRESULT get_BusinessFaxNumber ([out] BSTR *pbstrBusinessFaxNumber);
 *   HRESULT put_BusinessFaxNumber ([in] BSTR bstrBusinessFaxNumber);
 *   HRESULT get_CompanyName ([out] BSTR *pbstrCompanyName);
 *   HRESULT put_CompanyName ([in] BSTR bstrCompanyName);
 *   HRESULT get_Department ([out] BSTR *pbstrDepartment);
 *   HRESULT put_Department ([in] BSTR bstrDepartment);
 *   HRESULT get_Email1Address ([out] BSTR *pbstrEmail1Address);
 *   HRESULT put_Email1Address ([in] BSTR bstrEmail1Address);
 *   HRESULT get_MobileTelephoneNumber ([out] BSTR *pbstrMobileTelephoneNumber);
 *   HRESULT put_MobileTelephoneNumber ([in] BSTR bstrMobileTelephoneNumber);
 *   HRESULT get_OfficeLocation ([out] BSTR *pbstrOfficeLocation);
 *   HRESULT put_OfficeLocation ([in] BSTR bstrOfficeLocation);
 *   HRESULT get_PagerNumber ([out] BSTR *pbstrPagerNumber);
 *   HRESULT put_PagerNumber ([in] BSTR bstrPagerNumber);
 *   HRESULT get_BusinessTelephoneNumber ([out] BSTR *pbstrBusinessTelephoneNumber);
 *   HRESULT put_BusinessTelephoneNumber ([in] BSTR bstrBusinessTelephoneNumber);
 *   HRESULT get_JobTitle ([out] BSTR *pbstrJobTitle);
 *   HRESULT put_JobTitle ([in] BSTR bstrJobTitle);
 *   HRESULT get_HomeTelephoneNumber ([out] BSTR *pbstrHomeTelephoneNumber);
 *   HRESULT put_HomeTelephoneNumber ([in] BSTR bstrHomeTelephoneNumber);
 *   HRESULT get_Email2Address ([out] BSTR *pbstrEmail2Address);
 *   HRESULT put_Email2Address ([in] BSTR bstrEmail2Address);
 *   HRESULT get_Spouse ([out] BSTR *pbstrSpouse);
 *   HRESULT put_Spouse ([in] BSTR bstrSpouse);
 *   HRESULT get_Email3Address ([out] BSTR *pbstrEmail3Address);
 *   HRESULT put_Email3Address ([in] BSTR bstrEmail3Address);
 *   HRESULT get_Home2TelephoneNumber ([out] BSTR *pbstrHome2TelephoneNumber);
 *   HRESULT put_Home2TelephoneNumber ([in] BSTR bstrHome2TelephoneNumber);
 *   HRESULT get_HomeFaxNumber ([out] BSTR *pbstrHomeFaxNumber);
 *   HRESULT put_HomeFaxNumber ([in] BSTR bstrHomeFaxNumber);
 *   HRESULT get_CarTelephoneNumber ([out] BSTR *pbstrCarTelephoneNumber);
 *   HRESULT put_CarTelephoneNumber ([in] BSTR bstrCarTelephoneNumber);
 *   HRESULT get_AssistantName ([out] BSTR *pbstrAssistantName);
 *   HRESULT put_AssistantName ([in] BSTR bstrAssistantName);
 *   HRESULT get_AssistantTelephoneNumber ([out] BSTR *pbstrAssistantTelephoneNumber);
 *   HRESULT put_AssistantTelephoneNumber ([in] BSTR bstrAssistantTelephoneNumber);
 *   HRESULT get_Children ([out] BSTR *pbstrChildren);
 *   HRESULT put_Children ([in] BSTR bstrChildren);
 *   HRESULT get_Categories ([out] BSTR *pbstrCategories);
 *   HRESULT put_Categories ([in] BSTR bstrCategories);
 *   HRESULT get_WebPage ([out] BSTR *pbstrWebPage);
 *   HRESULT put_WebPage ([in] BSTR bstrWebPage);
 *   HRESULT get_Business2TelephoneNumber ([out] BSTR *pbstrBusiness2TelephoneNumber);
 *   HRESULT put_Business2TelephoneNumber ([in] BSTR bstrBusiness2TelephoneNumber);
 *   HRESULT get_RadioTelephoneNumber ([out] BSTR *pbstrRadioTelephoneNumber);
 *   HRESULT put_RadioTelephoneNumber ([in] BSTR bstrRadioTelephoneNumber);
 *   HRESULT get_FileAs ([out] BSTR *pbstrFileAs);
 *   HRESULT put_FileAs ([in] BSTR bstrFileAs);
 *   HRESULT get_YomiCompanyName ([out] BSTR *pbstrYomiCompanyName);
 *   HRESULT put_YomiCompanyName ([in] BSTR bstrYomiCompanyName);
 *   HRESULT get_YomiFirstName ([out] BSTR *pbstrYomiFirstName);
 *   HRESULT put_YomiFirstName ([in] BSTR bstrYomiFirstName);
 *   HRESULT get_YomiLastName ([out] BSTR *pbstrYomiLastName);
 *   HRESULT put_YomiLastName ([in] BSTR bstrYomiLastName);
 *   HRESULT get_Title ([out] BSTR *pbstrTitle);
 *   HRESULT put_Title ([in] BSTR bstrTitle);
 *   HRESULT get_FirstName ([out] BSTR *pbstrFirstName);
 *   HRESULT put_FirstName ([in] BSTR bstrFirstName);
 *   HRESULT get_MiddleName ([out] BSTR *pbstrMiddleName);
 *   HRESULT put_MiddleName ([in] BSTR bstrMiddleName);
 *   HRESULT get_LastName ([out] BSTR *pbstrLastName);
 *   HRESULT put_LastName ([in] BSTR bstrLastName);
 *   HRESULT get_Suffix ([out] BSTR *pbstrSuffix);
 *   HRESULT put_Suffix ([in] BSTR bstrSuffix);
 *   HRESULT get_HomeAddressStreet ([out] BSTR *pbstrHomeAddressStreet);
 *   HRESULT put_HomeAddressStreet ([in] BSTR bstrHomeAddressStreet);
 *   HRESULT get_HomeAddressCity ([out] BSTR *pbstrHomeAddressCity);
 *   HRESULT put_HomeAddressCity ([in] BSTR bstrHomeAddressCity);
 *   HRESULT get_HomeAddressState ([out] BSTR *pbstrHomeAddressState);
 *   HRESULT put_HomeAddressState ([in] BSTR bstrHomeAddressState);
 *   HRESULT get_HomeAddressPostalCode ([out] BSTR *pbstrHomeAddressPostalCode);
 *   HRESULT put_HomeAddressPostalCode ([in] BSTR bstrHomeAddressPostalCode);
 *   HRESULT get_HomeAddressCountry ([out] BSTR *pbstrHomeAddressCountry);
 *   HRESULT put_HomeAddressCountry ([in] BSTR bstrHomeAddressCountry);
 *   HRESULT get_OtherAddressStreet ([out] BSTR *pbstrOtherAddressStreet);
 *   HRESULT put_OtherAddressStreet ([in] BSTR bstrOtherAddressStreet);
 *   HRESULT get_OtherAddressCity ([out] BSTR *pbstrOtherAddressCity);
 *   HRESULT put_OtherAddressCity ([in] BSTR bstrOtherAddressCity);
 *   HRESULT get_OtherAddressState ([out] BSTR *pbstrOtherAddressState);
 *   HRESULT put_OtherAddressState ([in] BSTR bstrOtherAddressState);
 *   HRESULT get_OtherAddressPostalCode ([out] BSTR *pbstrOtherAddressPostalCode);
 *   HRESULT put_OtherAddressPostalCode ([in] BSTR bstrOtherAddressPostalCode);
 *   HRESULT get_OtherAddressCountry ([out] BSTR *pbstrOtherAddressCountry);
 *   HRESULT put_OtherAddressCountry ([in] BSTR bstrOtherAddressCountry);
 *   HRESULT get_BusinessAddressStreet ([out] BSTR *pbstrBusinessAddressStreet);
 *   HRESULT put_BusinessAddressStreet ([in] BSTR bstrBusinessAddressStreet);
 *   HRESULT get_BusinessAddressCity ([out] BSTR *pbstrBusinessAddressCity);
 *   HRESULT put_BusinessAddressCity ([in] BSTR bstrBusinessAddressCity);
 *   HRESULT get_BusinessAddressState ([out] BSTR *pbstrBusinessAddressState);
 *   HRESULT put_BusinessAddressState ([in] BSTR bstrBusinessAddressState);
 *   HRESULT get_BusinessAddressPostalCode ([out] BSTR *pbstrBusinessAddressPostalCode);
 *   HRESULT put_BusinessAddressPostalCode ([in] BSTR bstrBusinessAddressPostalCode);
 *   HRESULT get_BusinessAddressCountry ([out] BSTR *pbstrBusinessAddressCountry);
 *   HRESULT put_BusinessAddressCountry ([in] BSTR bstrBusinessAddressCountry);
 *   HRESULT get_Body ([out] BSTR *pbstrBody);
 *   HRESULT put_Body ([in] BSTR bstrBody);
 *   HRESULT get_BodyInk ([out] CEBLOB **ppBodyInk);
 *   HRESULT put_BodyInk ([in] CEBLOB *pBodyInk);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *   HRESULT get_Oid ([out] long *plOid);
 *
 * IContact methods (3 pages):
 *   ms880165 Copy: HRESULT Copy(IContact** ppolItem);
 *   ms880170 Delete: HRESULT Delete ();
 *   ms880181 Save: HRESULT Save ();
 */

/* ITask: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * ITask properties (32 accessors):
 *   HRESULT get_Subject ([out] BSTR *pbstrSubject);
 *   HRESULT put_Subject ([in] BSTR bstrSubject);
 *   HRESULT get_Categories ([out] BSTR *pbstrCategories);
 *   HRESULT put_Categories ([in] BSTR bstrCategories);
 *   HRESULT get_StartDate ([out] DATE *pdaStartDate);
 *   HRESULT put_StartDate ([in] DATE daStartDate);
 *   HRESULT get_DueDate ([out] DATE *pdaDueDate);
 *   HRESULT put_DueDate ([in] DATE daDueDate);
 *   HRESULT get_DateCompleted ([out] DATE *pdaDateCompleted);
 *   HRESULT get_Importance ([out] long *plImportance);
 *   HRESULT put_Importance ([in] long lImportance);
 *   HRESULT get_Complete ([out] VARIANT_BOOL *pbComplete);
 *   HRESULT put_Complete ([in] VARIANT_BOOL bComplete);
 *   HRESULT get_IsRecurring ([out] VARIANT_BOOL *pbIsRecurring);
 *   HRESULT get_Sensitivity ([out] long *plSensitivity);
 *   HRESULT put_Sensitivity ([in] long lSensitivity);
 *   HRESULT get_TeamTask ([out] VARIANT_BOOL *pbTeamTask);
 *   HRESULT put_TeamTask ([in] VARIANT_BOOL bTeamTask);
 *   HRESULT get_ReminderSet ([out] VARIANT_BOOL *pbReminderSet);
 *   HRESULT put_ReminderSet ([in] VARIANT_BOOL bReminderSet);
 *   HRESULT get_ReminderSoundFile ([out] BSTR *pbstrReminderSoundFile);
 *   HRESULT put_ReminderSoundFile ([in] BSTR bstrReminderSoundFile);
 *   HRESULT get_ReminderOptions ([out] long *plReminderOptions);
 *   HRESULT put_ReminderOptions ([in] long lReminderOptions);
 *   HRESULT get_ReminderTime ([out] DATE *pdaReminderTime);
 *   HRESULT put_ReminderTime ([in] DATE daReminderTime);
 *   HRESULT get_Body ([out] BSTR *pbstrBody);
 *   HRESULT put_Body ([in] BSTR bstrBody);
 *   HRESULT get_BodyInk ([out] CEBLOB **ppBodyInk);
 *   HRESULT put_BodyInk ([in] CEBLOB *pBodyInk);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *   HRESULT get_Oid ([out] long *plOid);
 *
 * ITask methods (6 pages):
 *   ms890811 ClearRecurrencePattern: HRESULT ClearReccurencePattern ();
 *   ms890817 Copy: HRESULT Copy(ITask** ppolItem);
 *   ms890821 Delete: HRESULT Delete ();
 *   ms890827 GetRecurrencePattern: HRESULT GetRecurrence(IRecurrencePattern* pRec);
 *   ms890846 Save: HRESULT Save ();
 *   ms890851 SkipRecurrence: HRESULT SkipRecurrence ();
 */

/* IRecurrencePattern: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IRecurrencePattern properties (27 accessors):
 *   HRESULT get_RecurrenceType ([out] long *plRecurrenceType);
 *   HRESULT put_RecurrenceType ([in] long lRecurrenceType);
 *   HRESULT get_PatternStartDate ([out] DATE *pdaPatternStartDate);
 *   HRESULT put_PatternStartDate ([in] DATE daPatternStartDate);
 *   HRESULT get_PatternEndDate ([out] DATE *pdaPatternEndDate);
 *   HRESULT put_PatternEndDate ([in] DATE daPatternEndDate);
 *   HRESULT get_NoEndDate ([out] VARIANT_BOOL *pbNoEndDate);
 *   HRESULT put_NoEndDate ([in] VARIANT_BOOL bNoEndDate);
 *   HRESULT get_Occurrences ([out] long *plOccurrences);
 *   HRESULT put_Occurrences ([in] long lOccurrences);
 *   HRESULT get_StartTime ([out] DATE *pdaStartTime);
 *   HRESULT put_StartTime ([in] DATE daStartTime);
 *   HRESULT get_Duration ([out] long *plDuration);
 *   HRESULT put_Duration ([in] long lDuration);
 *   HRESULT get_EndTime ([out] DATE *pdaEndTime);
 *   HRESULT put_EndTime ([in] DATE daEndTime);
 *   HRESULT get_Exceptions ([out] Iexceptions **ppExceptions);
 *   HRESULT get_Interval ([out] long *plInterval);
 *   HRESULT put_Interval ([in] long lInterval);
 *   HRESULT get_DayOfWeekMask ([out] long *plDayOfWeekMask);
 *   HRESULT put_DayOfWeekMask ([in] long lDayOfWeekMask);
 *   HRESULT get_DayOfMonth ([out] long *plDayOfMonth);
 *   HRESULT put_DayOfMonth ([in] long lDayOfMonth);
 *   HRESULT get_Instance ([out] long *plInstance);
 *   HRESULT put_Instance ([in] long lInstance);
 *   HRESULT get_MonthOfYear ([out] long *plMonthOfYear);
 *   HRESULT put_MonthOfYear ([in] long lMonthOfYear);
 *
 * IRecurrencePattern methods (1 pages):
 *   ms884582 GetOccurrence: HRESULT GetOccurrence(DATEdate,IAppointmentItem* polAppt);
 */

/* IException: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IException properties (3 accessors):
 *   HRESULT get_Deleted ([out] VARIANT_BOOL *pbDeleted);
 *   HRESULT get_OriginalDate ([out] DATE *pdaOriginalDate);
 *   HRESULT get_AppointmentItem ([out] Iappointment **ppAppointmentItem);
 */

/* IExceptions: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IExceptions properties (2 accessors):
 *   HRESULT get_Count ([out] int *piCount);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *
 * IExceptions methods (1 pages):
 *   aa515721 Item: HRESULT Item(intiIndex,IException** ppException);
 */

/* IFolder: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IFolder properties (3 accessors):
 *   HRESULT get_Items ([out] IPOutlookItemCollection **ppolItems);
 *   HRESULT get_DefaultItemType ([out] int *piDefaultItemType);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *
 * IFolder methods (3 pages):
 *   aa516161 AddItemToInfraredFolder: HRESULT AddItemToInfraredFolder(int olItem,IDispatch* polItem);
 *   aa516164 ReceiveFromInfrared: HRESULT ReceiveFromInfrared(IPOutlookItemCollection** ppolItems);
 *   aa516165 SendToInfrared: HRESULT SendToInfrared ();
 */

/* IPOutlookItemCollection: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IPOutlookItemCollection properties (4 accessors):
 *   HRESULT get_Count ([out] int *piCount);
 *   HRESULT get_IncludeRecurrences ([out] VARIANT_BOOL *pbIncludeRecurrences);
 *   HRESULT put_IncludeRecurrences ([in] VARIANT_BOOL bIncludeRecurrences);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *
 * IPOutlookItemCollection methods (7 pages):
 *   ms884078 Add: HRESULT Add(IDispatch** ppolItem);
 *   ms884141 Find: HRESULT Find (BSTR pwszRestriction,IDispatch** ppolItem);
 *   ms884152 FindNext: HRESULT FindNext(IDispatch** ppolItem);
 *   ms884165 Item: HRESULT Item(int iItem,IDispatch** ppolItem);
 *   ms884201 Remove: HRESULT Remove(int iItem);
 *   ms884210 Restrict: HRESULT Restrict(BSTR pwszRestriction,IPOutlookItemCollection** ppolItems);
 *   ms884223 Sort: HRESULT Sort(BSTR pwszProperty,VARIANT_BOOLfDescending);
 */

/* IPOlRecipient: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IPOlRecipient methods (1 pages):
 *   ms883882 Resolve: HRESULT Resolve(VARIANT_BOOLfDisplayUI,VARIANT_BOOL* pfResolved);
 */

/* IRecipient: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IRecipient properties (3 accessors):
 *   HRESULT get_Address ([out] BSTR *pbstrAddress);
 *   HRESULT put_Address ([in] BSTR bstrAddress);
 *   HRESULT get_Name ([out] BSTR *pbstrName);
 */

/* IRecipients: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * IRecipients properties (2 accessors):
 *   HRESULT get_Count ([out] int *piCount);
 *   HRESULT get_Application ([out] IPOutlookApp **ppIPOutlookApp);
 *
 * IRecipients methods (3 pages):
 *   ms884349 Add: HRESULT Add(BSTRpwszName,IRecipient** pRecipient);
 *   ms884359 Item: HRESULT Item(intiIndex,IRecipient** ppRecipient);
 *   ms884577 Remove: HRESULT Remove(intiIndex);
 */

/* ITimeZone: documented surface (Windows CE 2.0 and later;
 * Pimstore.h; Pimstore.lib).  vtable layouts are not published;
 * signatures are recorded verbatim from the method pages and the
 * "Properties in Vtable Order" property tables (accessor order
 * preserved).
 *
 * ITimeZone properties (16 accessors):
 *   HRESULT get_Bias ([out] long *plBias);
 *   HRESULT get_SupportsDST ([out] VARIANT_BOOL *pbSupportsDST);
 *   HRESULT get_IsStandardAbsoluteDate ([out] VARIANT_BOOL *pbIsStandardAbsoluteDate);
 *   HRESULT get_IsDaylightAbsoluteDate ([out] VARIANT_BOOL *pbIsDaylightAbsoluteDate);
 *   HRESULT get_StandardDate ([out] DATE *pdaStandardDate);
 *   HRESULT get_StandardBias ([out] long *plStandardBias);
 *   HRESULT get_StandardName ([out] BSTR *pbstrStandardName);
 *   HRESULT get_StandardDayOfWeekMask ([out] long *plStandardDayOfWeekMask);
 *   HRESULT get_StandardInstance ([out] long *plStandardInstance);
 *   HRESULT get_StandardMonthOfYear ([out] long *plStandardMonthOfYear);
 *   HRESULT get_DaylightDate ([out] DATE *pdaDaylightDate);
 *   HRESULT get_DaylightBias ([out] long *plDaylightBias);
 *   HRESULT get_DaylightName ([out] BSTR *pbstrDaylightName);
 *   HRESULT get_DaylightDayOfWeekMask ([out] long *plDaylightDayOfWeekMask);
 *   HRESULT get_DaylightInstance ([out] long *plDaylightInstance);
 *   HRESULT get_DaylightMonthOfYear ([out] long *plDaylightMonthOfYear);
 */

/* ------------------------------------------------------------------
 * Book surface: poom (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa515361 IAppointment Properties (Header: Pimstore.h.) */
/* aa515347 IAppointment::Cancel (Header: Pimstore.h.) */
/* aa515349 IAppointment::ClearRecurrencePattern (Header: Pimstore.h.) */
/* aa515351 IAppointment::Copy (Header: Pimstore.h.) */
/* aa515355 IAppointment::Delete (Header: Pimstore.h.) */
/* aa515357 IAppointment::GetRecurrencePattern (Header: Pimstore.h.) */
/* aa515363 IAppointment::Save (Header: Pimstore.h.) */
/* aa515365 IAppointment::Send (Header: Pimstore.h.) */
/* ms880177 IContact Properties (Header: Pimstore.h.) */
/* ms880165 IContact::Copy (Header: Pimstore.h.) */
/* ms880170 IContact::Delete (Header: Pimstore.h.) */
/* ms880181 IContact::Save (Header: Pimstore.h.) */
/* aa515719 IException Properties (Header: Pimstore.h.) */
/* aa516109 IExceptions Properties (Header: Pimstore.h.) */
/* aa515721 IExceptions::Item (Header: Pimstore.h.) */
/* aa516163 IFolder Properties (Header: Pimstore.h.) */
/* aa516161 IFolder::AddItemToInfraredFolder (Header: Pimstore.h.) */
/* aa516164 IFolder::ReceiveFromInfrared (Header: Pimstore.h.) */
/* aa516165 IFolder::SendToInfrared (Header: Pimstore.h.) */
/* ms883882 IPOlRecipient::Resolve (Header: Pimstore.h.) */
/* ms883975 IPOutlookApp Properties (Header: Pimstore.h.) */
/* ms883892 IPOutlookApp::CreateItem (Header: Pimstore.h.) */
/* ms883903 IPOutlookApp::GetDefaultFolder (Header: Pimstore.h.) */
/* ms883912 IPOutlookApp::GetItemFromOid (Header: Pimstore.h.) */
/* ms883922 IPOutlookApp::GetTimeZoneFromIndex (Header: Pimstore.h.) */
/* ms883930 IPOutlookApp::GetTimeZoneInformationFromIndex (Header: Pimstore.h.) */
/* ms883952 IPOutlookApp::Logoff (Header: Pimstore.h.) */
/* ms883962 IPOutlookApp::Logon (Header: Pimstore.h.) */
/* ms883983 IPOutlookApp::ReceiveFromInfrared (Header: Pimstore.h.) */
/* ms884055 IPOutlookApp::SysFreeString (Header: Pimstore.h.) */
/* ms884192 IPOutlookItemCollection Properties (Header: Pimstore.h.) */
/* ms884078 IPOutlookItemCollection::Add (Header: Pimstore.h.) */
/* ms884141 IPOutlookItemCollection::Find (Header: Pimstore.h.) */
/* ms884152 IPOutlookItemCollection::FindNext (Header: Pimstore.h.) */
/* ms884165 IPOutlookItemCollection::Item (Header: Pimstore.h.) */
/* ms884201 IPOutlookItemCollection::Remove (Header: Pimstore.h.) */
/* ms884210 IPOutlookItemCollection::Restrict (Header: Pimstore.h.) */
/* ms884223 IPOutlookItemCollection::Sort (Header: Pimstore.h.) */
/* ms884338 IRecipient Properties (Header: Pimstore.h.) */
/* ms884569 IRecipients Properties (Header: Pimstore.h.) */
/* ms884349 IRecipients::Add (Header: Pimstore.h.) */
/* ms884359 IRecipients::Item (Header: Pimstore.h.) */
/* ms884577 IRecipients::Remove (Header: Pimstore.h.) */
/* ms884584 IRecurrencePattern Properties (Header: Pimstore.h.) */
/* ms884582 IRecurrencePattern::GetOccurrence (Header: Pimstore.h.) */
/* ms890839 ITask Properties (Header: Pimstore.h.) */
/* ms890811 ITask::ClearRecurrencePattern (Header: Pimstore.h.) */
/* ms890817 ITask::Copy (Header: Pimstore.h.) */
/* ms890821 ITask::Delete (Header: Pimstore.h.) */
/* ms890827 ITask::GetRecurrencePattern (Header: Pimstore.h.) */
/* ms890846 ITask::Save (Header: Pimstore.h.) */
/* ms890851 ITask::SkipRecurrence (Header: Pimstore.h.) */
/* ms890879 ITimeZone Properties (Header: Pimstore.h.) */

/* ------------------------------------------------------------------
 * Book surface: poom (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms862095 Basic Object Model */
/* ms862103 Cancel Method */
/* ms862129 Creating a Recurring Appointment */
/* ms862135 Design Goals */
/* ms862137 Determining the Version */
/* ms862141 Differences Between the Windows CE and Desktop Models */
/* ms862169 Infrared Support */
/* ms862659 No Events */
/* ms862660 No Inspector or Explorer Object */
/* ms862661 No NameSpace Object */
/* ms862663 OID Instead of EntryID */
/* ms862668 Outlook Compatibility */
/* ms897376 Pocket Outlook Object Model Application Development */
/* ms862673 Pocket Outlook Object Model Code Examples */
/* aa513746 Pocket Outlook Object Model Constants */
/* aa513747 Pocket Outlook Object Model Functions */
/* aa513748 Pocket Outlook Object Model Interfaces */
/* ms897377 Pocket Outlook Object Model OS Design Development */
/* aa513749 Pocket Outlook Object Model Reference */
/* aa513751 Pocket Outlook Object Model Security */
/* aa513750 POOM Sample Code */
/* ms862681 Recipients Define Meeting Requests */
/* ms862683 Reminder Methods */

/* ------------------------------------------------------------------
 * Book surface: poom (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa515361 IAppointment Properties (Header: Pimstore.h.) */
/* aa515347 IAppointment::Cancel (Header: Pimstore.h.) */
/* aa515349 IAppointment::ClearRecurrencePattern (Header: Pimstore.h.) */
/* aa515351 IAppointment::Copy (Header: Pimstore.h.) */
/* aa515355 IAppointment::Delete (Header: Pimstore.h.) */
/* aa515357 IAppointment::GetRecurrencePattern (Header: Pimstore.h.) */
/* aa515363 IAppointment::Save (Header: Pimstore.h.) */
/* aa515365 IAppointment::Send (Header: Pimstore.h.) */
/* ms880177 IContact Properties (Header: Pimstore.h.) */
/* ms880165 IContact::Copy (Header: Pimstore.h.) */
/* ms880170 IContact::Delete (Header: Pimstore.h.) */
/* ms880181 IContact::Save (Header: Pimstore.h.) */
/* aa515719 IException Properties (Header: Pimstore.h.) */
/* aa516109 IExceptions Properties (Header: Pimstore.h.) */
/* aa515721 IExceptions::Item (Header: Pimstore.h.) */
/* aa516163 IFolder Properties (Header: Pimstore.h.) */
/* aa516161 IFolder::AddItemToInfraredFolder (Header: Pimstore.h.) */
/* aa516164 IFolder::ReceiveFromInfrared (Header: Pimstore.h.) */
/* aa516165 IFolder::SendToInfrared (Header: Pimstore.h.) */
/* ms883882 IPOlRecipient::Resolve (Header: Pimstore.h.) */
/* ms883975 IPOutlookApp Properties (Header: Pimstore.h.) */
/* ms883892 IPOutlookApp::CreateItem (Header: Pimstore.h.) */
/* ms883903 IPOutlookApp::GetDefaultFolder (Header: Pimstore.h.) */
/* ms883912 IPOutlookApp::GetItemFromOid (Header: Pimstore.h.) */
/* ms883922 IPOutlookApp::GetTimeZoneFromIndex (Header: Pimstore.h.) */
/* ms883930 IPOutlookApp::GetTimeZoneInformationFromIndex (Header: Pimstore.h.) */
/* ms883952 IPOutlookApp::Logoff (Header: Pimstore.h.) */
/* ms883962 IPOutlookApp::Logon (Header: Pimstore.h.) */
/* ms883983 IPOutlookApp::ReceiveFromInfrared (Header: Pimstore.h.) */
/* ms884055 IPOutlookApp::SysFreeString (Header: Pimstore.h.) */
/* ms884192 IPOutlookItemCollection Properties (Header: Pimstore.h.) */
/* ms884078 IPOutlookItemCollection::Add (Header: Pimstore.h.) */
/* ms884141 IPOutlookItemCollection::Find (Header: Pimstore.h.) */
/* ms884152 IPOutlookItemCollection::FindNext (Header: Pimstore.h.) */
/* ms884165 IPOutlookItemCollection::Item (Header: Pimstore.h.) */
/* ms884201 IPOutlookItemCollection::Remove (Header: Pimstore.h.) */
/* ms884210 IPOutlookItemCollection::Restrict (Header: Pimstore.h.) */
/* ms884223 IPOutlookItemCollection::Sort (Header: Pimstore.h.) */
/* ms884338 IRecipient Properties (Header: Pimstore.h.) */
/* ms884569 IRecipients Properties (Header: Pimstore.h.) */
/* ms884349 IRecipients::Add (Header: Pimstore.h.) */
/* ms884359 IRecipients::Item (Header: Pimstore.h.) */
/* ms884577 IRecipients::Remove (Header: Pimstore.h.) */
/* ms884584 IRecurrencePattern Properties (Header: Pimstore.h.) */
/* ms884582 IRecurrencePattern::GetOccurrence (Header: Pimstore.h.) */
/* ms890839 ITask Properties (Header: Pimstore.h.) */
/* ms890811 ITask::ClearRecurrencePattern (Header: Pimstore.h.) */
/* ms890817 ITask::Copy (Header: Pimstore.h.) */
/* ms890821 ITask::Delete (Header: Pimstore.h.) */
/* ms890827 ITask::GetRecurrencePattern (Header: Pimstore.h.) */
/* ms890846 ITask::Save (Header: Pimstore.h.) */
/* ms890851 ITask::SkipRecurrence (Header: Pimstore.h.) */
/* ms890879 ITimeZone Properties (Header: Pimstore.h.) */

/* ------------------------------------------------------------------
 * Book surface: poom (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms862095 Basic Object Model */
/* ms862103 Cancel Method */
/* ms862129 Creating a Recurring Appointment */
/* ms862135 Design Goals */
/* ms862137 Determining the Version */
/* ms862141 Differences Between the Windows CE and Desktop Models */
/* ms862169 Infrared Support */
/* ms862659 No Events */
/* ms862660 No Inspector or Explorer Object */
/* ms862661 No NameSpace Object */
/* ms862663 OID Instead of EntryID */
/* ms862668 Outlook Compatibility */
/* ms897376 Pocket Outlook Object Model Application Development */
/* ms862673 Pocket Outlook Object Model Code Examples */
/* aa513746 Pocket Outlook Object Model Constants */
/* aa513747 Pocket Outlook Object Model Functions */
/* aa513748 Pocket Outlook Object Model Interfaces */
/* ms897377 Pocket Outlook Object Model OS Design Development */
/* aa513749 Pocket Outlook Object Model Reference */
/* aa513751 Pocket Outlook Object Model Security */
/* aa513750 POOM Sample Code */
/* ms862681 Recipients Define Meeting Requests */
/* ms862683 Reminder Methods */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_PIMSTORE_H */
