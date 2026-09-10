/*
 * Winldap.h -- LDAP client API for Windows CE (Winldap.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Lightweight Directory Access Protocol (LDAP)
 * Client :: LDAP Reference" (tools/manifests/ldap.manifest, 124 leaves);
 * whitespace-preserved prototypes were cross-read against the CE 6.0
 * (v=winembedded.60) twins (tools/manifests/m54-ce60.manifest).
 *
 * Requirement rows: Header Winldap.h, Link Library Wldap32.lib for every
 * function page (see def/wldap32-doc.def); the structure / enumeration /
 * option pages carry no Link Library row.  OS Versions: "Windows CE .NET
 * 4.0 and later" unless noted otherwise per declaration.
 *
 * Quirk recorded once for the whole file: the migrated CE 5.0 pages print
 * a "UNICODE" marker before PTCHAR parameters/fields (e.g. ldap_init
 * ms892275 prints "UNICODE PTCHAR HostName").  This is the archive's
 * Unicode-only notation, not a C type qualifier; the declarations below
 * use PTCHAR (TCHAR*, and CE is Unicode-only, see windef.h).
 *
 * Windows CE functions are __cdecl; the WINAPI/CALLBACK decorations the
 * migrated pages sometimes print are empty on CE (see windef.h).  The
 * referral-callback pages print "_cdecl" (one underscore, sic) -- mapped
 * to the empty-on-CE CALLBACK like the other CE calling conventions.
 */

#ifndef AKARI_WINLDAP_H
#define AKARI_WINLDAP_H

#include "Windef.h"
#include "Wincrypt.h"   /* PCCERT_CONTEXT (VERIFYSERVERCERT ms897184) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Opaque handle types (LDAP Structures book).                         */
/* ------------------------------------------------------------------ */

/* ms891742 "LDAP": page prints "typedef ldap LDAP, *PLDAP;" (struct
 * keyword restored as with the M51 IMENUMINFO page); the tag is never
 * laid out -- the connection is opaque.  CE .NET 4.0+. */
typedef struct ldap LDAP, *PLDAP;

/* ms892278 "LDAPMessage": "typedef ldapmsg LDAPMessage, *PLDAPMessage;"
 * -- opaque result/message handle.  CE .NET 4.0+. */
typedef struct ldapmsg LDAPMessage, *PLDAPMessage;

/* ms892309 "LDAPSearch": "typedef struct ldapsearch LDAPSearch,
 * *PLDAPSearch;" -- opaque paged-search handle.  CE .NET 4.0+. */
typedef struct ldapsearch LDAPSearch, *PLDAPSearch;

/* ms863747 "BerElement": printed with one documented member (the
 * desktop reference treats the same tag as opaque; the CE page prints
 * "typedef struct berElement {UNICODE PTCHAR opaque;} BerElement;").
 * CE .NET 4.0+; Winldap.h (the ber_* functions are Winber.h). */
typedef struct berElement {
    PTCHAR   opaque;
} BerElement;

/* ms863826 "berval": "typedef struct berval {ULONG bv_len;
 * UNICODE PTCHAR bv_val;} LDAP_BERVAL, *PLDAP_BERVAL, BERVAL,
 * *PBERVAL;".  CE .NET 4.0+. */
typedef struct berval {
    ULONG    bv_len;
    PTCHAR   bv_val;
} LDAP_BERVAL, *PLDAP_BERVAL, BERVAL, *PBERVAL;

/* ------------------------------------------------------------------ */
/* Value structures (LDAP Structures book).                            */
/* ------------------------------------------------------------------ */

/* ms891757 "LDAPControl": "typedef struct ldapcontrol {PWCHAR ldctl_oid;
 * struct berval ldctl_value; BOOLEAN ldctl_iscritical;} LDAPControl,
 * *PLDAPControl;".  CE .NET 4.0+. */
typedef struct ldapcontrol {
    PWCHAR          ldctl_oid;
    struct berval   ldctl_value;
    BOOLEAN         ldctl_iscritical;
} LDAPControl, *PLDAPControl;

/* ms892279 "LDAPMod": "typedef struct ldapmod {ULONG mod_op;
 * PWCHAR mod_type; union {PWCHAR* modv_strvals; struct berval**
 * modv_bvals;} mod_vals;} LDAPMod, *PLDAPMod;".  mod_op takes the
 * LDAP_MOD_* values (values published on this page, see below).
 * CE .NET 4.0+. */
typedef struct ldapmod {
    ULONG           mod_op;
    PWCHAR          mod_type;
    union {
        PWCHAR              *modv_strvals;
        struct berval       **modv_bvals;
    } mod_vals;
} LDAPMod, *PLDAPMod;

/* ms892315 "LDAP_TIMEVAL": "typedef struct l_timeval {LONG tv_sec;
 * LONG tv_usec;} LDAP_TIMEVAL, *PLDAP_TIMEVAL;".  CE .NET 4.0+. */
typedef struct l_timeval {
    LONG     tv_sec;
    LONG     tv_usec;
} LDAP_TIMEVAL, *PLDAP_TIMEVAL;

/* ms892313 "LDAPSortKey": "typedef struct ldapsortkey {PWCHAR
 * sk_attrtype; PWCHAR sk_matchruleoid; BOOLEAN sk_reverseorder;}
 * LDAPSortKey, *PLDAPSortKey;".  CE .NET 4.0+. */
typedef struct ldapsortkey {
    PWCHAR   sk_attrtype;
    PWCHAR   sk_matchruleoid;
    BOOLEAN  sk_reverseorder;
} LDAPSortKey, *PLDAPSortKey;

/* ------------------------------------------------------------------ */
/* LDAP_RETCODE (ms892299, LDAP Enumerations book; values published    */
/* on the page, printed verbatim below).                               */
/* ------------------------------------------------------------------ */

typedef enum {
    LDAP_SUCCESS                 = 0x00,
    LDAP_OPERATIONS_ERROR        = 0x01,
    LDAP_PROTOCOL_ERROR          = 0x02,
    LDAP_TIMELIMIT_EXCEEDED      = 0x03,
    LDAP_SIZELIMIT_EXCEEDED      = 0x04,
    LDAP_COMPARE_FALSE           = 0x05,
    LDAP_COMPARE_TRUE            = 0x06,
    LDAP_AUTH_METHOD_NOT_SUPPORTED = 0x07,
    LDAP_STRONG_AUTH_REQUIRED    = 0x08,
    LDAP_REFERRAL_V2             = 0x09,
    LDAP_PARTIAL_RESULTS         = 0x09,
    LDAP_REFERRAL                = 0x0a,
    LDAP_ADMIN_LIMIT_EXCEEDED    = 0x0b,
    LDAP_UNAVAILABLE_CRIT_EXTENSION = 0x0c,
    LDAP_CONFIDENTIALITY_REQUIRED = 0x0d,
    LDAP_SASL_BIND_IN_PROGRESS   = 0x0e,
    LDAP_NO_SUCH_ATTRIBUTE       = 0x10,
    LDAP_UNDEFINED_TYPE          = 0x11,
    LDAP_INAPPROPRIATE_MATCHING  = 0x12,
    LDAP_CONSTRAINT_VIOLATION    = 0x13,
    LDAP_ATTRIBUTE_OR_VALUE_EXISTS = 0x14,
    LDAP_INVALID_SYNTAX          = 0x15,
    LDAP_NO_SUCH_OBJECT          = 0x20,
    LDAP_ALIAS_PROBLEM           = 0x21,
    LDAP_INVALID_DN_SYNTAX       = 0x22,
    LDAP_IS_LEAF                 = 0x23,
    LDAP_ALIAS_DEREF_PROBLEM     = 0x24,
    LDAP_INAPPROPRIATE_AUTH      = 0x30,
    LDAP_INVALID_CREDENTIALS     = 0x31,
    LDAP_INSUFFICIENT_RIGHTS     = 0x32,
    LDAP_BUSY                    = 0x33,
    LDAP_UNAVAILABLE             = 0x34,
    LDAP_UNWILLING_TO_PERFORM    = 0x35,
    LDAP_LOOP_DETECT             = 0x36,
    LDAP_NAMING_VIOLATION        = 0x40,
    LDAP_OBJECT_CLASS_VIOLATION  = 0x41,
    LDAP_NOT_ALLOWED_ON_NONLEAF  = 0x42,
    LDAP_NOT_ALLOWED_ON_RDN      = 0x43,
    LDAP_ALREADY_EXISTS          = 0x44,
    LDAP_NO_OBJECT_CLASS_MODS    = 0x45,
    LDAP_RESULTS_TOO_LARGE       = 0x46,
    LDAP_AFFECTS_MULTIPLE_DSAS   = 0x47,
    LDAP_OTHER                   = 0x50,
    LDAP_SERVER_DOWN             = 0x51,
    LDAP_LOCAL_ERROR             = 0x52,
    LDAP_ENCODING_ERROR          = 0x53,
    LDAP_DECODING_ERROR          = 0x54,
    LDAP_TIMEOUT                 = 0x55,
    LDAP_AUTH_UNKNOWN            = 0x56,
    LDAP_FILTER_ERROR            = 0x57,
    LDAP_USER_CANCELLED          = 0x58,
    LDAP_PARAM_ERROR             = 0x59,
    LDAP_NO_MEMORY               = 0x5a,
    LDAP_CONNECT_ERROR           = 0x5b,
    LDAP_NOT_SUPPORTED           = 0x5c,
    LDAP_CONTROL_NOT_FOUND       = 0x5d,
    LDAP_NO_RESULTS_RETURNED     = 0x5e,
    LDAP_MORE_RESULTS_TO_RETURN  = 0x5f,
    LDAP_CLIENT_LOOP             = 0x60,
    LDAP_REFERRAL_LIMIT_EXCEEDED = 0x61
} LDAP_RETCODE;

/* ------------------------------------------------------------------ */
/* Published constants.                                                */
/* ------------------------------------------------------------------ */

/* LDAPMod.mod_op values (ms892279 LDAPMod page table). */
#define LDAP_MOD_ADD            0x00
#define LDAP_MOD_DELETE         0x01
#define LDAP_MOD_REPLACE        0x02

/* Session options (ms893453 "Session Options" tables; values printed
 * in parentheses on the page).  The page prints the SERVER_EXT_ERROR
 * row as "LPDA_OPT_SERVER_EXT_ERROR (0x34)" [sic]; the spelling is
 * recorded verbatim.  LDAP_OPT_PROTOCOL_VERSION and LDAP_OPT_VERSION
 * are the same option (0x11) per the page row. */
#define LDAP_OPT_DESC                 0x01
#define LDAP_OPT_DEREF                0x02
#define LDAP_OPT_SIZELIMIT            0x03
#define LDAP_OPT_TIMELIMIT            0x04
#define LDAP_OPT_REFERRALS            0x08
#define LDAP_OPT_RESTART              0x09   /* "Not supported" on CE */
#define LDAP_OPT_SSL                  0x0a
#define LDAP_OPT_REFERRAL_HOP_LIMIT   0x10
#define LDAP_OPT_PROTOCOL_VERSION     0x11
#define LDAP_OPT_VERSION              0x11
#define LDAP_OPT_HOST_NAME            0x30
#define LDAP_OPT_ERROR_NUMBER         0x31
#define LDAP_OPT_ERROR_STRING         0x32
#define LDAP_OPT_SERVER_ERROR         0x33
#define LPDA_OPT_SERVER_EXT_ERROR     0x34   /* [sic] page spelling */
#define LDAP_OPT_DNSDOMAIN_NAME       0x3B
#define LDAP_OPT_HOST_REACHABLE       0x3E
#define LDAP_OPT_PROMPT_CREDENTIALS   0x3F
#define LDAP_OPT_AUTO_RECONNECT       0x91
#define LDAP_OPT_SSPI_FLAGS           0x92
#define LDAP_OPT_AREC_EXCLUSIVE       0x98
#define PING_KEEP_ALIVE               0x36
#define PING_WAIT_TIME                0x37
#define PING_LIMIT                    0x38

/* LDAP_OPT_DEREF output values (ms893453 table). */
#define LDAP_DEREF_NEVER              0x00
#define LDAP_DEREF_SEARCHING          0x01
#define LDAP_DEREF_FINDING            0x02
#define LDAP_DEREF_ALWAYS             0x03

/* Referral/limit sentinel: "A value of LDAP_NO_LIMIT (zero) means
 * that there is no limit" (ms893453). */
#define LDAP_NO_LIMIT                 0

/* HELD (named on CE pages, values not published -- names-without-values
 * only, see docs/inventory.md M54): LDAP_OPT_ON / LDAP_OPT_OFF,
 * LDAP_ON / LDAP_OFF, LDAP_VERSION2 / LDAP_VERSION3,
 * LDAP_CHASE_SUBORDINATE_REFERRALS / LDAP_CHASE_EXTERNAL_REFERRALS
 * (ms893453), LDAP_AUTH_SIMPLE / LDAP_AUTH_NTLM / LDAP_AUTH_NEGOTIATE
 * (ldap_bind ms891748 / ldap_bind_s ms891749 tables), LDAP_SCOPE_BASE /
 * LDAP_SCOPE_ONELEVEL / LDAP_SCOPE_SUBTREE (ldap_search* ms892302 etc.
 * tables), LDAP_RES_ADD / _BIND / _COMPARE / _DELETE / _EXTENDED /
 * _MODDN / _MODIFY / _SEARCH_ENTRY / _SEARCH_REFERENCE / _SEARCH_RESULT
 * (ldap_result ms892297 table), LDAP_OPT_SIGN (ms893453 prints no
 * value), SEC_WINNT_AUTH_IDENTITY (ldap_bind_s parameter type -- SSPI
 * book not yet harvested). */

/* ------------------------------------------------------------------ */
/* Referral callbacks (LDAP Callback Functions book) and the           */
/* LDAP_REFERRAL_CALLBACK structure (ms892294).                        */
/* ------------------------------------------------------------------ */

/* ms864415 "DEREFERENCECONNECTION": page prints
 * "typedef ULONG (_cdecl DEREFERENCECONNECTION)(PLDAP PrimaryConnection,
 * PLDAP ConnectionToDereference);". */
typedef ULONG (CALLBACK DEREFERENCECONNECTION)(
    PLDAP PrimaryConnection,
    PLDAP ConnectionToDereference);

/* ms892585 "NOTIFYOFNEWCONNECTION": page prints
 * "typedef BOOLEAN (_cdecl NOTIFYOFNEWCONNECTION) (PLDAP
 * PrimaryConnection, PLDAP ReferralFromConnection, PWCHAR NewDN,
 * PCHAR HostName, PLDAP NewConnection, ULONG PortNumber, PVOID
 * SecAuthIdentity, PVOID CurrentUser, ULONG ErrorCodeFromBind);". */
typedef BOOLEAN (CALLBACK NOTIFYOFNEWCONNECTION)(
    PLDAP PrimaryConnection,
    PLDAP ReferralFromConnection,
    PWCHAR NewDN,
    PCHAR HostName,
    PLDAP NewConnection,
    ULONG PortNumber,
    PVOID SecAuthIdentity,
    PVOID CurrentUser,
    ULONG ErrorCodeFromBind);

/* ms892640 "QUERYFORCONNECTION": page prints
 * "typedef ULONG (_cdecl QUERYFORCONNECTION)(PLDAP PrimaryConnection,
 * PLDAP ReferralFromConnection, PWCHAR NewDN, PCHAR HostName,
 * ULONG PortNumber, PVOID SecAuthIdentity, PVOID CurrentUserToken,
 * PLDAP* ConnectionToUse);". */
typedef ULONG (CALLBACK QUERYFORCONNECTION)(
    PLDAP PrimaryConnection,
    PLDAP ReferralFromConnection,
    PWCHAR NewDN,
    PCHAR HostName,
    ULONG PortNumber,
    PVOID SecAuthIdentity,
    PVOID CurrentUserToken,
    PLDAP *ConnectionToUse);

/* ms897184 "VERIFYSERVERCERT": page prints
 * "typedef BOOLEAN (_cdecl VERIFYSERVERCERT) (PLDAP Connection,
 * PCCERT_CONTEXT pServerCert);".  PCCERT_CONTEXT is from wincrypt.h
 * (M48). */
typedef BOOLEAN (CALLBACK VERIFYSERVERCERT)(
    PLDAP Connection,
    PCCERT_CONTEXT pServerCert);

/* ms892294 "LDAP_REFERRAL_CALLBACK": "typedef struct
 * LdapReferralCallback {ULONG SizeOfCallbacks; QUERYFORCONNECTION*
 * QueryForConnection; NOTIFYOFNEWCONNECTION* NotifyRoutine;
 * DEREFERENCECONNECTION* DereferenceRoutine;} LDAP_REFERRAL_CALLBACK,
 * *PLDAP_REFERRAL_CALLBACK;". */
typedef struct LdapReferralCallback {
    ULONG                    SizeOfCallbacks;
    QUERYFORCONNECTION      *QueryForConnection;
    NOTIFYOFNEWCONNECTION   *NotifyRoutine;
    DEREFERENCECONNECTION   *DereferenceRoutine;
} LDAP_REFERRAL_CALLBACK, *PLDAP_REFERRAL_CALLBACK;

/* HELD -- ms892639 "QUERYCLIENTCERT": page prints
 * "BOOLEAN QUERYCLIENTCERT(PLDAP Connection,
 * PSecPkgContext_IssuerListInfoEx trusted_CAs, HCERTSTORE hCertStore,
 * DWORD* pcCreds);" but PSecPkgContext_IssuerListInfoEx (SSPI) has no
 * CE page in the harvested corpus, so the callback type is not
 * declared; recorded verbatim here per the dangling-type policy. */

/* ------------------------------------------------------------------ */
/* LDAP Functions (all: Header Winldap.h, Link Library Wldap32.lib,    */
/* OS "Windows CE .NET 4.0 and later" unless noted).                   */
/* ------------------------------------------------------------------ */

/* --- Session functions --- */
AKARI_CE_IMPORT LDAP*    cldap_open(PTCHAR HostName, ULONG PortNumber) AKARI_CE_NAME(cldap_open);            /* ms863877 */
AKARI_CE_IMPORT ULONG    ldap_abandon(LDAP *ld, ULONG msgid) AKARI_CE_NAME(ldap_abandon);                      /* ms891743 */
AKARI_CE_IMPORT ULONG    ldap_bind(LDAP *ld, PTCHAR dn, PTCHAR cred, ULONG method) AKARI_CE_NAME(ldap_bind);/* ms891748 */
AKARI_CE_IMPORT ULONG    ldap_bind_s(LDAP *ld, PTCHAR dn, PTCHAR cred, ULONG method) AKARI_CE_NAME(ldap_bind_s); /* ms891749 */
/* ms891756 ldap_connect: both the CE 5.0 page and its CE 6.0 twin
 * ee485147 print "PLDAP_TIMEVAL* timeout" (pointer to PLDAP_TIMEVAL)
 * -- kept verbatim. */
AKARI_CE_IMPORT ULONG    ldap_connect(LDAP *ld, PLDAP_TIMEVAL *timeout) AKARI_CE_NAME(ldap_connect);           /* ms891756 */
AKARI_CE_IMPORT ULONG    ldap_get_option(LDAP *ld, int option, void *outvalue) AKARI_CE_NAME(ldap_get_option);    /* ms892271 */
AKARI_CE_IMPORT LDAP*    ldap_init(PTCHAR HostName, ULONG PortNumber) AKARI_CE_NAME(ldap_init);             /* ms892275 */
AKARI_CE_IMPORT LDAP*    ldap_open(PTCHAR HostName, ULONG PortNumber) AKARI_CE_NAME(ldap_open);             /* ms892288 */
AKARI_CE_IMPORT ULONG    ldap_set_option(LDAP *ld, int option, void *invalue) AKARI_CE_NAME(ldap_set_option);     /* ms892310 */
AKARI_CE_IMPORT ULONG    ldap_simple_bind(LDAP *ld, PTCHAR dn, PTCHAR passwd) AKARI_CE_NAME(ldap_simple_bind);     /* ms892311 */
AKARI_CE_IMPORT ULONG    ldap_simple_bind_s(LDAP *ld, PTCHAR dn, PTCHAR passwd) AKARI_CE_NAME(ldap_simple_bind_s);   /* ms892312 */
AKARI_CE_IMPORT LDAP*    ldap_sslinit(PTCHAR HostName, ULONG PortNumber, int secure) AKARI_CE_NAME(ldap_sslinit); /* ms892314 */
AKARI_CE_IMPORT ULONG    ldap_unbind(LDAP *ld) AKARI_CE_NAME(ldap_unbind);                                    /* ms892317 */
AKARI_CE_IMPORT ULONG    ldap_unbind_s(LDAP *ld) AKARI_CE_NAME(ldap_unbind_s);                                  /* ms892318 */

/* --- Directory entry functions --- */
AKARI_CE_IMPORT ULONG    ldap_add(LDAP *ld, PTCHAR dn, LDAPMod *attrs[]) AKARI_CE_NAME(ldap_add);          /* ms891744 */
AKARI_CE_IMPORT ULONG    ldap_add_ext(LDAP *ld, PTCHAR dn, LDAPMod *attrs[],
                      LDAPControl **ServerControls,
                      LDAPControl **ClientControls,
                      ULONG *MessageNumber) AKARI_CE_NAME(ldap_add_ext);                       /* ms891745 */
AKARI_CE_IMPORT ULONG    ldap_add_ext_s(LDAP *ld, PTCHAR dn, LDAPMod *attrs[],
                        LDAPControl **ServerControls,
                        LDAPControl **ClientControls) AKARI_CE_NAME(ldap_add_ext_s);             /* ms891746 */
AKARI_CE_IMPORT ULONG    ldap_add_s(LDAP *ld, PTCHAR dn, LDAPMod *attrs[]) AKARI_CE_NAME(ldap_add_s);        /* ms891747 */
AKARI_CE_IMPORT ULONG    ldap_close_extended_op(LDAP *ld, ULONG MessageNumber) AKARI_CE_NAME(ldap_close_extended_op);    /* ms891751 */
AKARI_CE_IMPORT ULONG    ldap_compare(LDAP *ld, PTCHAR dn, PTCHAR attr, PTCHAR value) AKARI_CE_NAME(ldap_compare); /* ms891752 */
AKARI_CE_IMPORT ULONG    ldap_compare_ext(LDAP *ld, PTCHAR dn, PTCHAR Attr, PTCHAR Value,
                          struct berval *Data,
                          LDAPControl **ServerControls,
                          LDAPControl **ClientControls,
                          ULONG *MessageNumber) AKARI_CE_NAME(ldap_compare_ext);                   /* ms891753 */
AKARI_CE_IMPORT ULONG    ldap_compare_ext_s(LDAP *ld, PTCHAR dn, PTCHAR Attr, PTCHAR Value,
                            struct berval *Data,
                            LDAPControl **ServerControls,
                            LDAPControl **ClientControls) AKARI_CE_NAME(ldap_compare_ext_s);         /* ms891754 */
AKARI_CE_IMPORT ULONG    ldap_compare_s(LDAP *ld, PTCHAR dn, PTCHAR attr, PTCHAR value) AKARI_CE_NAME(ldap_compare_s); /* ms891755 */
AKARI_CE_IMPORT ULONG    ldap_delete(LDAP *ld, PTCHAR dn) AKARI_CE_NAME(ldap_delete);                         /* ms891766 */
AKARI_CE_IMPORT ULONG    ldap_delete_ext(LDAP *ld, PTCHAR dn,
                         LDAPControl **ServerControls,
                         LDAPControl **ClientControls,
                         ULONG *MessageNumber) AKARI_CE_NAME(ldap_delete_ext);                    /* ms891767 */
AKARI_CE_IMPORT ULONG    ldap_delete_ext_s(LDAP *ld, PTCHAR dn,
                           LDAPControl **ServerControls,
                           LDAPControl **ClientControls) AKARI_CE_NAME(ldap_delete_ext_s);          /* ms891768 */
AKARI_CE_IMPORT ULONG    ldap_delete_s(LDAP *ld, PTCHAR dn) AKARI_CE_NAME(ldap_delete_s);                       /* ms891769 */
AKARI_CE_IMPORT ULONG    ldap_modify(LDAP *ld, PTCHAR dn, LDAPMod *mods[]) AKARI_CE_NAME(ldap_modify);        /* ms892280 */
AKARI_CE_IMPORT ULONG    ldap_modify_ext(LDAP *ld, PTCHAR dn, LDAPMod *mods[],
                         LDAPControl **ServerControls,
                         LDAPControl **ClientControls,
                         ULONG *MessageNumber) AKARI_CE_NAME(ldap_modify_ext);                    /* ms892281 */
AKARI_CE_IMPORT ULONG    ldap_modify_ext_s(LDAP *ld, PTCHAR dn, LDAPMod *mods[],
                           LDAPControl **ServerControls,
                           LDAPControl **ClientControls) AKARI_CE_NAME(ldap_modify_ext_s);          /* ms892282 */
AKARI_CE_IMPORT ULONG    ldap_modify_s(LDAP *ld, PTCHAR dn, LDAPMod *mods[]) AKARI_CE_NAME(ldap_modify_s);      /* ms892283 */
AKARI_CE_IMPORT ULONG    ldap_rename_ext(LDAP *ld, PTCHAR dn, PTCHAR NewRDN,
                         PTCHAR NewParent, INT DeleteOldRdn,
                         LDAPControl **ServerControls,
                         LDAPControl **ClientControls,
                         ULONG *MessageNumber) AKARI_CE_NAME(ldap_rename_ext);                    /* ms892295 */
AKARI_CE_IMPORT ULONG    ldap_rename_ext_s(LDAP *ld, PTCHAR dn, PTCHAR NewRDN,
                           PTCHAR NewParent, INT DeleteOldRdn,
                           LDAPControl **ServerControls,
                           LDAPControl **ClientControls) AKARI_CE_NAME(ldap_rename_ext_s);          /* ms892296 */
AKARI_CE_IMPORT ULONG    ldap_extended_operation(LDAP *ld, PTCHAR Oid,
                                 struct berval *Data,
                                 LDAPControl **ServerControls,
                                 LDAPControl **ClientControls,
                                 ULONG *MessageNumber) AKARI_CE_NAME(ldap_extended_operation);            /* ms892261 */

/* --- Search functions --- */
AKARI_CE_IMPORT ULONG    ldap_check_filter(LDAP *ld, PTCHAR SearchFilter) AKARI_CE_NAME(ldap_check_filter);         /* ms891750 */
AKARI_CE_IMPORT ULONG    ldap_count_entries(LDAP *ld, LDAPMessage *res) AKARI_CE_NAME(ldap_count_entries);           /* ms891760 */
AKARI_CE_IMPORT ULONG    ldap_count_references(LDAP *ld, LDAPMessage *res) AKARI_CE_NAME(ldap_count_references);        /* ms891761 */
AKARI_CE_IMPORT ULONG    ldap_escape_filter_element(PTCHAR sourceFilterElement,
                                    ULONG sourceLength,
                                    PTCHAR destFilterElement,
                                    ULONG destLength) AKARI_CE_NAME(ldap_escape_filter_element);             /* ms892136 */
AKARI_CE_IMPORT PTCHAR   ldap_first_attribute(LDAP *ld, LDAPMessage *entry,
                              BerElement **ptr) AKARI_CE_NAME(ldap_first_attribute);                   /* ms892263 */
AKARI_CE_IMPORT LDAPMessage* ldap_first_entry(LDAP *ld, LDAPMessage *res) AKARI_CE_NAME(ldap_first_entry);         /* ms892264 */
AKARI_CE_IMPORT LDAPMessage* ldap_first_reference(LDAP *ld, LDAPMessage *res) AKARI_CE_NAME(ldap_first_reference);     /* ms892265 */
AKARI_CE_IMPORT PTCHAR   ldap_get_dn(LDAP *ld, LDAPMessage *entry) AKARI_CE_NAME(ldap_get_dn);                /* ms892266 */
AKARI_CE_IMPORT ULONG    ldap_get_next_page(LDAP *ExternalHandle,
                            LDAPSearch *SearchHandle, ULONG PageSize,
                            ULONG *MessageNumber) AKARI_CE_NAME(ldap_get_next_page);                 /* ms892268 */
AKARI_CE_IMPORT ULONG    ldap_get_next_page_s(LDAP *ExternalHandle,
                              LDAPSearch *SearchHandle,
                              LDAP_TIMEVAL *timeout, ULONG PageSize,
                              ULONG *TotalCount,
                              LDAPMessage **Results) AKARI_CE_NAME(ldap_get_next_page_s);              /* ms892269 */
AKARI_CE_IMPORT ULONG    ldap_get_paged_count(LDAP *ExternalHandle,
                              LDAPSearch *SearchBlock,
                              ULONG *TotalCount,
                              LDAPMessage *Results) AKARI_CE_NAME(ldap_get_paged_count);               /* ms892272 */
AKARI_CE_IMPORT PTCHAR*  ldap_get_values(LDAP *ld, LDAPMessage *entry, PTCHAR attr) AKARI_CE_NAME(ldap_get_values); /* ms892273 */
AKARI_CE_IMPORT struct berval** ldap_get_values_len(LDAP *ExternalHandle,
                                    LDAPMessage *Message,
                                    PTCHAR attr) AKARI_CE_NAME(ldap_get_values_len);                  /* ms892274 */
AKARI_CE_IMPORT PTCHAR   ldap_next_attribute(LDAP *ld, LDAPMessage *entry,
                             BerElement *ptr) AKARI_CE_NAME(ldap_next_attribute);                     /* ms892285 */
AKARI_CE_IMPORT LDAPMessage* ldap_next_entry(LDAP *ld, LDAPMessage *entry) AKARI_CE_NAME(ldap_next_entry);        /* ms892286 */
AKARI_CE_IMPORT LDAPMessage* ldap_next_reference(LDAP *ld, LDAPMessage *entry) AKARI_CE_NAME(ldap_next_reference);    /* ms892287 */
AKARI_CE_IMPORT ULONG    ldap_search(LDAP *ld, PTCHAR base, ULONG scope, PTCHAR filter,
                     PTCHAR attrs[], ULONG attrsonly) AKARI_CE_NAME(ldap_search);             /* ms892302 */
AKARI_CE_IMPORT ULONG    ldap_search_abandon_page(LDAP *ExternalHandle,
                                  LDAPSearch *SearchBlock) AKARI_CE_NAME(ldap_search_abandon_page);        /* ms892303 */
AKARI_CE_IMPORT ULONG    ldap_search_ext(LDAP *ld, PTCHAR base, ULONG scope,
                         PTCHAR filter, PTCHAR attrs[], ULONG attrsonly,
                         LDAPControl **ServerControls,
                         LDAPControl **ClientControls,
                         ULONG TimeLimit, ULONG SizeLimit,
                         ULONG *MessageNumber) AKARI_CE_NAME(ldap_search_ext);                    /* ms892304 */
AKARI_CE_IMPORT ULONG    ldap_search_ext_s(LDAP *ld, PTCHAR base, ULONG scope,
                           PTCHAR filter, PTCHAR attrs[], ULONG attrsonly,
                           LDAPControl **ServerControls,
                           LDAPControl **ClientControls,
                           struct l_timeval *timeout, ULONG SizeLimit,
                           LDAPMessage **res) AKARI_CE_NAME(ldap_search_ext_s);                     /* ms892305 */
AKARI_CE_IMPORT PLDAPSearch ldap_search_init_page(LDAP *ExternalHandle,
                                  PTCHAR DistinguishedName,
                                  ULONG ScopeOfSearch, PTCHAR SearchFilter,
                                  PTCHAR AttributeList[],
                                  ULONG AttributesOnly,
                                  LDAPControl **ServerControls,
                                  LDAPControl **ClientControls,
                                  ULONG PageTimeLimit, ULONG TotalSizeLimit,
                                  LDAPSortKey **SortKeys) AKARI_CE_NAME(ldap_search_init_page);         /* ms892306 */
AKARI_CE_IMPORT ULONG    ldap_search_s(LDAP *ld, PTCHAR base, ULONG scope, PTCHAR filter,
                       PTCHAR attrs[], ULONG attrsonly,
                       LDAPMessage **res) AKARI_CE_NAME(ldap_search_s);                         /* ms892307 */
AKARI_CE_IMPORT ULONG    ldap_search_st(LDAP *ld, PTCHAR base, ULONG scope, PTCHAR filter,
                        PTCHAR attrs[], ULONG attrsonly,
                        struct l_timeval *timeout,
                        LDAPMessage **res) AKARI_CE_NAME(ldap_search_st);                        /* ms892308 */
AKARI_CE_IMPORT ULONG    ldap_result(LDAP *ld, ULONG msgid, ULONG all,
                     LDAP_TIMEVAL *timeout, LDAPMessage **res) AKARI_CE_NAME(ldap_result);    /* ms892297 */

/* --- Error handling functions --- */
AKARI_CE_IMPORT PTCHAR   ldap_err2string(ULONG err) AKARI_CE_NAME(ldap_err2string);                               /* ms892105 */
AKARI_CE_IMPORT ULONG    ldap_result2error(LDAP *ld, LDAPMessage *res, ULONG freeit) AKARI_CE_NAME(ldap_result2error); /* ms892298 */
AKARI_CE_IMPORT ULONG    LdapGetLastError(void) AKARI_CE_NAME(LdapGetLastError);                                   /* ms892267 */
AKARI_CE_IMPORT ULONG    LdapMapErrorToWin32(ULONG LdapError) AKARI_CE_NAME(LdapMapErrorToWin32);                     /* ms892276 */

/* --- Memory management functions --- */
AKARI_CE_IMPORT ULONG    ldap_control_free(LDAPControl *Control) AKARI_CE_NAME(ldap_control_free);                  /* ms891758 */
AKARI_CE_IMPORT ULONG    ldap_controls_free(LDAPControl **Controls) AKARI_CE_NAME(ldap_controls_free);               /* ms891759 */
AKARI_CE_IMPORT VOID     ldap_memfree(PTCHAR Block) AKARI_CE_NAME(ldap_memfree);                               /* ms892277 */
AKARI_CE_IMPORT ULONG    ldap_msgfree(LDAPMessage *res) AKARI_CE_NAME(ldap_msgfree);                           /* ms892284 */
AKARI_CE_IMPORT ULONG    ldap_value_free(PTCHAR *vals) AKARI_CE_NAME(ldap_value_free);                            /* ms892321 */
AKARI_CE_IMPORT ULONG    ldap_value_free_len(struct berval **vals) AKARI_CE_NAME(ldap_value_free_len);                /* ms892322 */

/* --- Parse functions (LDAP Search book) --- */
AKARI_CE_IMPORT PTCHAR   ldap_dn2ufn(PTCHAR dn) AKARI_CE_NAME(ldap_dn2ufn);                                   /* ms891770 */
AKARI_CE_IMPORT PTCHAR*  ldap_explode_dn(PTCHAR dn, ULONG notypes) AKARI_CE_NAME(ldap_explode_dn);                /* ms892251 */
/* ms892289 ldap_parse_extended_result: both the CE 5.0 page and its
 * CE 6.0 twin ee486808 print the first parameter as a bare "LDAP
 * Connection" (no indirection -- the LDAP tag is opaque, so the
 * by-value print cannot compile); the documented reading is the
 * connection pointer, recorded here. */
AKARI_CE_IMPORT ULONG    ldap_parse_extended_result(LDAP *Connection,
                                    LDAPMessage *ResultMessage,
                                    PTCHAR *ResultOID,
                                    struct berval **ResultData,
                                    BOOL Freeit) AKARI_CE_NAME(ldap_parse_extended_result);                  /* ms892289 */
AKARI_CE_IMPORT ULONG    ldap_parse_page_control(LDAP *ExternalHandle,
                                 LDAPControl **ServerControls,
                                 ULONG *TotalCount,
                                 struct berval **Cookie) AKARI_CE_NAME(ldap_parse_page_control);          /* ms892290 */
AKARI_CE_IMPORT ULONG    ldap_parse_reference(LDAP *Connection, LDAPMessage *ResultMessage,
                              PTCHAR **Referrals) AKARI_CE_NAME(ldap_parse_reference);                 /* ms892291 */
AKARI_CE_IMPORT ULONG    ldap_parse_result(LDAP *Connection, LDAPMessage *ResultMessage,
                           ULONG *ReturnCode,          /* OPTIONAL */
                           PTCHAR *MatchedDNs,         /* OPTIONAL */
                           PTCHAR *ErrorMessage,       /* OPTIONAL */
                           PTCHAR **Referrals,         /* OPTIONAL */
                           LDAPControl ***ServerControls, /* OPTIONAL */
                           BOOLEAN Freeit) AKARI_CE_NAME(ldap_parse_result);            /* ms892292 */
AKARI_CE_IMPORT ULONG    ldap_parse_sort_control(LDAP *ExternalHandle,
                                 LDAPControl **Control, ULONG *Result,
                                 PTCHAR *Attribute) AKARI_CE_NAME(ldap_parse_sort_control);               /* ms892293 */
AKARI_CE_IMPORT ULONG    ldap_create_page_control(LDAP *ExternalHandle, ULONG PageSize,
                                  struct berval *Cookie, UCHAR IsCritical,
                                  LDAPControl **Control) AKARI_CE_NAME(ldap_create_page_control);          /* ms891764 */
AKARI_CE_IMPORT ULONG    ldap_create_sort_control(LDAP *ExternalHandle,
                                  LDAPSortKey **SortKeys,
                                  UCHAR IsCritical,
                                  LDAPControl **Control) AKARI_CE_NAME(ldap_create_sort_control);          /* ms891765 */
AKARI_CE_IMPORT ULONG    ldap_count_values(PTCHAR *vals) AKARI_CE_NAME(ldap_count_values);                          /* ms891762 */
AKARI_CE_IMPORT ULONG    ldap_count_values_len(struct berval **vals) AKARI_CE_NAME(ldap_count_values_len);              /* ms891763 */
AKARI_CE_IMPORT ULONG    ldap_ufn2dn(PTCHAR ufn, PTCHAR *pDn) AKARI_CE_NAME(ldap_ufn2dn);                     /* ms892316 */

/* --- Other LDAP functions --- */
AKARI_CE_IMPORT int      LdapUnicodeToUTF8(LPCWSTR lpSrcStr, int cchSrc,
                           LPSTR lpDestStr, int cchDest) AKARI_CE_NAME(LdapUnicodeToUTF8);          /* ms892319 */
AKARI_CE_IMPORT int      LdapUTF8ToUnicode(LPCSTR lpSrcStr, int cchSrc,
                           LPWSTR lpDestStr, int cchDest) AKARI_CE_NAME(LdapUTF8ToUnicode);         /* ms892320 */

/* --- SASL bind (extended) --- */
/* ms892301 ldap_sasl_bind_s: page and CE 6.0 twin ee486753 print
 * "ULONG ldap_sasl_bind_s(LDAP* ExternalHandle, const UNICODE PTCHAR
 * DistName, const UNICODE PTCHAR AuthMechanism, const BERVAL* cred,
 * LDAPControlA** ServerCtrls, LDAPControlA** ClientCtrls, PBERVAL*
 * ServerData);" -- the ServerCtrls/ClientCtrls parameter type is
 * printed as LDAPControlA** (no CE page defines an LDAPControlA; the
 * LDAPControl page ms891757 defines only LDAPControl).  Declared with
 * the documented LDAPControl spelling; see docs/inventory.md M54. */
AKARI_CE_IMPORT ULONG    ldap_sasl_bind_s(LDAP *ExternalHandle, const PTCHAR DistName,
                          const PTCHAR AuthMechanism, const BERVAL *cred,
                          LDAPControl **ServerCtrls,
                          LDAPControl **ClientCtrls,
                          PBERVAL *ServerData) AKARI_CE_NAME(ldap_sasl_bind_s);                    /* ms892301 */

/* HELD -- ms892300 "ldap_sasl_bind": the CE 5.0 page mis-prints the
 * ldap_sasl_bind_s prototype on the asynchronous bind page (it shows
 * "... PBERVAL-free int* MessageNumber" form, see inventory M54);
 * the asynchronous prototype cannot be confirmed from the CE 5.0
 * page and is not declared. */

/* ------------------------------------------------------------------
 * Book surface: ldap-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms863826 berval (Header: Winldap.h.) */
/* ms892300 ldap_sasl_bind (Header: Winldap.h.) */
/* ms893453 Session Options (Header: Winldap.h.) */

/* ------------------------------------------------------------------
 * Book surface: ldap-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms862089 Authenticating an LDAP Client */
/* ms862090 Authentication Operations */
/* ms862108 Closing a Connection */
/* ms862140 Differences Between the LDAP Implementation in Windows CE and Windows Server 2003 */
/* ms862144 Establishing an LDAP Session */
/* ms862172 Interrogation Operations */
/* ms862244 LDAP Distinguished Names */
/* ms862372 LDAP Migration */
/* ms862177 LDAP OS Design Development */
/* ms862403 LDAP Registry Settings */
/* ms862417 LDAP Samples */
/* ms862429 LDAP Schema Model */
/* ms862439 LDAP Security */
/* ms862452 LDAP Security Model */
/* ms862477 Managing Memory */
/* ms862548 Modifying a Directory Entry */
/* ms862670 Paging Search Results */
/* ms862693 Searching a Directory */
/* ms862704 Sorting Search Results */
/* ms862713 Synchronous vs. Asynchronous Calls */
/* ms862719 Update Operations */
/* ms862720 Using Controls */

/* ------------------------------------------------------------------
 * Book surface: ldap-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms863826 berval (Header: Winldap.h.) */
/* ms892300 ldap_sasl_bind (Header: Winldap.h.) */
/* ms893453 Session Options (Header: Winldap.h.) */

/* ------------------------------------------------------------------
 * Book surface: ldap-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms862089 Authenticating an LDAP Client */
/* ms862090 Authentication Operations */
/* ms862108 Closing a Connection */
/* ms862140 Differences Between the LDAP Implementation in Windows CE and Windows Server 2003 */
/* ms862144 Establishing an LDAP Session */
/* ms862172 Interrogation Operations */
/* ms862244 LDAP Distinguished Names */
/* ms862372 LDAP Migration */
/* ms862177 LDAP OS Design Development */
/* ms862403 LDAP Registry Settings */
/* ms862417 LDAP Samples */
/* ms862429 LDAP Schema Model */
/* ms862439 LDAP Security */
/* ms862452 LDAP Security Model */
/* ms862477 Managing Memory */
/* ms862548 Modifying a Directory Entry */
/* ms862670 Paging Search Results */
/* ms862693 Searching a Directory */
/* ms862704 Sorting Search Results */
/* ms862713 Synchronous vs. Asynchronous Calls */
/* ms862719 Update Operations */
/* ms862720 Using Controls */

/* ------------------------------------------------------------------
 * Book surface: ldap-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms863826 berval (Header: Winldap.h.) */
/* ms892300 ldap_sasl_bind (Header: Winldap.h.) */
/* ms893453 Session Options (Header: Winldap.h.) */

/* ------------------------------------------------------------------
 * Book surface: ldap-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms862089 Authenticating an LDAP Client */
/* ms862090 Authentication Operations */
/* ms862108 Closing a Connection */
/* ms862140 Differences Between the LDAP Implementation in Windows CE and Windows Server 2003 */
/* ms862144 Establishing an LDAP Session */
/* ms862172 Interrogation Operations */
/* ms862244 LDAP Distinguished Names */
/* ms862372 LDAP Migration */
/* ms862177 LDAP OS Design Development */
/* ms862403 LDAP Registry Settings */
/* ms862417 LDAP Samples */
/* ms862429 LDAP Schema Model */
/* ms862439 LDAP Security */
/* ms862452 LDAP Security Model */
/* ms862477 Managing Memory */
/* ms862548 Modifying a Directory Entry */
/* ms862670 Paging Search Results */
/* ms862693 Searching a Directory */
/* ms862704 Sorting Search Results */
/* ms862713 Synchronous vs. Asynchronous Calls */
/* ms862719 Update Operations */
/* ms862720 Using Controls */

/* ------------------------------------------------------------------
 * Book surface: ldap (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms863826 berval (Header: Winldap.h.) */
/* ms892300 ldap_sasl_bind (Header: Winldap.h.) */
/* ms893453 Session Options (Header: Winldap.h.) */

/* ------------------------------------------------------------------
 * Book surface: ldap (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa513731 LDAP Callback Functions */
/* aa513732 LDAP Directory Entry Functions */
/* aa513733 LDAP Enumerations */
/* aa513734 LDAP Error Handling Functions */
/* aa513735 LDAP Functions */
/* aa513736 LDAP Memory Management Functions */
/* aa513738 LDAP Search Functions */
/* aa513739 LDAP Session Functions */
/* aa513740 LDAP Structures */
/* ms862667 Other LDAP Functions */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINLDAP_H */
