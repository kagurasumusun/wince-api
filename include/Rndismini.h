/* Rndismini.h -- RNDIS miniport MDD/PDD driver library (Rndismini).
 *
 * Source pages: Network Driver Reference rows printing
 * "Header: Rndismini.h" (16) and "Header: RndisMini.h" (1, the
 * GetHandler typedef -- same header, capital-M spelling as printed;
 * merged here, one file per header name).
 *
 * The MDD/PDD helper functions print no Link Library row (they are
 * driver-library functions, like the FirewallLog* precedent M77c)
 * and are declared; every DATA_WRAPPER use is through a pointer, so
 * the unpublished LIST_ENTRY member holds only the struct, not the
 * functions.  RNDIS_PDD_CHARACTERISTICS prints no layout (opaque).
 * See docs/inventory.md M78c.
 */

#ifndef AKARI_RNDISMINI_H
#define AKARI_RNDISMINI_H

#include "Windef.h"    /* BOOL, UINT, PVOID, ULONG, PBYTE */

/* ms902178 "MDDAllocDataWrapper" row: DATA_WRAPPER print
 * `typedef struct _DATA_WRAPPER { LIST_ENTRY Link; UCHAR* pucData;
 * DWORDdwDataSize;} DATA_WRAPPER, *PDATA_WRAPPER;` -- LIST_ENTRY is
 * not printed by any CE page; held, pointer-only. */
typedef struct _DATA_WRAPPER DATA_WRAPPER, *PDATA_WRAPPER;

/* "RNDIS_PDD_CHARACTERISTICS" (no print on any CE page; referenced
 * by PDDInit): opaque. */
typedef struct _RNDIS_PDD_CHARACTERISTICS RNDIS_PDD_CHARACTERISTICS,
    *PRNDIS_PDD_CHARACTERISTICS;

/* --- PDD callback typedefs (printed). -------------------------- */
/* "SendRndisMessageHandler": print
 * `typedef void(* PFN_PDD_SEND_RNDIS_MESSAGE)( PDATA_WRAPPER
 * pDataWrapper);` */
typedef void (*PFN_PDD_SEND_RNDIS_MESSAGE)(PDATA_WRAPPER pDataWrapper);

/* "SendRndisPacketHandler": print
 * `typedef void (* PFN_PDD_SEND_RNDIS_PACKET)( PDATA_WRAPPER
 * pDataWrapper);` */
typedef void (*PFN_PDD_SEND_RNDIS_PACKET)(PDATA_WRAPPER pDataWrapper);

/* "SetHandler": print
 * `typedef BOOL (* PFN_PDD_SET)( UINT uiRequestId, PVOID pvData,
 * ULONG ulDataLength);` */
typedef BOOL (*PFN_PDD_SET)(UINT uiRequestId, PVOID pvData,
                             ULONG ulDataLength);

/* "GetHandler" (Header: RndisMini.h as printed): print
 * `typedef BOOL(* PFN_PDD_GET)(UINT uiRequestId,PVOID pvData,
 * ULONG ulDataLength,ULONG* pulRequiredLength);` plus the four
 * REQ_ID_* request-identifier constants below. */
typedef BOOL (*PFN_PDD_GET)(UINT uiRequestId, PVOID pvData,
                             ULONG ulDataLength,
                             ULONG *pulRequiredLength);

#define REQ_ID_VENDOR_ID          0x80000001
#define REQ_ID_VENDOR_DESCRIPTION 0x80000002
#define REQ_ID_DEVICE_MAX_RX      0x80000003
#define REQ_ID_DEVICE_MACADDR     0x80000004

/* --- MDD/PDD functions (printed; no Link Library row). -------- */
/* ms902178 "MDDAllocDataWrapper": `PDATA_WRAPPER
 * MDDAllocDataWrapper(void);` */
AKARI_CE_IMPORT PDATA_WRAPPER MDDAllocDataWrapper(void)
                    AKARI_CE_NAME(MDDAllocDataWrapper);

/* ms902181 "MDDFreeDataWrapper" page (two prints on one page):
 * `void MDDFreeDataWrapper(PDATA_WRAPPERpDataWrapper);` and
 * `PBYTE MDDAllocMem(void);` */
AKARI_CE_IMPORT void MDDFreeDataWrapper(PDATA_WRAPPER pDataWrapper)
                    AKARI_CE_NAME(MDDFreeDataWrapper);
AKARI_CE_IMPORT PBYTE MDDAllocMem(void)
                    AKARI_CE_NAME(MDDAllocMem);

/* ms902182 "MDDFreeMem": `void MDDFreeMem(PBYTEpBuffer);` */
AKARI_CE_IMPORT void MDDFreeMem(PBYTE pBuffer)
                    AKARI_CE_NAME(MDDFreeMem);

/* "MddDisconnect": `void MddDisconnect();` (empty parens -> void). */
AKARI_CE_IMPORT void MddDisconnect(void)
                    AKARI_CE_NAME(MddDisconnect);

/* "MddIndicateRndisMessage":
 * `void MddIndicateRndisMessage(PDATA_WRAPPER pDataWrapper);` */
AKARI_CE_IMPORT void MddIndicateRndisMessage(PDATA_WRAPPER pDataWrapper)
                    AKARI_CE_NAME(MddIndicateRndisMessage);

/* "MddIndicateRndisPacket":
 * `void MddIndicateRndisPacket(PDATA_WRAPPERpDataWrapper);` */
AKARI_CE_IMPORT void MddIndicateRndisPacket(PDATA_WRAPPER pDataWrapper)
                    AKARI_CE_NAME(MddIndicateRndisPacket);

/* "PDDInit": `BOOL PDDInit(RNDIS_PDD_CHARACTERISTICS*
 * pRndisPddCharacteristics,PBYTE pBaseAddress);` */
AKARI_CE_IMPORT BOOL PDDInit(RNDIS_PDD_CHARACTERISTICS *pRndisPddCharacteristics,
                    PBYTE pBaseAddress) AKARI_CE_NAME(PDDInit);

#endif /* AKARI_RNDISMINI_H */
